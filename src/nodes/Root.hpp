#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Node.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class Root : public Node
{
    std::shared_ptr< boost::property_tree::ptree > rootTag;
    std::vector< std::shared_ptr< Node > > subnodes;

public:
    Root();
    void FindSubNodes() override;
    void Print() override;

    void setRootTag(std::shared_ptr< boost::property_tree::ptree > rootTag);
};