#ifndef SHARPLINEITEM_H
#define SHARPLINEITEM_H

#include "lineitem.h"

class SharpLineItem : public LineItem
{
public:
    explicit SharpLineItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal mCurrentWidth;
};

#endif // SHARPLINEITEM_H
