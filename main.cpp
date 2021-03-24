#include <iostream>
#include <string>
#include <vector>


#include <QtWidgets>
#include <QDebug>

#include "grid.h"
#include "pathfinding.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    AAGrid aaView;

    aaView.show();

    /*
    // test code!
    int posY[8] = {100, 100, 100, 100, 300, 300, 300, 300};
    int posX[8] = {0, 100, 200, 300, 0, 100, 200, 300};

    int GoalNodesY[2] = {0, 400};
    int GoalNodesX[2] = {0, 0};

    int arraySize = sizeof(posX)/sizeof(posX[0]);

    for (int i = 0; i < arraySize; ++i) {
        std::string hashString = AANode::hashCode(posX[i], posY[i]);
        auto nodeIterator = aaView.hashesNodeMapping.find(hashString);

        AANode* aaNode = nodeIterator->second;
        aaNode->switchWallState();

    }

    int goalArraySize = sizeof(GoalNodesX)/sizeof(GoalNodesX[0]);

    std::vector<AANode*> goalNodes;
    goalNodes.resize(2);

    for (int i = 0; i < goalArraySize; ++i) {
        std::string hashString = AANode::hashCode(GoalNodesX[i], GoalNodesY[i]);
        auto nodeIterator = aaView.hashesNodeMapping.find(hashString);
        AANode* aaNode = nodeIterator->second;
        aaNode->switchGoalNode();
        goalNodes[i] = aaNode;

    }

    findPath(goalNodes.at(0), goalNodes.at(1));
    */

    return a.exec();
}
