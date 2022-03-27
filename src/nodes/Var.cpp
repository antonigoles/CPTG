#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number),
    range( {48, 57} )
{
    boost::optional< boost::property_tree::ptree& > attributes =
        varTag->get_child_optional("<xmlattr>");

    if(attributes)
    {
        FindParameters(attributes);
    }
}

void Var::FindParameters(boost::optional< boost::property_tree::ptree& >& attributes)
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
        FindLength();
    }
}

// Returns true if type is valid, type can be empty
bool Var::FindType( boost::optional< boost::property_tree::ptree& >& attributes )
{
    if(attributes.value().count("type"))
    {
        // TODO: Check if type is valid

        varType = typeMap[varTag->get<std::string>("<xmlattr>.type")];
        return true;
    }

    return true;
}

void Var::FindNumericRange(boost::optional< boost::property_tree::ptree& >& attributes)
{
    // if no range parameter is specified, return
    if(!attributes.value().count("range"))
    {
        return;
    }
    
}

void Var::FindLexicalRange(boost::optional< boost::property_tree::ptree& >& attributes)
{
    // if no range parameter is specified, set default lexical range and return
    if(!attributes.value().count("range"))
    {
        range = {97, 122};
        return;
    }

}

void Var::FindLength()
{

}

void Var::Print()
{

}
