#ifndef SHARPLINEITEM_H
#define SHARPLINEITEM_H

#include "lineitem.h"

class SharpLineItem : public LineItem
{
public:
    enum VariantMode
    {
        Expand, Shrink
    };

    explicit SharpLineItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    qreal startWidth() const
    {
        return mStartWidth;
    }
    void setStartWidth(qreal w)
    {
        mStartWidth = w;
        update();
    }

    void setVariantMode(VariantMode mode)
    {
        mMode = mode;
    }
    VariantMode variantMode()
    {
        return mMode;
    }

    void setMinWidth(qreal w)
    {
        if (mMinWidth != w)
        {
            mMinWidth = w;
            update();
        }
    }

    void setMaxWidth(qreal w)
    {
        if (mMaxWidth != w)
        {
            mMaxWidth = w;
            update();
        }
    }

private:
    qreal mStartWidth;
    qreal mMinWidth;
    qreal mMaxWidth;
    VariantMode mMode;

    qreal mCurrentWidth;
};

#endif // SHARPLINEITEM_H
