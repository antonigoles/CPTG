#pragma once

// Abstract class for all Nodes
class Node
{
public:
	virtual ~Node() = default;

	// Prints the contents of a node to the standard output
	virtual void Print() const = 0;

};
