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
	PrintManager(std::string inputFile);
	PrintManager(std::string inputFile, std::string outputFile);

	void findNodes();
	void generateNewTest();

	void printToFile();
	void printToConsole();
};

} // namespace cptg