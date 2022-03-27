#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number),
    range( {'0', '9'} )
{
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
}

// Returns true if type is valid, type can be empty
bool Var::FindType(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(attributes.value().count("type"))
    {
        // If type is not in typemap, return false
        if(typeMap.find(attributes.value().get<std::string>("type")) == typeMap.end())
        {
            return false;
        }

        varType = typeMap[varTag->get<std::string>("<xmlattr>.type")];
    }

    return true;
}

void Var::FindNumericRange(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    // if no range parameter is specified, return
    if(attributes.value().count("range"))
    {
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
    else
    {
        range = {0, 9};
    }
}

void Var::FindLexicalRange(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    // if no range parameter is specified, set default lexical range and return
    if(attributes.value().count("range"))
    {
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
        else if(rangeKey == "ALL")
        {
            range = {'!', '~'};
        }
        else
        {
            std::cout << "Error: Unknown range\nUsed default instead" << std::endl;
            range = {'a', 'z'};
        }
    }
    else
    {
        // Set default range for lexical variables
        range = {'a', 'z'};
    }
}

void Var::FindLength(const boost::optional< boost::property_tree::ptree& >& attributes)
{
    if(attributes.value().count("length"))
    {
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
    else
    {
        length = 3;
    }
}

void Var::Print()
{

}
