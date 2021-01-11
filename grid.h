#pragma once

#include <string>
#include <vector>

#include "node.h"

class AAGrid {
    public:

    explicit AAGrid();

    std::unordered_map<AANode, size_t, _NodeHasher> nodeHashesMapping;
    //std::unordered_map<size_t, AANode> hashesNodeMapping;
    std::vector<AANode*> gridNodes;
    std::vector<AANode*> goalNodes;

    void addNode(AANode& aaNode);
    AANode getNeighbours(AANode& inNode);
    void reset();
    void setGoalNode(AANode& inNode);

};