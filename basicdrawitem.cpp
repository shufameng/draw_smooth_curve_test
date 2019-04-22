#include "basicdrawitem.h"

BasicDrawItem::BasicDrawItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{

}

BasicDrawItem::~BasicDrawItem()
{

}

void BasicDrawItem::setPen(const QPen &p)
{
    mPen = p;
    update();
}

void BasicDrawItem::setBrush(const QBrush &b)
{
    mBrush = b;
    update();
}
