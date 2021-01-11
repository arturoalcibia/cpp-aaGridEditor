#include <unordered_map>
#include <utility>

#include "grid.h"
#include "node.h"

AAGrid::AAGrid() {

}

void AAGrid::addNode(AANode &aaNode) {

    size_t hashCode = aaNode.getHashCode();

    // todo: non-default constructor might be the issue here.
    //nodeHashesMapping.insert(std::make_pair(aaNode, hashCode));
    //nodeHashesMapping[ aaNode ] = hashCode;
    //hashesNodeMapping[ hashCode ] = aaNode;
    //gridNodes.push_back( aaNode );
}

void AAGrid::setGoalNode(AANode &inNode) {

    if (inNode.getCurrentState() == STATES::GOAL)
        return;

    inNode.switchGoalNode();

    if (goalNodes.size() == 2)
    {
        AANode* nodeToRemove = goalNodes.at( 0 );
        nodeToRemove->setCurrentState( STATES::BLANK );
        goalNodes.erase( goalNodes.begin() + 0 );
    }

    goalNodes.push_back(&inNode);

}
