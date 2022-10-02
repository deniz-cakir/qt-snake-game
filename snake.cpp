#include "snake.h"
#include "Config.h"
#include <QKeyEvent>

Snake::Snake()
{
    setFlag(QGraphicsItem::ItemIsFocusable);

    currentDirection = Direction::left;

    int sizeOfArea = elementSize * elementCount;
    QPoint headP = QPoint (sizeOfArea / 2, sizeOfArea / 2);
    QPoint tailP = QPoint (headP.x() + elementSize * snakeLen, headP.y());
    points.append(headP);
    points.append(tailP);
    poly = QPolygon();
}

Snake::~Snake()
{

}

QPainterPath Snake::shape () const
{
    poly.append(points [0]);
    poly.append(points [1]);
    path.addPolygon(poly);
    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen = QPen();
    pen.setWidth(snakeSize);
    pen.setBrush(elementBrush);

    painter->setPen(pen);
    painter->drawPath(path);
}


bool Snake::isDirectionPerpendicular(Direction dir1)
{
    switch (dir1)
    {
    case Direction::bottom:
        if (currentDirection == Direction::top || currentDirection == Direction::bottom) return false;
        break;
    case Direction::left:
        if (currentDirection == Direction::right || currentDirection == Direction::left) return false;
        break;
    case Direction::right:
        if (currentDirection == Direction::left || currentDirection == Direction::right) return false;
        break;
    case Direction::top:
        if (currentDirection == Direction::bottom || currentDirection == Direction::top) return false;
        break;
    }
    return true;
}


void Snake::keyPressEvent(QKeyEvent *event)
{
    if (points.first() == points[1]) return;
    switch (event->key())
    {
    case Qt::Key_Left:
        if (isDirectionPerpendicular(Direction::left))
        {
            currentDirection = Direction::left;
            changeDirection();
        }
        break;
    case Qt::Key_Up:
        if (isDirectionPerpendicular(Direction::top))
        {
            currentDirection = Direction::top;
            changeDirection();
        }
        break;
    case Qt::Key_Down:
        if (isDirectionPerpendicular(Direction::bottom))
        {
            currentDirection = Direction::bottom;
            changeDirection();
        }
        break;
     case Qt::Key_Right:
        if (isDirectionPerpendicular(Direction::right))
        {
            currentDirection = Direction::right;
            changeDirection();
        }
        break;
    }
}

void Snake::advanceSnake ()
{
    prepareGeometryChange();
    advanceHead();
    clearPoints();
    if (!didEatTheCake) advanceTail();
    updatePoly();
    didEatTheCake = false;

    QPainterPath path;
    path.addPolygon(poly);
    this->path = path;
}

void Snake::cakeEaten()
{
    didEatTheCake = true;
    qInfo () << didEatTheCake;
}

bool Snake::getCakeStat()
{
    return didEatTheCake;
}


void Snake::changeDirection()
{
    QPoint newHeadP = QPoint(points[0]);
    points.insert(1, newHeadP);
}

void Snake::advanceHead()
{
    advancePoint(points.first());
}

void Snake::advanceTail()
{

    if (points.length() > 2)
    {
        vectorAdvance(points.last(), points[points.size() - 2]);
    }
    if (points.length() == 2)
    {
        advancePoint(points.last());
    }
//    calculateLen();
//    if (snakeLen > 5)
//    {
//        vectorAdvance(points.last(), points[size - 1]);
//        qInfo () << snakeLen;
//    }
}

void Snake::advancePoint(QPoint &p)
{
    if (currentDirection == Direction::left)
    {
        p.setX(p.x() - elementSize);
    }
    if (currentDirection == Direction::right)
    {
        p.setX(p.x() + elementSize);
    }
    if (currentDirection == Direction::top)
    {
        p.setY(p.y() - elementSize);
    }
    if (currentDirection == Direction::bottom)
    {
        p.setY(p.y() + elementSize);
    }
}

void Snake::vectorAdvance(QPoint &p1, QPoint &p2)
{
    QPoint dir = p1 - p2;

    int dx = dir.x();
    int dy = dir.y();

    if (dx > 0)
    {
        p1.setX(p1.x() - elementSize);
    }
    else if (dx < 0)
    {
        p1.setX(p1.x() + elementSize);
    }
    else if (dy > 0)
    {
        p1.setY(p1.y() - elementSize);
    }
    else if (dy < 0)
    {
        p1.setY(p1.y() + elementSize);
    }
}

void Snake::updatePoly()
{
    QPolygon newPoly;
    foreach(QPoint p, points)
    {
        newPoly.append(p);
    }
    poly = newPoly;
}

void Snake::calculateLen()
{
    int totalLen = 0;
    for (int i = 0; i < points.length() - 1; i++)
    {
        QPoint p = points[i] - points[i + 1];
        int l1 = abs (p.x()) + abs (p.y());
        totalLen = totalLen + l1 / elementSize;
    }
    snakeLen = totalLen;
}

void Snake::clearPoints()
{
    QPoint p = points.last() - points[points.size() - 2];

    if (p.isNull())
    {
        points.removeLast();
    }
}


bool Snake::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    QRectF otherItem = QRectF(other->mapRectFromItem(other, other->boundingRect()));
    QPointF topLeft = otherItem.topLeft();
    QPointF bottomLeft = otherItem.bottomLeft();
    QPointF bottomRight = otherItem.bottomRight();
    QPointF topRight = otherItem.topRight();

    QLineF line1 = QLineF (topLeft, bottomLeft);
    QLineF line2 = QLineF (bottomLeft, bottomRight);
    QLineF line3 = QLineF (bottomRight, topRight);
    QLineF line4 = QLineF (topRight, topLeft);

    QList <QLineF> lines = {line1, line2, line3, line4};

    foreach(QLineF line, lines)
    {
        if (line.intersects(QLineF(poly.point(0), poly.point(1))) == QLineF::BoundedIntersection) return true;
    }
    return false;
}
















