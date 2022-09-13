#include <iostream>
#include <fstream>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Var.hpp"

typedef boost::property_tree::ptree ptree;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "You must specify a file to parse" << std::endl;
		return 1;
	}
	
	ptree tree;
	boost::property_tree::read_xml(argv[1], tree);
	
	auto testTag = tree.get_child_optional("test");
	
	if (testTag == boost::none)
	{
		std::cerr << "File must contain a 'test' tag." << std::endl;
		return 1;
	}

	Seq root = Seq(
		std::make_shared<ptree>(testTag.get()),
		1);
	
	if (argc == 3)
	{
		std::ofstream outputFile(argv[2], std::ios::trunc);
		outputFile << root;
		outputFile.close();
	}
	else
	{
		std::cout << root;
	}
}
