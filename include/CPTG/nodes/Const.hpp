#pragma once

#include <memory>

#include "CPTG/nodes/Node.hpp"

#include <boost/property_tree/ptree.hpp>

class Const : public Node
{
    std::string value;

public:
    Const();
    Const( std::shared_ptr< boost::property_tree::ptree > );

    void Print() override;
};