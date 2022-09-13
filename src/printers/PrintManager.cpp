#include <fstream>
#include <iostream>

#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Var.hpp"
#include "CPTG/printers/PrintManager.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace cptg;

PrintManager::PrintManager() { }

PrintManager::PrintManager(std::string inputFile) : inputFile(inputFile) { }

PrintManager::PrintManager(std::string inputFile, std::string outputFile) :
	inputFile(inputFile), outputFile(outputFile)
{
}

void PrintManager::findNodes()
{
	if(inputFile == "")
	{
		std::cerr << "You must provide an input file.";
		exit(1);
	}

	ptree tree;
	boost::property_tree::read_xml(inputFile, tree);
	auto testTag = tree.get_child_optional("test");

	if(testTag == boost::none)
	{
		std::cerr << "File must contain a 'test' tag." << std::endl;
		exit(1);
	}

	root = cptg::Seq(testTag.get(), 1);
}

void PrintManager::generateNewTest()
{
	testBuff.clear();
	testBuff = root.getString();
}

void PrintManager::printToFile()
{
	if(outputFile == "")
	{
		std::cerr << "You must prvide an output file name to print to cmd";
		return; // Return because this is non-criticall error
	}

	if(testBuff == "")
	{
		testBuff = root.getString();
	}

	std::ofstream file(outputFile, std::ios::trunc);
	file << testBuff;
	file.close();

	std::cout << "Output written to " << outputFile;
}

void PrintManager::printToConsole()
{
	if(testBuff == "")
	{
		testBuff = root.getString();
	}
	std::cout << testBuff;
}
