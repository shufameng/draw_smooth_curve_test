#include "sscene.h"
#include <QGraphicsSceneEvent>
#include "linegroupitem.h"
#include "lineitem.h"
#include "pointitem.h"
#include <QScrollBar>
#include <QPainterPathStroker>
#include <QDebug>
#include "pathitem.h"

qreal getAngle(const QPointF &p, const QPointF &cp1, const QPointF &cp2)
{
    qreal angle;
    return angle;
}

QPainterPath test_get_smooth_curve_by_points(const QList<QPointF> &points)
{
    QPainterPath path;
    int pointsCount = points.size();
    QPointF prev, current;
    QPointF prevMidPoint;
    qreal dist = 0;
    qreal k = 0.5; // 直线所占比例

    for (int i = 0; i < pointsCount; ++i)
    {
        current = points.at(i);

        if (0 == i)
        {
            path.moveTo(current);
            continue;
        }
        else if (1 == i)
        {
            prev = points.at(i - 1);
            current = points.at(i);
            QLineF line(prev, current);

            dist += line.length();

            if (dist < 2)
            {
                //path.lineTo(current);
                //dist = 0;
                continue;
            }
            else
            {
                line.setLength(line.length()*0.5);
                prevMidPoint = line.p2();
                path.lineTo(prevMidPoint);
                dist = 0;
            }
        }
        else
        {
            prev = points.at(i - 1);
            QLineF line(prev, current);

            dist += line.length();

            if (dist < 2)
            {
                //path.lineTo(current);
                continue;
            }
            else
            {
                line.setLength(line.length()*0.5);
                path.quadTo(prev, line.p2());
                dist = 0;
            }
        }
    }

   return path;
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
            mPoints.append(e->scenePos());
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
            qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
            if (len > 1)
            {
                mPoints.append(e->scenePos());

                PointItem *item = new PointItem;
                item->setPoint(e->scenePos());
                QPen p = mToolPen;
                p.setWidthF(p.widthF()/2);
                item->setPen(p);
                addItem(item);
                mLButtonScenePos = e->scenePos();
                mLButtonScreenPos = e->screenPos();
            }
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
        if (Pen4 == mTool)
        {
            QPainterPath path = test_get_smooth_curve_by_points(mPoints);
            PathItem *item = new PathItem;
            item->setPen(mToolPen);
            item->setPath(path);
            addItem(item);
            mPoints.clear();
        }
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









