#include "sscene.h"
#include <QGraphicsSceneEvent>
#include "linegroupitem.h"
#include "lineitem.h"

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
}

void SScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (mIsLButtonOnPress)
    {
        if (mTool == Pen)
        {
            if (mLastCreatedLineGroup)
                mLastCreatedLineGroup->addToGroup(QLineF(e->lastScenePos(), e->scenePos()));
        }
        else if (mTool == PathPen)
        {

        }
    }
}

void SScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mLastCreatedLineGroup = NULL;
        mIsLButtonOnPress = false;
    }
}
