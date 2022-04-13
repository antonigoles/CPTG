#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number),
    range( {'0', '9'} )
{
    srand(time(NULL));
    boost::optional< boost::property_tree::ptree& > attributes =
        varTag->get_child_optional("<xmlattr>");

    if(attributes)
    {
        FindParameters(attributes);
    }
}

void Var::FindParameters(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(!FindType(attributes))
    {
        std::cout << "Error: Unknown type of variable" << std::endl;
        return;
    }

    // Find range depending on variable type
    if(varType == Type::Number || varType == Type::Float)
    {
        FindNumericRange(attributes);
    }
    else
    {
        FindLexicalRange(attributes);
    }
    
    // Find lengh only if needed
    if(varType == Type::String || varType == Type::Float)
    {
        FindLength(attributes);
    }
    else if(varType == Type::Char)
    {
        length = 1;
    }
}

// Returns true if type is valid, type can be empty
bool Var::FindType(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(!attributes.value().count("type"))
    {
        return true;
    }

    // If type is not in typemap, return false
    if(typeMap.find(attributes.value().get<std::string>("type")) == typeMap.end())
    {
        return false;
    }

    varType = typeMap[varTag->get<std::string>("<xmlattr>.type")];
    return true;
}

void Var::FindNumericRange(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(!attributes.value().count("range"))
    {
        range = {0, 9};
        return;
    }

    std::string rangeStr = attributes.value().get<std::string>("range");
    std::vector< std::string > splitRange;

    boost::split(splitRange, rangeStr, boost::is_any_of(":"));

    if(std::stoi(splitRange[0]) > std::stoi(splitRange[1]))
    {
        std::cout << "Error: Range is not valid\nUsing default instead" << std::endl;
        range = {0, 9};
        return;
    }

    range = {std::stoi(splitRange[0]), std::stoi(splitRange[1])};
}

void Var::FindLexicalRange(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(!attributes.value().count("range"))
    {
        range = {'a', 'z'};
        return;
    }

    std::string rangeKey = varTag->get<std::string>("<xmlattr>.range");

    if(rangeKey == "abc")
    {
        range = {'a', 'z'};
    }
    if(rangeKey == "ABC")
    {
        range = {'A', 'Z'};
    }
    else if(rangeKey == "special")
    {
        // TODO: range does not cover all characters
        range = {':', '@'};
    }
    else if(rangeKey == "all")
    {
        range = {'!', '~'};
    }
    else
    {
        std::cout << "Error: Unknown range\nUsed default instead" << std::endl;
        range = {'a', 'z'};
    }
}

void Var::FindLength(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(!attributes.value().count("length"))
    {
        length = 3;
        return;
    }

    int readLength = varTag->get<int>("<xmlattr>.length");
        
    if(readLength >= 0)
    {
        length = readLength;
    }
    else
    {
        std::cout << "Error: Length must be positive\nUsing default length instead" << std::endl;
        length = 3;
    }
}

void Var::Print()
{
    if(varType == Type::Number || varType == Type::Float)
    {
        int randomNumber = GenerateRandomNumber();
        std::cout << randomNumber;

        if(varType == Type::Float)
        {
            std::cout << GetReverseNumber(randomNumber);
        }
    }
    else if(varType == Type::String || varType == Type::Char)
    {
        for(int i = 0; i < length; i++)
        {
            std::cout << GenerateRandomChar();
        }
    }
    
    std::cout << " ";
}

char Var::GenerateRandomChar()
{
    return char(range.first + rand() % (range.second - range.first + 1));
}

int Var::GenerateRandomNumber()
{
    return (rand() % (range.second - range.first + 1) + range.first) - '0';
}

std::string Var::GetReverseNumber(int generatedNumber)
{
    // To avoid exceeding provided range
    if(generatedNumber == range.second)
    {
        return "";
    }

    std::stringstream ss, tempStream;
    
    for(int i = 0; i < length; i++)
    {
        tempStream << char('0' + rand() % 10);
        if(tempStream.str().back() != '0')
        {
            ss << tempStream.str();
            tempStream.str("");
        }
    }

    if(!ss.str().empty())
    {
        ss << '.';
    }

    std::string str = ss.str();
    std::reverse(str.begin(), str.end());
    return str;
}