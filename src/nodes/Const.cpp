#include <iostream>

#include "CPTG/nodes/Const.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace cptg;

Const::Const() : value("") { }

Const::Const(ptree& constTag)
{
	auto attributes = constTag.get_child_optional("<xmlattr>");
	bool attributeExists =
		attributes != boost::none && attributes.value().count("value") != 0;

	if(attributeExists)
	{
		value = constTag.get< std::string >("<xmlattr>.value");
	}
	else
	{
		value = "";
	}
}

std::string Const::getString() const
{
	return value + ' ';
}
