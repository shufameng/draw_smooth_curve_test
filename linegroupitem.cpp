#include "linegroupitem.h"
#include "lineitem.h"

LineGroupItem::LineGroupItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{

}

LineGroupItem::~LineGroupItem()
{

}

void LineGroupItem::addToGroup(LineItem *item)
{
    QGraphicsItemGroup::addToGroup(item);
    item->setPen(mPen);
    item->setBrush(mBrush);
}

void LineGroupItem::addToGroup(const QLineF &line)
{
    addToGroup(new LineItem(line));
}

void LineGroupItem::removeFromGroup(LineItem *item)
{
    QGraphicsItemGroup::removeFromGroup(item);
}

void LineGroupItem::setPen(const QPen &p)
{
    mPen = p;
    QList<QGraphicsItem*> list = childItems();
    for (int i = 0; i < list.size(); ++i)
    {
        dynamic_cast<LineItem*>(list[i])->setPen(p);
    }
    update();
}

void LineGroupItem::setBrush(const QBrush &b)
{
    mBrush = b;
    QList<QGraphicsItem*> list = childItems();
    for (int i = 0; i < list.size(); ++i)
    {
        dynamic_cast<LineItem*>(list[i])->setBrush(b);
    }
    update();
}
