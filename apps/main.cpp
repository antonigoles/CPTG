#include <iostream>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "CPTG/nodes/Seq.hpp"
#include "CPTG/nodes/Var.hpp"

typedef boost::property_tree::ptree ptree;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "You must specify a file to parse" << std::endl;
        return 1;
    }

    Seq root;
    ptree tree;
    boost::property_tree::read_xml(argv[1], tree);

    tree.get_child("test");

    // Iterate through base tags
    BOOST_FOREACH(ptree::value_type& child, tree)
    {   
        if(child.first == "test")
        {
            root = Seq(
                std::make_shared< ptree >(child.second),
                1
            );
        }
    }

    root.FindSubNodes();
    root.Print();
}
