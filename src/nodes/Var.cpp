#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number),
    range( {48, 57} )
{
    // Pointer created to attributes node only if they exist
    boost::optional< boost::property_tree::ptree& > child =
        varTag->get_child_optional("<xmlattr>");

    if(child)
    {
        if(child.value().count("type"))
        {
            // TODO: what if the entered type does not exist?
            varType = typeMap[varTag->get<std::string>("<xmlattr>.type")];
        }
    }
    else
    // No Parameters are specified (all default)
    {
        return;
    }

    // Find the range for var variable
    if(varType == Type::Number || varType == Type::Float)
    {
        FindNumericRange(child);
    }
    else
    {
        FindLexicalRange(child);
    }
    
    // Find lengh only if needed
    if(varType == Type::String || varType == Type::Float)
    {
        FindLength();
    }
}

void Var::FindNumericRange(boost::optional< boost::property_tree::ptree& >& child)
{
    // if no range parameter is specified, return
    if(!child.value().count("range"))
    {
        return;
    }
    
}

void Var::FindLexicalRange(boost::optional< boost::property_tree::ptree& >& child)
{
    // if no range parameter is specified, set default lexical range and return
    if(!child.value().count("range"))
    {
        range = {97, 122};
        return;
    }

}

void Var::Print()
{

}
