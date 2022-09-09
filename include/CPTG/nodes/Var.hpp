#pragma once

#include <memory>
#include <unordered_map>

#include "CPTG/nodes/Node.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::property_tree::ptree ptree;

class Var : public Node
{
	std::shared_ptr< ptree > varTag;

	enum class Type { Char, Number, Float, String };
	static const std::unordered_map< std::string, Type > typeMap; 
	Type varType;

	enum class LexicalRange { abc, ABC, special, all };
	static const std::unordered_map < std::string, LexicalRange > lexicalRangesMap;
	LexicalRange lexicalRange;

	static const std::vector<char> abcRange;
	static const std::vector<char> ABCRange;
	static const std::vector<char> specialRange;

	std::pair< int, int > range;
	int length;
	int power;

	void FindParameters( const ptree&attributes );

	void FindType( const ptree& attributes );
	void FindNumericRange( const ptree& attributes );
	void FindLexicalRange( const ptree& attributes );
	void FindLength( const ptree& attributes );

	int GenerateRandomNumber() const;
	std::string GenerateDecimalPlaces( int generatedNumber ) const;
	char GenerateRandomChar() const;
	LexicalRange chooseRange() const;

public:
	Var();
	Var(std::shared_ptr< ptree >);

	void Print() override;
};
