#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "CPTG/nodes/Node.hpp"

#include <boost/property_tree/ptree.hpp>

typedef boost::property_tree::ptree ptree;

namespace cptg
{

class Seq : public Node
{
	std::vector< std::shared_ptr< Node > > subnodes;

	int times;

public:
	Seq();

	Seq(ptree& seqTag);

	Seq(ptree& seqTag, int times);

	std::string getString() const override;

private:
	void FindSubNodes(ptree& seqTag);
};

} // namespace cptg
