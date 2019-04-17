#include "pathitem.h"
#include <QPainter>

PathItem::PathItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{

}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawPath(mPath);
}

QRectF PathItem::boundingRect() const
{
    qreal halfpw = mPen.style() == Qt::NoPen ? 0 : mPen.widthF()/2;
    return mPath.boundingRect().adjusted(-halfpw, -halfpw, halfpw, halfpw);
}
