#include "sharplineitem.h"
#include <QPainter>
#include <QDebug>

SharpLineItem::SharpLineItem(QGraphicsItem *parent) :
    LineItem(parent)
{
    mMode = Shrink;
    mStartWidth = pen().widthF();
    mMinWidth = pen().widthF();
    mMaxWidth = pen().widthF();
}

void SharpLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    mCurrentWidth  = mStartWidth;
    qreal variantFactor = 0.99;
    painter->setRenderHint(QPainter::Antialiasing, true);
    qreal percent = 1/line().length()/2;

    for (qreal f = 0; f <= 1; f += percent)
    {
        if (mMode == Expand)
        {
            mCurrentWidth /= variantFactor;
            if (mCurrentWidth > mMaxWidth)
                mCurrentWidth = mMaxWidth;
        }
        else if (mMode == Shrink)
        {
            mCurrentWidth *= variantFactor;
            if (mCurrentWidth < mMinWidth)
                mCurrentWidth = mMinWidth;
        }

        QPen p = pen();
        p.setWidthF(mCurrentWidth);
        painter->setPen(p);
        painter->drawPoint(line().pointAt(f));
    }
}
