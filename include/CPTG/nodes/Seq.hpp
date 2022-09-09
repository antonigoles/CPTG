#pragma once

#include <vector>
#include <memory>

#include "CPTG/nodes/Node.hpp"

#include <boost/property_tree/ptree.hpp>

typedef boost::property_tree::ptree ptree;

class Seq : public Node
{
	std::shared_ptr< ptree > seqTag;
	std::vector< std::shared_ptr< Node > > subnodes;

	int times;

public:
	Seq();
	
	Seq( std::shared_ptr< ptree > );
	
	Seq( std::shared_ptr< ptree >, int );

	void FindSubNodes();
	std::string getString() const override;
};