#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "Node.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class Var : public Node
{
    std::shared_ptr< boost::property_tree::ptree > varTag;

    enum class Type { Char, Number, Float, String };
    Type varType;

    std::unordered_map< std::string, Type> typeMap = {
        {"Char", Type::Char},
        {"Number", Type::Number},
        {"Float", Type::Float},
        {"String", Type::String}
    };

    std::pair< int, int > range;

    void FindNumericRange();
    void FindLexicalRange();
    void FindLength();

public:
    Var();
    Var( std::shared_ptr< boost::property_tree::ptree > );

    void Print() override;
};