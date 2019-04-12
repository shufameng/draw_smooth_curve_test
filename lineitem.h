#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

class LineItem : public QGraphicsItem
{
public:
    explicit LineItem(QGraphicsItem *parent = 0);
    explicit LineItem(const QLineF &l, QGraphicsItem *parent = 0);
    explicit LineItem(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent = 0);
    virtual ~LineItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPen pen() const
    {
        return mPen;
    }

    void setPen(const QPen &p)
    {
        mPen = p;
        update();
    }

    QBrush brush() const
    {
        return mBrush;
    }

    void setBrush(const QBrush &b)
    {
        mBrush = b;
        update();
    }

    QLineF line() const
    {
        return mLine;
    }

    void setLine(const QLineF &l)
    {
        prepareGeometryChange();
        mLine = l;
        update();
    }

    void setLine(const QPointF &p1, const QPointF &p2)
    {
        setLine(QLineF(p1, p2));
    }

private:
    QPen mPen;
    QBrush mBrush;
    QLineF mLine;
};

#endif // LINEITEM_H
