#include "sscene.h"
#include <QGraphicsSceneEvent>
#include "linegroupitem.h"
#include "lineitem.h"
#include "pointitem.h"
#include <QScrollBar>
#include <QPainterPathStroker>
#include <QDebug>

qreal getAngle(const QPointF &p, const QPointF &cp1, const QPointF &cp2)
{
    qreal angle;
    return angle;
}

SScene::SScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mTool = Pen1;
    setSceneRect(0, 0, 1920, 1080);

    //QBrush b;
    //b.setTexture(QPixmap("C:/Qt_test_cpp/bg_style_grid.png"));
    //b.setColor(Qt::red);
    //b.setStyle(Qt::Dense2Pattern);
    //setBackgroundBrush(b);
}

SScene::~SScene()
{

}

void SScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mIsLButtonOnPress = true;
        mLButtonScenePos = e->scenePos();
        mLButtonScreenPos = e->screenPos();
        switch (mTool)
        {
        case Pen1:
        case Pen2:
        case Pen3:
        {
            mLastCreatedLineGroup = new LineGroupItem;
            addItem(mLastCreatedLineGroup);
        }
            break;
        case Pen4:
        {
            PointItem *item = new PointItem;
            item->setPoint(e->scenePos());
            item->setPen(mToolPen);
            addItem(item);
        }
            break;
        default:
            break;
        }
    }
    else if (e->button() & Qt::RightButton)
    {
        mIsRButtonOnPress = true;
        mRButtonScenePos = e->scenePos();
    }
}

void SScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (mIsLButtonOnPress)
    {
        if (mTool == Pen1)
        {
            qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
            if (len > mToolPen.widthF())
            {
                if (mLButtonScenePos != e->lastScenePos())
                {
                    addLineItem(QLineF(mLButtonScenePos, e->lastScenePos()));
                }
                addLineItem(QLineF(e->lastScenePos(), e->scenePos()));
                mLButtonScenePos = e->scenePos();
                mLButtonScreenPos = e->screenPos();
            }
        }
        else if (mTool == Pen2)
        {
            qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
            if (len > mToolPen.widthF())
            {
                addLineItem(QLineF(mLButtonScenePos, e->scenePos()));
                mLButtonScenePos = e->scenePos();
                mLButtonScreenPos = e->screenPos();
            }
        }
        else if (mTool == Pen3)
        {
            addLineItem(QLineF(e->lastScenePos(), e->scenePos()));
            mLButtonScenePos = e->scenePos();
            mLButtonScreenPos = e->screenPos();
        }
        else if (mTool == Pen4)
        {
            PointItem *item = new PointItem;
            item->setPoint(e->scenePos());
            item->setPen(mToolPen);
            addItem(item);
        }
    }
    else if (mIsRButtonOnPress)
    {
        mRButtonScenePos = e->scenePos();
    }
}

void SScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mLastCreatedLineGroup = NULL;
        mIsLButtonOnPress = false;
    }
    else if (e->button() & Qt::RightButton)
    {
        mIsRButtonOnPress = false;
    }
}

void SScene::addLineItem(const QLineF &line)
{
    LineItem *item = new LineItem(line);
    item->setPen(mToolPen);
    addItem(item);
    //mLastCreatedLineGroup->addToGroup(item);
}









