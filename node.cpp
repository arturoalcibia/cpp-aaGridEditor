//
// Created by Arturo on 2021-01-08.
//

#include <QtCore>
#include <QtGui>

#include "node.h"

/*
AANode& createAANode(int posX, int posY, int gridSize)
{
	return AANode(posX, posY, gridSize);
}
*/

AANode::AANode(int inPosX, int inPosY, int inGridSize) : QGraphicsItem() {

    //TODO: change to private and add setters and getters
    posX = inPosX;
    posY = inPosY;
    gridSize = inGridSize;
    gCost = 0;
    hCost = 0;
    fCost = 0;

    qDebug("hoi is %d", gridSize);

    parentNode = nullptr;

    currentState = STATES::BLANK;

    this->setPos(posX, posY);

    qBrush = QBrush();
    qBrush.setStyle(Qt::SolidPattern);

    qBrush.setColor( MAPPED_COLORS.at(STATES::BLANK) );

    qPen = QPen();
    qPen.setStyle(Qt::SolidLine);
    qPen.setWidth(1);
    //qPen.setColor( &BORDER_COLOR );
};

QRectF AANode::boundingRect() const
{
    return QRectF(0, 0, gridSize, gridSize);
}

int AANode::distanceTo(AANode& otherAANode){
    int xDistance = abs(this->posX - otherAANode.posX);
    int yDistance = abs(this->posY - otherAANode.posY);

    if (xDistance > yDistance)
        return (int)( 0.14 * yDistance + ( ( xDistance - yDistance ) * 0.10 ) );

    return (int)( 0.14 * xDistance + ( ( yDistance - xDistance ) * 0.10 ) );
}

void AANode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    qBrush.setColor( MAPPED_COLORS.at(currentState) );
    painter->setBrush(qBrush);
    painter->setPen(qPen);
    painter->drawRect(0, 0, gridSize, gridSize);
}

STATES AANode::getCurrentState()
{
    return currentState;
}

int AANode::getFCost()
{
    return (gCost + hCost);
}

int AANode::getGCost()
{
    return gCost;
}

int AANode::getHCost()
{
    return hCost;
}

void AANode::setCurrentState(STATES newState)
{
    currentState = newState;

    AANode::update();
}

void AANode::setGCost(int newGCost)
{
    gCost = newGCost;
}

void AANode::setHCost(int newHCost)
{
    hCost = newHCost;
}

void AANode::setToExplored() {
    if (std::find(std::begin(NON_EXPLORING_STATES ),
                  std::end(NON_EXPLORING_STATES),
                  currentState ) != std::end(NON_EXPLORING_STATES))
        this->setCurrentState(STATES::EXPLORED);
}

void AANode::setToPath() {
    if (this->getCurrentState() != STATES::GOAL)
        this->setCurrentState(STATES::PATH);
}

void AANode::switchWallState() {
    if (this->getCurrentState() == STATES::BLANK)
        this->setCurrentState(STATES::WALL);
    else if (currentState == STATES::WALL)
        this->setCurrentState(STATES::BLANK);
}

void AANode::switchGoalPointState() {
    if (this->getCurrentState() == STATES::GOAL) {
        this->setCurrentState(STATES::BLANK);
        return;
    }
    this->setCurrentState(STATES::GOAL);
}

void AANode::reset() {
    if (std::find(std::begin(NON_EXPLORING_STATES ),
                  std::end(NON_EXPLORING_STATES),
                  this->getCurrentState() ) != std::end(NON_EXPLORING_STATES))
        this->setCurrentState(STATES::BLANK);

    this->setGCost(0);
    this->setHCost(0);
    this->parentNode = nullptr;
}
