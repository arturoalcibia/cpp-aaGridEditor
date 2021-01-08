#pragma once

#include <QtWidgets>

#include "node.h";

class AAView : public QGraphicsView {
public:
    const int MOUSE_DRAG_STATE = 0;

    explicit AAView();

    QGraphicsScene* currentScene;

    AANode* prevNode;

    void createNode(int inPosX, int inPosY, int inGridSize);
};