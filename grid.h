#pragma once

#include <QtWidgets>

#include "node.h"

//todo: define them in the cpp ?
const int WIDTH = 1280;
const int HEIGHT = 720;
const int NODE_SIZE = 80;

class AAGrid : public QGraphicsView {

public:

    int currentMouseState;
    STATES paintingState;

    std::vector<AANode*> nodesToSwitch;

    explicit AAGrid();

    //AAPathfinding* aaPathfinding;

    void resetNodes();

    QGraphicsScene* currentScene;
    std::unordered_map<size_t, AANode*> hashesNodeMapping;
    std::vector<AANode*> goalNodes;
    void setGoalNode(AANode *inNode);
    std::vector<AANode*> getNeighbours(AANode* inNode);

    void createNode(int inPosX, int inPosY, int inGridSize);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
