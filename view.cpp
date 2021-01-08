//
// Created by Arturo on 2021-01-08.
//

#include <vector>

#include <QDebug>
#include <QtWidgets>

#include "view.h"
#include "grid.h"

AAView::AAView() {

    int currentMouseState = 0;
    currentScene = new QGraphicsScene;
    setScene(currentScene);

    this->setRenderHint(QPainter::HighQualityAntialiasing, true);
    this->setRenderHint(QPainter::SmoothPixmapTransform, true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->scene()->setSceneRect(0, 0, AAGrid::WIDTH, AAGrid::HEIGHT);

    prevNode = nullptr;

    for (int x = currentScene->sceneRect().left(); x <= currentScene->sceneRect().right(); x = x + AAGrid::NODE_SIZE)
    {
        for (int y = currentScene->sceneRect().top(); y <= currentScene->sceneRect().bottom(); y = y + AAGrid::NODE_SIZE)
        {
            AAView::createNode(x, y, AAGrid::NODE_SIZE);
        }
    }
};

void AAView::createNode(int inPosX, int inPosY, int inGridSize)
{
    AANode* aaNode = new AANode(inPosX, inPosY, inGridSize);
	this->scene()->addItem( aaNode );
}