#include <iostream>

#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Const.hpp"
#include "CPTG/nodes/Br.hpp"
#include "CPTG/nodes/Var.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace cptg;

// Creates a shared pointer to nodeType object
#define SharedNode(nodeType, propTree) \
	std::make_shared<nodeType>( \
		nodeType(std::make_shared< ptree >(propTree)))

Seq::Seq() : times(1) { }

Seq::Seq(std::shared_ptr< ptree > sT) : seqTag(sT)
{
	auto attributes = seqTag->get_child_optional("<xmlattr>");
	bool attributeExists = attributes != boost::none && attributes.value().count("times") != 0;

	if(attributeExists)
	{
		times = seqTag->get<int>("<xmlattr>.times");
	}
	else
	{
		times = 1;
	}

	FindSubNodes();
}

Seq::Seq(std::shared_ptr< ptree > sT, int times) : 
	seqTag(sT),
	times(times) 
{
	FindSubNodes();
}

// TODO: Transform Node to act as a factory to clean up this part of code
void Seq::FindSubNodes()
{
	BOOST_FOREACH(ptree::value_type & child, (*seqTag))
	{
		if (child.first == "seq")
		{
			subnodes.push_back(SharedNode(Seq, child.second));
		}
		else if (child.first == "const")
		{
			subnodes.push_back(SharedNode(Const, child.second));
		}
		else if (child.first == "var")
		{
			subnodes.push_back(SharedNode(Var, child.second));
		}
		else if (child.first == "br")
		{
			subnodes.push_back(std::make_shared<Br>());
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