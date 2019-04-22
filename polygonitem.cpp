#include "polygonitem.h"
#include <QPainter>

PolygonItem::PolygonItem(QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent)
{

}

void PolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    //painter->fillRect(boundingRect(), Qt::transparent);
    QGraphicsPolygonItem::paint(painter, option, widget);
}
