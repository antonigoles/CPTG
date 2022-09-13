#pragma once

#include "CPTG/nodes/Node.hpp"

namespace cptg
{

class Br : public Node
{
public:
	Br();

	std::string getString() const override;
};

} // namespace cptg
