#include "CPTG/printers/PrintManager.hpp"

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "You must specify a file to parse" << std::endl;
		return 1;
	}

	cptg::PrintManager printer;
	if(argc == 2)
	{
		printer = cptg::PrintManager(argv[1]);
	}
	else
	{
		printer = cptg::PrintManager(argv[1], argv[2]);
	}
	
	printer.findNodes();
	printer.printToConsole();
	printer.printToFile();
}
