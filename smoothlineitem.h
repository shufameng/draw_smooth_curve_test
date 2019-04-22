#ifndef SMOOTHLINEITEM_H
#define SMOOTHLINEITEM_H

#include "basicdrawitem.h"

class SmoothLineItem : public BasicDrawItem
{
public:
    explicit SmoothLineItem(QGraphicsItem *parent = 0);

    QLineF line() const
    { return mLine; }

    void setLine(const QLineF &li);

    QRectF boundingRect() const
    { return mBoundingRectCache; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRectF mBoundingRectCache;
    QLineF mLine;
};

#endif // SMOOTHLINEITEM_H
