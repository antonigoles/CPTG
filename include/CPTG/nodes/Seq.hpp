#pragma once

#include <vector>
#include <memory>

#include "CPTG/nodes/Node.hpp"

#include <boost/property_tree/ptree.hpp>

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