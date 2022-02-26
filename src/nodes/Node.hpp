#pragma once

/* Abstract class for all Nodes
 * Find nodes willl find subnodes (if possible)
 * Print will output itself and all subnodes */
class Node
{
public:
    virtual ~Node() = default;
    virtual void Print() = 0;

};
