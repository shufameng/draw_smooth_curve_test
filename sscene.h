#ifndef SSCENE_H
#define SSCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QGraphicsPathItem>

class LineItem;
class LineGroupItem;
class PathItem;
class SScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Tool { NoTool, Pen1, Pen2, Pen3, Pen4 };

    explicit SScene(QObject *parent = 0);
    virtual ~SScene();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

public :
    QPen toolPen() const
    {
        return mToolPen;
    }
    void setToolPen(const QPen &p)
    {
        mToolPen = p;
    }

    QBrush toolBrush() const
    {
        return mToolBrush;
    }
    void setToolBrush(const QBrush &b)
    {
        mToolBrush = b;
    }

    int tool() const
    {
        return mTool;
    }
    void setTool(int t)
    {
        mTool = t;
    }

    void addLineItem(const QLineF &line);

private:
    bool mIsLButtonOnPress;
    QPointF mLButtonScenePos;
    bool mIsRButtonOnPress;
    QPointF mRButtonScenePos;
    QPoint mLButtonScreenPos;
    QPen mToolPen;
    QBrush mToolBrush;
    int mTool;
    LineGroupItem *mLastCreatedLineGroup;
    //QGraphicsPathItem *mLastCreatedPath;

    QList<QPointF> mInputPoints;
    QPointF mLastPenPoint;
    PathItem *mLastCreatedPathItem;
    QPainterPath mLastCreatedPath;
    qreal mLastCreatedPathPenWidth;

    qreal mPenVariantFactor;
    qreal mPenMinWidth;
    qreal mPenMinLenghtBetweenPoints;
    qreal mPenExpandLength;
    qreal mPenShrinkLength;
};

#endif // SSCENE_H
