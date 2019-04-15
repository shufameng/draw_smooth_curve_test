#include "pointitem.h"
#include <QPainter>

PointItem::PointItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{

}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawPoint(mPoint);
}

QRectF PointItem::boundingRect() const
{
    qreal halfpw = mPen.style() == Qt::NoPen ? 0 : mPen.widthF()/2;
    return QRectF(mPoint - QPointF(1, 1),
                  mPoint + QPointF(1, 1))
            .adjusted(-halfpw, -halfpw, halfpw, halfpw);
}
