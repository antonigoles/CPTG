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
    Type varType;

    std::unordered_map< std::string, Type> typeMap = {
        {"Char", Type::Char},
        {"Number", Type::Number},
        {"Float", Type::Float},
        {"String", Type::String}
    };

    enum class LexicalRange { abc, ABC, special, all };
    LexicalRange lexicalRange;

    static const std::vector<char> abcRange;
    static const std::vector<char> ABCRange;
    static const std::vector<char> specialRange;

    std::pair< int, int > range;

    int length;

    void FindParameters( const boost::optional< ptree& >& attributes );

    bool FindType( const boost::optional< ptree& >& attributes );
    void FindNumericRange( const boost::optional< ptree& >& attributes );
    void FindLexicalRange( const boost::optional< ptree& >& attributes );
    void FindLength( const boost::optional< ptree& >& attributes );

    char GenerateRandomChar();
    int GenerateRandomNumber();
    std::string GetReverseNumber( int generatedNumber );

public:
    Var();
    Var(std::shared_ptr< ptree >);

    void Print() override;
};
