#include <iostream>

#include "CPTG/nodes/Br.hpp"
#include "CPTG/nodes/Const.hpp"
#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Var.hpp"

#include <boost/foreach.hpp>
#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace cptg;

Seq::Seq() : times(1) { }

Seq::Seq(ptree& seqTag)
{
	auto attributes = seqTag.get_child_optional("<xmlattr>");
	bool attributeExists =
		attributes != boost::none && attributes.value().count("times") != 0;

	if(attributeExists)
	{
		times = seqTag.get< int >("<xmlattr>.times");
	}
	else
	{
		times = 1;
	}

	FindSubNodes(seqTag);
}

Seq::Seq(ptree& seqTag, int times) : times(times)
{
	FindSubNodes(seqTag);
}

void Seq::FindSubNodes(ptree& seqTag)
{
	BOOST_FOREACH(ptree::value_type& child, seqTag)
	{
		if(child.first == "seq")
		{
			subnodes.push_back(std::make_shared< Seq >(Seq(child.second)));
		}
		else if(child.first == "const")
		{
			subnodes.push_back(std::make_shared< Const >(Const(child.second)));
		}
		else if(child.first == "var")
		{
			subnodes.push_back(std::make_shared< Var >(Var(child.second)));
		}
		else if(child.first == "br")
		{
			subnodes.push_back(std::make_shared< Br >());
		}
	}
}

std::string Seq::getString() const
{
	std::string result = "";
	for(int i = 0; i < times; i++)
	{
		for(auto& node : subnodes)
		{
			result += node->getString();
		}
	}

	return result;
}
