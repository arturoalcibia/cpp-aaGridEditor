#pragma once

#include <unordered_map>

#include <QtGui/QColor>
#include <QtWidgets/QGraphicsItem>

const enum STATES {
    BLANK,
    WALL,
    GOAL,
    EXPLORED,
    PATH
};

const std::unordered_map<STATES, QColor> MAPPED_COLORS = {
        { STATES::BLANK    , QColor(50 , 50 , 50 , 255) } ,
        { STATES::WALL     , QColor(100 , 100 , 100 , 255) } ,
        { STATES::GOAL     , QColor(250 , 70 , 70 , 255) } ,
        { STATES::EXPLORED , QColor(70 , 70 , 200 , 255) } ,
        { STATES::PATH	   , QColor(0 , 150 , 0 , 255) } ,
};

const QColor BORDER_COLOR = QColor(70, 70, 70, 255);

const QColor TEXT_COLOR = QColor(0, 200, 200, 255);

class AANode: public QGraphicsItem {

public:

    // constructor
    AANode(int inPosX, int inPosY, int inGridSize);

    // TODO: order declaring
    int posX;
    int posY;
    int gridSize;

    AANode* parentNode;

    STATES NON_EXPLORING_STATES[2] = { STATES::WALL , STATES::GOAL };

    QRectF boundingRect() const;

    STATES getCurrentState();

    void setCurrentState(STATES newState);

    int distanceTo(AANode& otherAANode);

    int getFCost();

    int getGCost();

    int getHCost();

    void setGCost(int newGCost);

    void setHCost(int newFCost);

    void switchWallState();

    void switchGoalPointState();

    void setToExplored();

    void setToPath();

    void reset();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:

    STATES currentState;
    int gCost;
    int hCost;
    int fCost;

    //todo: check if thats correct / if it needs pointers or being here.
    //todo: change to private
    QBrush qBrush;
    QPen qPen;

};