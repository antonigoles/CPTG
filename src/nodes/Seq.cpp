#include "Seq.hpp"

// Creates a shared pointer to nodeType object
#define SharedNode(nodeType, propTree) \
    std::make_shared<nodeType>( \
        nodeType(std::make_shared<boost::property_tree::ptree>(propTree)) \
    )

Seq::Seq() : times(1) { }

Seq::Seq(std::shared_ptr< boost::property_tree::ptree > sT) : 
    seqTag(sT),
    times(seqTag->get<int>("<xmlattr>.times"))
{
    FindSubNodes();
}

Seq::Seq(std::shared_ptr< boost::property_tree::ptree > sT, int times) : 
    seqTag(sT),
    times(times) { }

void Seq::FindSubNodes()
{
    BOOST_FOREACH(boost::property_tree::ptree::value_type& child, (*seqTag))
    {        
        if(child.first == "seq")
        {
            subnodes.push_back( SharedNode(Seq, child.second) );
        }

        if(child.first == "const")
        {
            subnodes.push_back( SharedNode(Const, child.second) );
        }

        if(child.first == "br")
        {
            subnodes.push_back( std::make_shared<Br>() );
        }
    }
}

void Seq::Print()
{
    for(int i = 0; i < times; i++)
    {
        for(auto& node : subnodes)
        {
            node->Print();
        }
    }
}