#include "Const.hpp"

Const::Const() : value("") { }

Const::Const(std::shared_ptr< boost::property_tree::ptree > tag) : 
    value(tag->get<std::string>("<xmlattr>.value"))
{

}

void Const::Print()
{
    std::cout << value << ' ';
}
