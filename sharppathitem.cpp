#include "sharppathitem.h"
#include <QPainter>

SharpPathItem::SharpPathItem(QGraphicsItem *parent) :
    PathItem(parent)
{
    mMode = Shrink;
    mStartWidth = pen().widthF();
    mMaxWidth = pen().widthF();
    mMinWidth = pen().widthF();
}

void SharpPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    mCurrentWidth = mStartWidth;
    qreal variantFactor = 0.98;
    painter->setRenderHint(QPainter::Antialiasing, true);
    qreal percent = 1/path().length()/2;

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
        painter->drawPoint(path().pointAtPercent(f));
    }
}
