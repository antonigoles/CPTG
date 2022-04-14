#include "Const.hpp"

Const::Const() : value("") { }

Const::Const(std::shared_ptr< boost::property_tree::ptree > tag) : 
    value("")
{
    // Pointer created to attributes node only if they exist
    boost::optional< boost::property_tree::ptree& > child =
        tag->get_child_optional("<xmlattr>");

    if(child)
    {
        if(child.value().count("value"))
        {
            value = tag->get<std::string>("<xmlattr>.value");
        }
    }
}

void Const::Print()
{
    std::cout << value << ' ';
}
