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


    void setPen(const QPen &p)
    {
        mPen = p;
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
