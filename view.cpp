//
// Created by Arturo on 2021-01-08.
//

#include <algorithm>
#include <vector>

#include <QDebug>
#include <QtGui>
#include <QtWidgets>

#include "view.h"
#include "grid.h"

//todo: private aaaand declared on the header.
int DEFAULT_MOUSE_STATE = 0;

int MOUSE_DRAG_STATE = 1;

AAView::AAView() {

    int currentMouseState = DEFAULT_MOUSE_STATE;
    paintingState = STATES::BLANK;

    currentScene = new QGraphicsScene;
    setScene(currentScene);

    this->setRenderHint(QPainter::HighQualityAntialiasing, true);
    this->setRenderHint(QPainter::SmoothPixmapTransform, true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->scene()->setSceneRect(0, 0, WIDTH, HEIGHT);

    for (int x = currentScene->sceneRect().left(); x <= currentScene->sceneRect().right(); x = x + NODE_SIZE)
    {
        for (int y = currentScene->sceneRect().top(); y <= currentScene->sceneRect().bottom(); y = y + NODE_SIZE)
        {
            AAView::createNode(x, y, NODE_SIZE);
        }
    }

    aaGrid = new AAGrid;

};

void AAView::createNode(int inPosX, int inPosY, int inGridSize)
{
    AANode* aaNode = new AANode(inPosX, inPosY, inGridSize);
	this->scene()->addItem( aaNode );
}

void AAView::mousePressEvent(QMouseEvent *event) {

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
            aaGrid->setGoalNode( *selectedNode );
        }
    }
}

void AAView::mouseMoveEvent(QMouseEvent *event) {
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

void AAView::mouseReleaseEvent(QMouseEvent *event) {

    currentMouseState = DEFAULT_MOUSE_STATE;

    nodesToSwitch.clear();
}


