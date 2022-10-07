#include "CPTG/nodes/NodesDecorator.hpp"

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "You must specify a file to parse" << std::endl;
		return 0;
	}

	cptg::PrintManager printer;
	printer.setInputFile(argv[1]);

	if(argc >= 3)
	{
		printer.setOutputFile(argv[2]);
	}

	if(argc == 4)
	{
		printer.setNumberOfTest(std::atoi(argv[3]));
	}

	printer.findNodes();
	printer.print();
}
