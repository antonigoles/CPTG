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
	std::shared_ptr< ptree > seqTag;
	std::vector< std::shared_ptr< Node > > subnodes;

	int times;

public:
	Seq();

	Seq(std::shared_ptr< ptree > seqTag);

	Seq(std::shared_ptr< ptree > seqTag, int times);

	std::string getString() const override;

private:
	void FindSubNodes();
};

} // namespace cptg
