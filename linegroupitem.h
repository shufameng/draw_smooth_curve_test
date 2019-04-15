#ifndef LINEGROUPITEM_H
#define LINEGROUPITEM_H

#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>

class LineItem;
class LineGroupItem : public QGraphicsItemGroup
{

public:
    explicit LineGroupItem(QGraphicsItem *parent = 0);
    virtual ~LineGroupItem();

    void addToGroup(LineItem *item);
    void addToGroup(const QLineF &line);
    void removeFromGroup(LineItem *item);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPen pen() const
    {
        return mPen;
    }
    void setPen(const QPen &p);

    QBrush brush() const
    {
        return mBrush;
    }
    void setBrush(const QBrush &b);

private:
    QPen mPen;
    QBrush mBrush;
};

#endif // LINEGROUPITEM_H
