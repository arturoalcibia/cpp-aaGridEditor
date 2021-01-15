#include<windows.h>

#include <vector>
#include <algorithm>
#include <QDebug>

#include "node.h"

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

            if (newNode == currentNode)
                continue;

            if (newNode->getFCost() <= currentNode->getFCost())
                if (newNode->getHCost() <= currentNode->getHCost())
                    currentNode = newNode;
                    //todo: can be replaced w iterator.
                    currentIndex = i;
        }

        openNodes.erase(openNodes.begin() + currentIndex);
        closedNodes.push_back(currentNode);

        if (currentNode == endNode) {
            AANode* nextNode = endNode->parentNode;

            while (nextNode != nullptr)
            {
                nextNode->setToPath();
                nextNode = nextNode->parentNode;
            }
            return;
        }

        //todo: store in pointer or reference ?
        for(std::size_t i = 0; i < currentNode->neighbourNodes.size(); ++i) {

            AANode* neighbourNode = currentNode->neighbourNodes[i];

            bool hoi = neighbourNode->getCurrentState() == STATES::WALL;

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
