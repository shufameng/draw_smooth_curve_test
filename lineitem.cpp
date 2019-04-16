#include "lineitem.h"
#include <QPainter>
#include <QDebug>

LineItem::LineItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    mPen.setCapStyle(Qt::RoundCap);
    mPen.setJoinStyle(Qt::RoundJoin);
}

LineItem::LineItem(const QLineF &l, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    mPen.setCapStyle(Qt::RoundCap);
    mPen.setJoinStyle(Qt::RoundJoin);
    setLine(l);
}

LineItem::LineItem(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    mPen.setCapStyle(Qt::RoundCap);
    mPen.setJoinStyle(Qt::RoundJoin);
    setLine(p1, p2);
}

LineItem::~LineItem()
{

}

QRectF LineItem::boundingRect() const
{
    qreal halfpw = mPen.style() == Qt::NoPen ? 0 : mPen.widthF()/2;
    return QRectF(QPointF(qMin(mLine.p1().x(), mLine.p2().x()), qMin(mLine.p1().y(), mLine.p2().y())),
                  QPointF(qMax(mLine.p1().x(), mLine.p2().x()), qMax(mLine.p1().y(), mLine.p2().y())))
            .adjusted(-halfpw, -halfpw, halfpw, halfpw);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{//qDebug() << "LineItem::paint";
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawLine(mLine);
}
