
/* Abstract class for all Nodes
 * Find nodes willl find subnodes (if possible)
 * Print will output itself and all subnodes */
class Node
{
public:
    virtual void FindSubNodes() = 0;
    virtual void Print() = 0;
};
