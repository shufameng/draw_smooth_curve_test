#ifndef SHARPPATHITEM_H
#define SHARPPATHITEM_H

#include "pathitem.h"

class SharpPathItem : public PathItem
{
public:
    enum VMode
    {
        Expand, Shrink
    };

    explicit SharpPathItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setStartWidth(qreal w)
    {
        mStartWidth = w;
        update();
    }

    void setVMode(VMode mode)
    {
        mMode = mode;
        update();
    }

private:
    qreal mStartWidth;
    qreal mCurrentWidth;
    qreal mMinWidth;
    qreal mMaxWidth;
    VMode mMode;
};

#endif // SHARPPATHITEM_H
