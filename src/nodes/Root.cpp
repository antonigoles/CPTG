#include "Root.hpp"

Root::Root()
{
    std::cout << "root construct\n";
}

void Root::setRootTag(std::shared_ptr< boost::property_tree::ptree > rootTag)
{
    std::cout << "root tag set!\n";
}

void Root::FindSubNodes()
{

}

void Root::Print()
{
    
}
