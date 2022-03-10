#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number)
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

    // Find the range for var variable
    if(varType == Type::Number || varType == Type::Float)
    {
        FindNumericRange();
    }
    else
    {
        FindLexicalRange();
    }
    
    // Find lengh only if needed
    if(varType == Type::String || varType == Type::Float)
    {
        FindLength();
    }
}

void Var::Print()
{
    std::cout << ' ';
}
