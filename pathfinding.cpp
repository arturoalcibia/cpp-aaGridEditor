#include<windows.h>

#include <vector>
#include <algorithm>
#include <QDebug>

#include "node.h"

//todo: preallocate size on closed/openNodes

void findPath(AANode* inStartNode, AANode* inEndNode) {

    //todo: move to header ?
    AANode* startNode = inStartNode;
    AANode* endNode = inEndNode;

    std::vector<AANode*> openNodes;
    std::vector<AANode*> closedNodes;

    openNodes.push_back( startNode );

    while ( !openNodes.empty() ) {
        AANode *currentNode = openNodes.at(0);

        int currentIndex = 0;

        for (std::size_t i = 0; i < openNodes.size(); ++i) {
            AANode *newNode = openNodes[i];

            //todo: can be replaced w iterator.
            if ( newNode->getFCost() <= currentNode->getFCost() || newNode->getHCost() <= currentNode->getHCost() )
            {
                currentNode = newNode;
                currentIndex = i;
            }
        }

        openNodes.erase(openNodes.begin() + currentIndex);
        closedNodes.push_back(currentNode);

        if (currentNode == endNode) {
            AANode* nextNode = endNode->parentNode;

            while (nextNode != NULL)
            {
                nextNode->setToPath();
                nextNode = nextNode->parentNode;
            }
            return;
        }

        for(std::size_t i = 0; i < currentNode->neighbourNodes.size(); ++i) {

            AANode* neighbourNode = currentNode->neighbourNodes[i];

            if (neighbourNode->getCurrentState() == STATES::WALL)
                continue;

            neighbourNode->setToExplored();

            if (std::find(closedNodes.begin(), closedNodes.end(), neighbourNode) != closedNodes.end())
                continue;

            int newCostToNeighbour = currentNode->getGCost() + currentNode->distanceTo( neighbourNode );

            if ( newCostToNeighbour < neighbourNode->getGCost() ||
                 (std::find(openNodes.begin(), openNodes.end(), neighbourNode) == openNodes.end())){

                neighbourNode->setGCost( newCostToNeighbour );
                neighbourNode->setHCost( neighbourNode->distanceTo( endNode ) );
                neighbourNode->parentNode = currentNode;

                if (std::find(openNodes.begin(), openNodes.end(), neighbourNode) == openNodes.end())
                    openNodes.push_back( neighbourNode );
            }
        }
    }
};
