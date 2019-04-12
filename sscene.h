#ifndef SSCENE_H
#define SSCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

class LineGroupItem;
class SScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Tool { NoTool, Pen, PathPen, Eraser };

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
};

#endif // SSCENE_H
