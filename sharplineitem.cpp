#include "sharplineitem.h"
#include <QPainter>
#include <QDebug>

SharpLineItem::SharpLineItem(QGraphicsItem *parent) :
    LineItem(parent)
{
}

void SharpLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    mCurrentWidth = pen().widthF();
    qreal percent = 0.1;
    QLineF li;

    for (qreal f = 0; f + percent <= 1; f += percent)
    {
        li.setPoints(line().pointAt(f), line().pointAt(f + percent));

        if (mCurrentWidth > 1)
        {
            mCurrentWidth *= 0.97;
            if (mCurrentWidth < 1)
                mCurrentWidth = 1;
        }


        QPen p = pen();
        p.setWidthF(mCurrentWidth);
        painter->setPen(p);
        painter->drawLine(li);
    }
}
