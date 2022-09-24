#pragma once

#include <CPTG/nodes/Seq.hpp>
namespace cptg
{

class PrintManager
{
	std::string inputFile;
	std::string outputFile;
	
	Seq root;

	std::string testBuff;

public:
	PrintManager();

	void setInputFile(const std::string& inFile);
	void setOutputFile(const std::string& outFile);

	void findNodes();
	void generateNewTest();

	void printToFile();
	void printToConsole();
};

} // namespace cptg