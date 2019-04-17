#ifndef PATHITEM_H
#define PATHITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

class PathItem : public QGraphicsItem
{

public:
    explicit PathItem(QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;


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

    void setPath(const QPainterPath &p)
    {
        prepareGeometryChange();
        mPath = p;
        update();
    }
    QPainterPath path() const
    {
        return mPath;
    }

private:
    QPen mPen;
    QBrush mBrush;
    QPainterPath mPath;
private:
};

#endif // PATHITEM_H
