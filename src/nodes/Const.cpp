#include <iostream>

#include "CPTG/nodes/Const.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>

Const::Const() : value("") { }

Const::Const(std::shared_ptr< ptree > tag)
{
	auto attributes = tag->get_child_optional("<xmlattr>");
	bool attributeExists = attributes != boost::none && attributes.value().count("value") != 0;

	if(attributeExists)
	{
		value = tag->get<std::string>("<xmlattr>.value");
	}
	else
	{
		value = "";
	}
}

void Const::Print() const
{
	std::cout << value << ' ';
}
