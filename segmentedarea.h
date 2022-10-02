#ifndef SEGMENTEDAREA_H
#define SEGMENTEDAREA_H

#include <QGraphicsItem>

class SegmentedArea : public QGraphicsPathItem
{
public:
    SegmentedArea();
    ~SegmentedArea();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:


};

#endif // SEGMENTEDAREA_H
