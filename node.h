#ifndef INCLUDE_NODE
#define INCLUDE_NODE

#include <unordered_map>
#include <string>

#include <QtGui>
#include <QtWidgets/QGraphicsItem>

enum STATES {
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

const STATES NON_EXPLORING_STATES[2] = { STATES::WALL , STATES::GOAL };

class AANode: public QGraphicsItem {

public:

    // constructor
    AANode(int inPosX, int inPosY, int inGridSize);

    // TODO: order declaring
    int posX;
    int posY;
    int gridSize;

    AANode* parentNode;
    std::vector<AANode*> neighbourNodes;

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

    void switchGoalNode();

    void setToExplored();

    void setToPath();

    void reset();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    std::string hashCode();

    static std::string hashCode(int inPosX, int inPosY);

private:

    STATES currentState;
    int gCost;
    int hCost;
    int fCost;
    QBrush qBrush;
    QPen qPen;

};