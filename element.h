#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QGraphicsItem>

class Element : public QGraphicsItem

{
public:
    explicit Element(int coorX, int coorY);
    ~Element();

    QRectF boundingRect() const override;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;

    QPoint getElementPoint();

signals:

private:
    QRectF element;
    int coorX;
    int coorY;

};

#endif // ELEMENT_H
