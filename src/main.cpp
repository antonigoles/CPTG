#include <iostream>

#include "nodes/Seq.hpp"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

int main()
{
    Seq root;
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("example1.xml", tree);

    tree.get_child("test");

    // Iterate through base tags
    BOOST_FOREACH(boost::property_tree::ptree::value_type& child, tree)
    {   
        if(child.first == "test")
        {
            root = Seq(
                std::make_shared< boost::property_tree::ptree >(child.second),
                1
                );
        }
    }

    root.FindSubNodes();
    root.Print();
}