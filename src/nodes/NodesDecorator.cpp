#include <fstream>
#include <iostream>

#include "CPTG/nodes/NodesDecorator.hpp"
#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Var.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace cptg;

PrintManager::PrintManager() { }

void PrintManager::setInputFile(const std::string& inFile)
{
	inputFile = inFile;
}

void PrintManager::setOutputFile(const std::string& outFile)
{
	outputFile = outFile;
}

void PrintManager::setNumberOfTest(const unsigned int testNumber)
{
	numberOfTests = testNumber;
	while(numberOfDigits * 10 <= testNumber)
	{
		numberOfDigits *= 10;
	}
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

void PrintManager::print()
{
	auto printerFunction = (outputFile == "")
							   ? &PrintManager::printTestToConsole
							   : &PrintManager::printTestToFile;

	for(unsigned int i = 1; i <= numberOfTests; i++)
	{
		getTestToBuffer();
		(this->*printerFunction)(i);
	}
}

void PrintManager::getTestToBuffer()
{
	testBuff.clear();
	testBuff = root.getString();
}

void PrintManager::printTestToFile(const unsigned int testNumber)
{
	std::string newTestName =
		outputFile + getFormatedTestNumber(testNumber) + ".in";
	printToFile(newTestName);
}

std::string PrintManager::getFormatedTestNumber(const unsigned int testNumber)
{
	std::string result = "";

	// Guarantee that all test numbers will have an equal number of digits
	for(unsigned int i = numberOfDigits; i > testNumber; i /= 10)
	{
		result += "0";
	}

	result += std::to_string(testNumber);
	return result;
}

void PrintManager::printTestToConsole(const unsigned int testNumber)
{
	std::cout << "\nTest number " << testNumber << ":\n\n";
	printToConsole();
}

void PrintManager::printToFile(const std::string& fileName)
{
	std::ofstream file(fileName, std::ios::trunc);
	file << testBuff;
	file.close();

	std::cout << "Output written to: " << fileName << "\n";
}

void PrintManager::printToConsole()
{
	std::cout << testBuff;
}
