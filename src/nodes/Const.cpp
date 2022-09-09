#include <iostream>

#include "CPTG/nodes/Const.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>

Const::Const() : value("") { }

Const::Const(std::shared_ptr< ptree > tag)
{
	boost::optional< ptree& > child = tag->get_child_optional("<xmlattr>");
	bool attributeExists = child != boost::none && child.value().count("value");

	if(attributeExists)
	{
		value = tag->get<std::string>("<xmlattr>.value");
	}
	else
	{
		value = "";
	}
}

void Const::Print()
{
	std::cout << value << ' ';
}
