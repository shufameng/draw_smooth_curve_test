#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

class PointItem : public QGraphicsItem
{

public:
    explicit PointItem(QGraphicsItem *parent = 0);

    QPen pen() const
    { return mPen; }
    void setPen(const QPen &p)
    {
        mPen = p;
        update();
    }

    QBrush brush() const
    { return mBrush; }
    void setBrush(const QBrush &b)
    {
        mBrush = b;
        update();
    }

    QPointF point() const
    { return mPoint; }
    void setPoint(const QPointF &p)
    {
        mPoint = p;
        update();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QPen mPen;
    QBrush mBrush;
    QPointF mPoint;
};

#endif // POINTITEM_H
