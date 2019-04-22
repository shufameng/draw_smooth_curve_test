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
#include <QtMath>
#include "polygonitem.h"

qreal getAngle(const QPointF &p, const QPointF &cp1, const QPointF &cp2)
{
    qreal angle;
    return angle;
}

QList<QPainterPath> test_get_smooth_curve_by_points(const QList<QPointF> &points, qreal minDist)
{
    QList<QPainterPath> paths;
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
            QPainterPath path;
            path.moveTo(current);
            paths.append(path);
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
                QPainterPath path;
                path.moveTo(paths.last().currentPosition());
                path.lineTo(prevMidPoint);
                paths.append(path);
                dist = 0;
                continue;
            }
        }
        else
        {
            prev = points.at(i - 1);
            QLineF line(prev, current);

            dist += line.length();

            if (dist < minDist)
            {
                QLineF linePrev(points.at(i-2), prev);
                if (qAbs(line.angle() - linePrev.angle()) > 30)
                {
                    line.setLength(line.length()*0.5);
                    QPainterPath path;
                    path.moveTo(paths.last().currentPosition());
                    path.quadTo(prev, line.p2());
                    paths.append(path);
                    dist = 0;
                }
                //path.lineTo(current);
                continue;
            }
            else
            {
                line.setLength(line.length()*0.5);
                QPainterPath path;
                path.moveTo(paths.last().currentPosition());
                path.quadTo(prev, line.p2());
                paths.append(path);
                //path.cubicTo(prev, prev, line.p2());
                dist = 0;
            }
        }
    }

   return paths;
}

QPolygonF lineToPolygon(const QLineF& pLine, const qreal& pWidth)

{

    qreal x1 = pLine.x1();

    qreal y1 = pLine.y1();



    qreal x2 = pLine.x2();

    qreal y2 = pLine.y2();



    qreal alpha = (90.0 - pLine.angle()) * M_PI / 180.0;

    qreal hypothenuse = pWidth / 2;



    // TODO UB 4.x PERF cache sin/cos table

    qreal opposite = sin(alpha) * hypothenuse;

    qreal adjacent = cos(alpha) * hypothenuse;



    QPointF p1a(x1 - adjacent, y1 - opposite);

    QPointF p1b(x1 + adjacent, y1 + opposite);



    QPointF p2a(x2 - adjacent, y2 - opposite);

    QPointF p2b(x2 + adjacent, y2 + opposite);



    QPainterPath painterPath;



    painterPath.moveTo(p1a);

    painterPath.lineTo(p2a);



    painterPath.arcTo(x2 - hypothenuse, y2 - hypothenuse, pWidth, pWidth, (90.0 + pLine.angle()), -180.0);



    //painterPath.lineTo(p2b);

    painterPath.lineTo(p1b);



    painterPath.arcTo(x1 - hypothenuse, y1 - hypothenuse, pWidth, pWidth, -1 * (90.0 - pLine.angle()), -180.0);



    painterPath.closeSubpath();



    return painterPath.toFillPolygon();

}

QPolygonF lineToPolygon(const QLineF& pLine, const qreal& pStartWidth, const qreal& pEndWidth)

{

    qreal x1 = pLine.x1();

    qreal y1 = pLine.y1();



    qreal x2 = pLine.x2();

    qreal y2 = pLine.y2();



    qreal alpha = (90.0 - pLine.angle()) * M_PI / 180.0;

    qreal startHypothenuse = pStartWidth / 2;

    qreal endHypothenuse = pEndWidth / 2;



    // TODO UB 4.x PERF cache sin/cos table

    qreal startOpposite = sin(alpha) * startHypothenuse;

    qreal startAdjacent = cos(alpha) * startHypothenuse;



    qreal endOpposite = sin(alpha) * endHypothenuse;

    qreal endAdjacent = cos(alpha) * endHypothenuse;



    QPointF p1a(x1 - startAdjacent, y1 - startOpposite);

    QPointF p1b(x1 + startAdjacent, y1 + startOpposite);



    QPointF p2a(x2 - endAdjacent, y2 - endOpposite);

    QPointF p2b(x2 + endAdjacent, y2 + endOpposite);



    QPainterPath painterPath;

    painterPath.moveTo(p1a);

    painterPath.lineTo(p2a);



    painterPath.arcTo(x2 - endHypothenuse, y2 - endHypothenuse, pEndWidth, pEndWidth, (90.0 + pLine.angle()), -180.0);



    //painterPath.lineTo(p2b);

    painterPath.lineTo(p1b);



    painterPath.arcTo(x1 - startHypothenuse, y1 - startHypothenuse, pStartWidth, pStartWidth, -1 * (90.0 - pLine.angle()), -180.0);



    painterPath.closeSubpath();



    return painterPath.toFillPolygon();

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
    b.setColor(Qt::white);
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
            mLastPenPoint = e->scenePos();
            mInputPoints.clear();
            mLineItems.clear();
            mInputPoints.append(e->scenePos());
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
            LineItem *item = new LineItem;
            item->setLine(QLineF(e->lastScenePos(), e->scenePos()));
            item->setPen(mToolPen);
            addItem(item);
            mLastCreatedPathItemsDummy.append(item);
            //mLastCreatedPath.lineTo(e->scenePos());
            //mLastCreatedPathItem->setPath(mLastCreatedPath);
        }
        else if (mTool == Pen2)
        {
            QLineF li(mLastPenPoint, e->scenePos());
            if (li.length() > 1)
            {
                LineItem *item = new LineItem;
                item->setPen(toolPen());
                item->setLine(li);
                addItem(item);
                mLastPenPoint = e->scenePos();
                mLineItems.append(item);
            }

            mInputPoints.append(e->scenePos());
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
            if (len > mToolPen.widthF()*1.5 && len > 1)
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
            QList<QPainterPath> paths = test_get_smooth_curve_by_points(mInputPoints, mToolPen.widthF());
            LineGroupItem *ig = new LineGroupItem;
            addItem(ig);
            for (int i = 0; i < mLastCreatedPathItemsDummy.size(); ++i)
            {
                removeItem(mLastCreatedPathItemsDummy[i]);
            }
            mLastCreatedPathItemsDummy.clear();
            for (int i = 0; i < paths.size(); ++i)
            {
                PathItem *item = new PathItem;
                item->setPen(mToolPen);
                item->setPath(paths.at(i));
                //addItem(item);
                ig->addToGroup(item);
            }
        }
        else if (Pen2 == mTool)
        {
//            QPointF p;
//            for (int i = 0; i + 2 < mInputPoints.size(); ++i)
//            {
//                QLineF l(mInputPoints.at(i), mInputPoints.at(i + 1));
//                if (l.length() < 10)
//                {
//                    LineItem *item = new LineItem;
//                    item->setPen(mToolPen);
//                    item->setLine(QLineF(mInputPoints.at(i), mInputPoints.at(i+2)));
//                    addItem(item);
//                }

//            }

//            foreach (LineItem *item, mLineItems)
//            {
//                removeItem(item);
//                delete item;
//           }

//            QPainterPath path;
//            for (int i = 0; i + 1 < mInputPoints.size(); ++i)
//            {
//                if (0 == i)
//                    path.moveTo(mInputPoints.at(i));
//                else
//                {
//                    path.lineTo(mInputPoints.at(i));
//                }

//                QPolygonF poly = lineToPolygon(QLineF(mInputPoints.at(i), mInputPoints.at(i+1)), mToolPen.widthF());

//                QPen p = mToolPen;
//                QColor c = mToolPen.color();
//                c.setAlpha(10);
//                p.setColor(c);
//                p.setWidthF(2);

//                QBrush b;
//                b.setStyle(Qt::SolidPattern);
//                b.setColor(mToolPen.color());

//                PolygonItem *item = new PolygonItem;item->setFillRule(Qt::WindingFill);
//                item->setPolygon(poly);
//                item->setBrush(b);
//                //p.setBrush(b);
//                item->setPen(p);

//                addItem(item);
//            }
//            QPainterPathStroker sk;
//            sk.setCapStyle(Qt::RoundCap);
//            sk.setJoinStyle(Qt::RoundJoin);
//            sk.setWidth(mToolPen.widthF());

//            QBrush b;
//            b.setStyle(Qt::SolidPattern);
//            b.setColor(mToolPen.color());


//            QPainterPath spath = sk.createStroke(path);spath.setFillRule(Qt::WindingFill);
//            PathItem *item = new PathItem;
//            item->setPath(spath);
//            item->setBrush(b);
//            item->setPen(QPen(Qt::NoPen));
//            addItem(item);

//            path.closeSubpath();
//            QList<QPolygonF> list = path.toFillPolygons();qDebug() << list.size();
//            for (int i = 0; i < list.size(); ++i)
//            {
//                PolygonItem *item = new PolygonItem;
//                item->setPolygon(list.at(i));
//                addItem(item);
//            }
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









