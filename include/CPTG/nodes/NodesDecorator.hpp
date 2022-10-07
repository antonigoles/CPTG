#pragma once

#include <CPTG/nodes/Seq.hpp>
namespace cptg
{

class PrintManager
{
	std::string inputFile;
	std::string outputFile;
	
	// By default, generate only one test
	unsigned int numberOfTests = 1;
	unsigned int numberOfDigits = 1;
	
	Seq root;

	std::string testBuff;

public:
	PrintManager();

	void setInputFile(const std::string& inFile);
	void setOutputFile(const std::string& outFile);
	void setNumberOfTest(const unsigned int testNumber);

	
	void findNodes();
	void print();

private:
	void getTestToBuffer();

	void printTestToFile(const unsigned int testNumber);
	std::string getFormatedTestNumber(const unsigned int testNumber);
	
	void printTestToConsole(const unsigned int testNumber);
	
	void printToFile(const std::string& fileName);
	void printToConsole();
};

} // namespace cptg