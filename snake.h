#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QPainter>
#include "Config.h"

class Snake : public QGraphicsPathItem
{
public:
    Snake();
    ~Snake();

    QPainterPath shape () const override;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool collidesWithItem (const QGraphicsItem* other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
    void advanceSnake();
    void cakeEaten();
    bool getCakeStat ();
private:

    bool isDirectionPerpendicular (Direction newDir);
    void changeDirection();

    void advanceHead();
    void advanceTail();
    void advancePoint(QPoint &p);
    void vectorAdvance (QPoint& p1, QPoint& p2);
    void updatePoly();
    void calculateLen();
    void clearPoints();

    Direction currentDirection;
    int snakeLen = 5;
    bool didEatTheCake = false;

    mutable QList <QPoint> points;
    mutable QPainterPath path;
    mutable QPolygon poly;

protected:
    virtual void keyPressEvent (QKeyEvent* event) override;

};

#endif // SNAKE_H
