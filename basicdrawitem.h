#ifndef BASICDRAWITEM_H
#define BASICDRAWITEM_H

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QPainter>

class BasicDrawItem : public QGraphicsItem
{
public:
    explicit BasicDrawItem(QGraphicsItem *parent = 0);
    virtual ~BasicDrawItem();

    QPen pen() const
    { return mPen; }

    QBrush brush() const
    { return mBrush; }

    void setPen(const QPen &p);
    void setBrush(const QBrush &b);

private:
    QPen mPen;
    QBrush mBrush;
};

#endif // BASICDRAWITEM_H
