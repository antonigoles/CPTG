#pragma once

#include "CPTG/nodes/Node.hpp"

class Br : public Node
{
public:
    Br();

    std::string getString() const override;
};