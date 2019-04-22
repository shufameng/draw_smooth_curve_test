#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QGraphicsPolygonItem>

class PolygonItem : public QGraphicsPolygonItem
{
public:
    explicit PolygonItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // POLYGONITEM_H
