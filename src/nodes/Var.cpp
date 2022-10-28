#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "CPTG/nodes/Var.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace cptg;

Var::Var() : varType(Type::Number), range({0, 9}) { }

Var::Var(ptree& varTag)
{
	srand((int)time(NULL));
	auto attributes = varTag.get_child_optional("<xmlattr>");

	if(attributes != boost::none)
	{
		FindParameters(attributes.get());
	}
	else
	{
		varType = Type::Number;
		range = {0, 9};
	}
}

void Var::FindParameters(const ptree& attributes)
{
	FindType(attributes);

	const bool bIsNumeric = (varType == Type::Number || varType == Type::Float);
	if(bIsNumeric)
	{
		FindNumericRange(attributes);
	}
	else
	{
		FindLexicalRange(attributes);
	}

	if(varType == Type::String || varType == Type::Float)
	{
		FindLength(attributes);
		power = (int)pow(10, length);
	}
	else if(varType == Type::Char)
	{
		length = 1;
	}
}

void Var::FindType(const ptree& attributes)
{
	if(attributes.count("type") == 0)
	{
		// It is permited to not specify type
		varType = Type::Number;
		return;
	}

	const auto type = attributes.get< std::string >("type");
	if(typeMap.find(type) != typeMap.end())
	{
		varType = typeMap.at(type);
	}
	else
	{
		std::cerr
			<< "Error: Unknown variable type provided\nUsing default instead"
			<< std::endl;
	}
}

void Var::FindNumericRange(const ptree& attributes)
{
	if(!attributes.count("range"))
	{
		// It is permited to not specify range
		range = {0, 9};
		return;
	}

	auto rangeStr = attributes.get< std::string >("range");
	std::vector< std::string > splitRange;

	boost::split(splitRange, rangeStr, boost::is_any_of(":"));

	const int rangeStart = std::stoi(splitRange[0]);
	const int rangeEnd = std::stoi(splitRange[1]);
	if(rangeStart < rangeEnd)
	{
		range = {rangeStart, rangeEnd};
	}
	else
	{
		std::cerr << "Error: First range element is larger than the second "
					 "one\nUsing default instead"
				  << std::endl;
		range = {0, 9};
	}
}

void Var::FindLexicalRange(const ptree& attributes)
{
	if(!attributes.count("range"))
	{
		// It is permited to not specify range
		lexicalRange = LexicalRange::abc;
		return;
	}

	const auto rangeKey = attributes.get< std::string >("range");
	if(lexicalRangesMap.find(rangeKey) != lexicalRangesMap.end())
	{
		lexicalRange = lexicalRangesMap.at(rangeKey);
	}
	else
	{
		std::cerr << "Error: Unknown lexical range\nUsed default instead"
				  << std::endl;
		lexicalRange = LexicalRange::abc;
	}
}

void Var::FindLength(const ptree& attributes)
{
	if(!attributes.count("length"))
	{
		// It is permited to not specify length
		length = 3;
		return;
	}

	const int readLength = attributes.get< int >("length");
	if(readLength >= 0)
	{
		length = readLength;
	}
	else
	{
		std::cerr
			<< "Error: Length must be positive\nUsing default length instead"
			<< std::endl;
		length = 3;
	}
}

std::string Var::getString() const
{
	std::string result = "";

	const bool bIsNumeric = (varType == Type::Number || varType == Type::Float);
	if(bIsNumeric)
	{
		const int randomNumber = GenerateRandomNumber();
		result += std::to_string(randomNumber);

		if(varType == Type::Float)
		{
			result += GenerateDecimalPlaces(randomNumber);
		}
	}
	else
	{
		for(int i = 0; i < length; i++)
		{
			result += GenerateRandomChar();
		}
	}

	return result + " ";
}

int Var::GenerateRandomNumber() const
{
	return rand() % (range.second - range.first + 1) + range.first;
}

std::string Var::GenerateDecimalPlaces(int generatedNumber) const
{
	// Avoid exceeding provided range
	if(generatedNumber == range.second)
	{
		return "";
	}

	const int decPlacesNumbers = rand() % power;

	if(decPlacesNumbers == 0)
	{
		return "";
	}

	std::string decPlaces = std::to_string(decPlacesNumbers);
	std::reverse(decPlaces.begin(), decPlaces.end());

	return "." + decPlaces;
}

char Var::GenerateRandomChar() const
{
	LexicalRange typeToGenerate;
	if(lexicalRange == LexicalRange::all)
	{
		typeToGenerate = chooseRange();
	}
	else
	{
		typeToGenerate = lexicalRange;
	}


	if(lexicalRange == LexicalRange::abc)
	{
		return abcRange[rand() % abcRange.size()];
	}
	else if(lexicalRange == LexicalRange::ABC)
	{
		return ABCRange[rand() % ABCRange.size()];
	}
	else
	{
		return specialRange[rand() % specialRange.size()];
	}
}

Var::LexicalRange Var::chooseRange() const
{
	const int sumOfChars =
		abcRange.size() + ABCRange.size() + specialRange.size();
	const int charToUse = rand() % sumOfChars;

	if(charToUse < abcRange.size())
	{
		return LexicalRange::abc;
	}
	else if(charToUse - abcRange.size() < ABCRange.size())
	{
		return LexicalRange::ABC;
	}
	else
	{
		return LexicalRange::special;
	}
}

const std::vector< char > Var::abcRange = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const std::vector< char > Var::ABCRange = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const std::vector< char > Var::specialRange = {
	'!', '@',  '#', '$', '%', '^', '&', '*', '(',  ')', '-',
	'_', '+',  '=', '{', '}', '[', ']', '|', '\\', ':', ';',
	'"', '\'', '<', ',', '>', '.', '?', '/', '~',  '|'};

const std::unordered_map< std::string, Var::Type > Var::typeMap = {
	{"Char", Type::Char},
	{"Number", Type::Number},
	{"Float", Type::Float},
	{"String", Type::String}};

const std::unordered_map< std::string, Var::LexicalRange >
	Var::lexicalRangesMap = {
		{"abc", LexicalRange::abc},
		{"ABC", LexicalRange::ABC},
		{"special", LexicalRange::special},
		{"all", LexicalRange::all}};
