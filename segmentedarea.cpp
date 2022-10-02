#include "segmentedarea.h"
#include "Config.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

SegmentedArea::SegmentedArea()
{

}

SegmentedArea::~SegmentedArea()
{

}

QRectF SegmentedArea::boundingRect() const
{
    int sizeOfArea = elementSize * elementCount;

    QPoint p1 = QPoint (0, 0);
    QPoint p2 = QPoint (0, sizeOfArea);
    QPoint p3 = QPoint (sizeOfArea , sizeOfArea);
    QPoint p4 = QPoint (sizeOfArea , 0);

    QRectF rect = QRectF (p1, p3);

    return rect;
}

void SegmentedArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = QPen();
    pen.setBrush(elementBrush);
    pen.setWidth(elementSize);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
}

















