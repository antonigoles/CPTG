#include "Seq.hpp"

Seq::Seq() { }

Seq::Seq(std::shared_ptr< boost::property_tree::ptree > sT) : 
    seqTag(sT),
    times(seqTag->get<int>("<xmlattr>.times"))
{

}

Seq::Seq(std::shared_ptr< boost::property_tree::ptree > sT, int times) : 
    seqTag(sT),
    times(times)
{

}

void Seq::FindSubNodes()
{
    BOOST_FOREACH(boost::property_tree::ptree::value_type& child, (*seqTag))
    {
        std::cout << child.first << '\n';
    }
}

void Seq::Print()
{

}