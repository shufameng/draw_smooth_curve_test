#include "sscene.h"
#include <QGraphicsSceneEvent>
#include "linegroupitem.h"
#include "lineitem.h"
#include "pointitem.h"
#include <QScrollBar>
#include <QPainterPathStroker>
#include <QDebug>
#include "pathitem.h"
#include "sharplineitem.h"
#include "sharppathitem.h"

qreal getAngle(const QPointF &p, const QPointF &cp1, const QPointF &cp2)
{
    qreal angle;
    return angle;
}

QPainterPath test_get_smooth_curve_by_points(const QList<QPointF> &points, qreal minDist)
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

            if (dist < minDist)
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
    mTool = Pen4;
    setSceneRect(0, 0, 1920, 1080);

    //QBrush b;
    //b.setTexture(QPixmap("C:/Qt_test_cpp/bg_style_grid.png"));
    //b.setColor(Qt::red);
    //b.setStyle(Qt::Dense2Pattern);
    //setBackgroundBrush(b);

//    QPainterPath path;
//    path.moveTo(600, 600);
//    path.quadTo(900, 900, 1000, 600);
//    SharpPathItem *item = new SharpPathItem;
//    item->setPath(path);
//    item->setStartWidth(20);
//    QPen p;
//    p.setJoinStyle(Qt::RoundJoin);
//    p.setCapStyle(Qt::RoundCap);
//    p.setColor(Qt::white);
//    item->setPen(p);
//    addItem(item);

    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::black);
    setBackgroundBrush(b);




    mPenMinLenghtBetweenPoints = 3;
    mPenMinWidth = 1.0;
    mPenVariantFactor = 0.95;
    mPenExpandLength = 10;
    mPenShrinkLength = 6;
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
        {
            mInputPoints.clear();
            mInputPoints.append(e->scenePos());
            mLastCreatedPath = QPainterPath();
            mLastCreatedPath.moveTo(e->scenePos());
            mLastCreatedPathItem = new PathItem;
            mLastCreatedPathItem->setPath(mLastCreatedPath);
            mLastCreatedPathItem->setPen(mToolPen);
            addItem(mLastCreatedPathItem);
        }
            break;
        case Pen2:
        {

        }
            break;

        case Pen3:
        {
            mInputPoints.append(e->scenePos());
            mLastPenPoint = e->scenePos();
            mLastCreatedPathPenWidth = mToolPen.widthF();

            QPainterPath path;
            path.moveTo(mLastPenPoint);
            mLastCreatedPathItem = new PathItem;
            mLastCreatedPathItem->setPath(path);
            mLastCreatedPathItem->setPen(mToolPen);
            addItem(mLastCreatedPathItem);
//            PointItem *item = new PointItem;
//            item->setPoint(e->scenePos());
//            item->setPen(mToolPen);
//            addItem(item);
        }
            break;
        case Pen4:
        {
            mInputPoints.append(e->scenePos());
            mLastPenPoint = e->scenePos();
            mLastCreatedPathPenWidth = mToolPen.widthF();

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
            mInputPoints.append(e->scenePos());
            mLastCreatedPath.lineTo(e->scenePos());
            mLastCreatedPathItem->setPath(mLastCreatedPath);
        }
        else if (mTool == Pen2)
        {

        }
        else if (mTool == Pen3)
        {
            QPainterPath path;
            path.moveTo(mLastPenPoint);
            qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
            if (len > mToolPen.widthF()/100 && len > 1)
            {
                QPainterPath path = mLastCreatedPathItem->path();

                QLineF line(mLButtonScenePos, e->scenePos());
                qreal dist = line.length();

                line.setLength(line.length()*0.5);
                path.quadTo(mInputPoints.last(), line.p2());
                mLastCreatedPathItem->setPath(path);

                mLastPenPoint = line.p2();

                mInputPoints.append(e->scenePos());
                mLButtonScenePos = e->scenePos();
                mLButtonScreenPos = e->screenPos();
            }

        }
        else if (mTool == Pen4)
        {
            qreal len = QLineF(mLButtonScenePos, e->scenePos()).length();
            if (len > mToolPen.widthF()*3 && len > 1)
            {
                mLastCreatedPathItem = new PathItem;
                QPainterPath path;
                path.moveTo(mLastPenPoint);

                QLineF line(mLButtonScenePos, e->scenePos());
                qreal dist = line.length();

                line.setLength(line.length()*0.5);
                path.quadTo(mInputPoints.last(), line.p2());

//                QPen p;
//                p.setStyle(Qt::SolidLine);
//                p.setWidthF(mToolPen.widthF());
//                p.setColor(Qt::red);
//                QPainterPathStroker stk(p);
//                stk.setCapStyle(Qt::RoundCap);
//                stk.setJoinStyle(Qt::RoundJoin);

//                stk.setCurveThreshold(0.1);
//                mLastCreatedPath->setPath(stk.createStroke(path));
                mLastCreatedPathItem->setPath(path);


                if (QLineF(e->lastScreenPos(), e->screenPos()).length() > 10)
                {
                    mLastCreatedPathPenWidth -= 0.2;
                }
                else
                {
                    mLastCreatedPathPenWidth += 0.2;
                }

                if (mLastCreatedPathPenWidth > mToolPen.widthF())
                    mLastCreatedPathPenWidth = mToolPen.widthF();
                if (mLastCreatedPathPenWidth < mToolPen.widthF()/2)
                    mLastCreatedPathPenWidth = mToolPen.widthF()/2;


                QPen pen = mToolPen;
                pen.setWidthF(mLastCreatedPathPenWidth);
                mLastCreatedPathItem->setPen(pen);

                addItem(mLastCreatedPathItem);

                mLastPenPoint = line.p2();

                mInputPoints.append(e->scenePos());
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
        if (Pen1 == mTool)
        {
            QPainterPath path = test_get_smooth_curve_by_points(mInputPoints, mToolPen.widthF()*4);
            mLastCreatedPathItem->setPath(path);
        }
        else if (Pen2 == mTool)
        {

        }
        else if (Pen3 == mTool)
        {
            QPainterPath path = mLastCreatedPathItem->path();
            QPainterPathStroker s(mToolPen);
            s.setWidth(mToolPen.widthF());
            s.setCurveThreshold(0.01);
            QPainterPath pathOutLine = s.createStroke(path);
            mLastCreatedPathItem->setPath(pathOutLine);
            QColor c = mToolPen.color();
            c.setAlpha(100);
            QPen p;
            p.setStyle(Qt::NoPen);
            p.setColor(Qt::red);
            p.setWidthF(1);
            mLastCreatedPathItem->setPen(p);
            QBrush b;
            b.setStyle(Qt::SolidPattern);
            b.setColor(mToolPen.color());
            mLastCreatedPathItem->setBrush(b);
        }
        else if (Pen4 == mTool)
        {
            SharpLineItem *item = new SharpLineItem;
            item->setLine(mLastPenPoint, e->scenePos());
            QPen p = mToolPen;
            p.setWidthF(mLastCreatedPathPenWidth);
            item->setPen(p);
            addItem(item);

//            mLastCreatedPath = new PathItem;
//            QPainterPath path;
//            path.moveTo(mLastPenPoint);
//            path.lineTo(e->scenePos());
//            QPen p = mToolPen;
//            p.setWidthF(mLastCreatedPathPenWidth);
//            mLastCreatedPath->setPen(p);
//            mLastCreatedPath->setPath(path);
//            addItem(mLastCreatedPath);

//            for (int i = 0; i < mInputPoints.size(); ++i)
//            {
//                PointItem *item = new PointItem;
//                item->setPoint(mInputPoints.at(i));
//                QPen p = mToolPen;
//                p.setColor(Qt::black);
//                item->setPen(p);
//                addItem(item);
//            }
            mInputPoints.clear();
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









