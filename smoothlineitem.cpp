#include "smoothlineitem.h"

SmoothLineItem::SmoothLineItem(QGraphicsItem *parent) :
    BasicDrawItem(parent)
{

}

void SmoothLineItem::setLine(const QLineF &li)
{
    prepareGeometryChange();
    mLine = li;
//    qreal halfpw = pen().style() == Qt::NoPen ? 0 : pen().widthF()/2;
//    mBoundingRectCache =
//            QRectF(QPointF(),
//                    QPointF())
//            .adjusted(-);
    update();
}

void SmoothLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
