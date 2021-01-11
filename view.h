#pragma once

#include <QtWidgets>

#include "node.h"
#include "grid.h"

//todo: define them in the cpp ?
const int WIDTH = 1280;
const int HEIGHT = 720;
const int NODE_SIZE = 20;

class AAView : public QGraphicsView {
public:

    int currentMouseState;
    STATES paintingState;

    std::vector<AANode*> nodesToSwitch;

    explicit AAView();

    QGraphicsScene* currentScene;
    AAGrid* aaGrid;

    void createNode(int inPosX, int inPosY, int inGridSize);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};
