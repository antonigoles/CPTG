#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Node.hpp"
#include "Const.hpp"
#include "Br.hpp"

#include <boost/optional/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class Seq : public Node
{
    std::shared_ptr< boost::property_tree::ptree > seqTag;
    std::vector< std::shared_ptr< Node > > subnodes;

    int times;

public:
    Seq();
    // Finds the times attribute from ptree
    Seq( std::shared_ptr< boost::property_tree::ptree > );
    // The times variable is provided by on construction
    Seq( std::shared_ptr< boost::property_tree::ptree >, int );

    void FindSubNodes();
    void Print() override;
};