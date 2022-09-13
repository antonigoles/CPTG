#pragma once

#include <memory>

#include "CPTG/nodes/Node.hpp"

#include <boost/property_tree/ptree.hpp>

typedef boost::property_tree::ptree ptree;

namespace cptg
{

class Const : public Node
{
	std::string value;

public:
	Const();
	Const(std::shared_ptr< ptree >);

	std::string getString() const override;
};

} // namespace cptg
