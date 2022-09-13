#pragma once
#include <iostream>

namespace cptg
{

// Abstract class for all Nodes
class Node
{
public:
	virtual ~Node() = default;

	virtual std::string getString() const = 0;

	friend std::ostream& operator<<(std::ostream& od, const Node& node)
	{
		od << node.getString();
		return od;
	}
};

} // namespace cptg
