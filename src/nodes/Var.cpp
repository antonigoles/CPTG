#include "Var.hpp"

Var::Var() : varType(Type::Number) { }

Var::Var(std::shared_ptr< boost::property_tree::ptree > tag) : 
    varTag(tag),
    varType(Type::Number)
{

}

void Var::FindNumericRange()
{

}

void Var::Print()
{
    std::cout << ' ';
}
