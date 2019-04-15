#include "linegroupitem.h"
#include "lineitem.h"
#include <QDateTime>
#include <QDebug>

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

void LineGroupItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "LineGroupItem::paint";
    qint64 t1 = QDateTime::currentMSecsSinceEpoch();qDebug() << t1;
    QGraphicsItemGroup::paint(painter, option, widget);
    qint64 t2 = QDateTime::currentMSecsSinceEpoch();qDebug() << t2;
    qDebug() << t2 - t1;
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
