#pragma once

#include <iostream>
#include <memory>

#include "Node.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class Const : public Node
{
    std::string value;

public:
    Const();
    Const( std::shared_ptr< boost::property_tree::ptree > );

    void Print() override;
};