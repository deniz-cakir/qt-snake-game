#include "element.h"
#include "Config.h"
#include <QPainter>

Element::Element(int coorX, int coorY) : coorX(coorX), coorY(coorY)
{
}

Element::~Element()
{

}

QRectF Element::boundingRect() const
{
    QRectF rect = QRectF(QPointF(coorX, coorY), QSizeF (snakeSize, snakeSize));
    rect.moveCenter(QPointF (coorX, coorY));
    return rect;
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(elementBrush);
    painter->drawRoundedRect(boundingRect(), elementRadius, elementRadius);
}

QPoint Element::getElementPoint()
{
    QPoint p = QPoint (coorX, coorY);
    return p;
}
