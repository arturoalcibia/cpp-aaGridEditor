#include <algorithm>
#include <iostream>
#include <vector>

#include <QDebug>
#include <QtGui>
#include <QtWidgets>

#include "grid.h"
#include "pathfinding.h"

//todo: private aaaand declared on the header.
int DEFAULT_MOUSE_STATE = 0;

int MOUSE_DRAG_STATE = 1;

AAGrid::AAGrid() {

    int currentMouseState = DEFAULT_MOUSE_STATE;
    paintingState = STATES::BLANK;

    currentScene = new QGraphicsScene;
    setScene(currentScene);

    this->setRenderHint(QPainter::HighQualityAntialiasing, true);
    this->setRenderHint(QPainter::SmoothPixmapTransform, true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->scene()->setSceneRect(0, 0, WIDTH, HEIGHT);

    for (int x = currentScene->sceneRect().left(); x < currentScene->sceneRect().right(); x = x + NODE_SIZE)
    {
        for (int y = currentScene->sceneRect().top(); y < currentScene->sceneRect().bottom(); y = y + NODE_SIZE)
        {
            AAGrid::createNode(x, y, NODE_SIZE);
        }
    }

    // Once all nodes are creater we iterate over them to assign their neighbours.
    for (auto i : hashesNodeMapping)
        setNeighbours(i.second);
};

void AAGrid::createNode(int inPosX, int inPosY, int inGridSize)
{
    auto* aaNode = new AANode(inPosX, inPosY, inGridSize);
	scene()->addItem( aaNode );
    hashesNodeMapping.insert({aaNode->hashCode(), aaNode});
}

void AAGrid::setGoalNode(AANode *inNode) {

    if (inNode->getCurrentState() == STATES::GOAL)
        return;

    inNode->switchGoalNode();

    if (goalNodes.size() == 2){
        AANode* nodeToRemove = goalNodes.at( 0 );
        nodeToRemove->setCurrentState( STATES::BLANK );
        goalNodes.erase( goalNodes.begin() + 0 );
    }

    goalNodes.push_back(inNode);
}

void AAGrid::setNeighbours(AANode* inNode) {

    std::vector<AANode*> neighbourNodes;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x== 0 && y == 0)
                continue;

            int neighbourX = inNode->posX + (x * NODE_SIZE);
            int neighbourY = inNode->posY + (y * NODE_SIZE);

            std::string hashString = AANode::hashCode(neighbourX, neighbourY);
            auto nodeIterator = hashesNodeMapping.find(hashString);

            if(nodeIterator == hashesNodeMapping.end())
                continue;

            AANode* neighbourNode = nodeIterator->second;
            neighbourNodes.push_back(neighbourNode);
        }
    }

    inNode->neighbourNodes = neighbourNodes;

}

void AAGrid::mousePressEvent(QMouseEvent *event) {

    AANode * selectedNode = (AANode*)this->scene()->itemAt( this->mapToScene( event->pos() ) ,
                                                            QTransform() );

    if (selectedNode == nullptr)
        return;

    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() == Qt::NoModifier )
        {
            selectedNode->switchWallState();
            currentMouseState = MOUSE_DRAG_STATE;
            paintingState = selectedNode->getCurrentState();
        }
        else if (event->modifiers() == Qt::AltModifier )
        {
            setGoalNode( selectedNode );
        }
    }
}

void AAGrid::mouseMoveEvent(QMouseEvent *event) {
    if (currentMouseState != MOUSE_DRAG_STATE)
        return;

    AANode * selectedNode = (AANode*)this->scene()->itemAt( this->mapToScene( event->pos() ) ,
                                                            QTransform() );

    if (selectedNode == nullptr)
        return;

    if(std::find(nodesToSwitch.begin(), nodesToSwitch.end(), selectedNode) != nodesToSwitch.end())
        return;

    if (selectedNode->getCurrentState() != paintingState)
        return

    selectedNode->switchWallState();

    nodesToSwitch.push_back( selectedNode );

}

void AAGrid::mouseReleaseEvent(QMouseEvent *event) {

    currentMouseState = DEFAULT_MOUSE_STATE;

    nodesToSwitch.clear();
}

void AAGrid::resetNodes() {

    for (auto const& pair: hashesNodeMapping) {
        pair.second->reset();
    }
}

void AAGrid::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Control)
    {
        resetNodes();
    }

    if (event->key() == Qt::Key_Shift)
    {
        if (goalNodes.size() == 2)
            findPath(goalNodes.at(0), goalNodes.at(1));
    }
}
