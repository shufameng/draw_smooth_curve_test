#include "sscene.h"
#include <QGraphicsSceneEvent>
#include "linegroupitem.h"
#include "lineitem.h"
#include <QScrollBar>
#include <QDebug>

SScene::SScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mTool = Pen;
    setSceneRect(0, 0, 1920, 1080);
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
        if (mTool == Pen)
        {
            mLastCreatedLineGroup = new LineGroupItem;
            mLastCreatedLineGroup->setPen(mToolPen);
            addItem(mLastCreatedLineGroup);
        }
        else if (mTool == PathPen)
        {

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
        if (mTool == Pen)
        {
            if (mLastCreatedLineGroup)
            {
                qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
                qreal len2 = QLineF(mLButtonScreenPos, e->screenPos()).length();
                qDebug() << len2 << len;
                mLastCreatedLineGroup->addToGroup(QLineF(e->lastScenePos(), e->scenePos()));
            }
        }
        else if (mTool == PathPen)
        {

        }

        mLButtonScenePos = e->scenePos();
        mLButtonScreenPos = e->screenPos();
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
