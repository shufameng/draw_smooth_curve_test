#include "sview.h"
#include "sscene.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTouchEvent>
#include "glwidget.h"
#include <QDebug>

SView::SView(QWidget *parent) :
    QGraphicsView(parent)
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    mTool = Pen;
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    //setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);

    mGLViewport = new GLWidget(this);
    setViewport(mGLViewport);

    //setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

SView::~SView()
{

}

void SView::setSceneToolPen(const QPen &p)
{
    SScene *s = dynamic_cast<SScene*>(scene());
    if (s)
        s->setToolPen(p);
}

void SView::setSceneTool(int tool)
{
    SScene *s = dynamic_cast<SScene*>(scene());
    if (s)
        s->setTool(tool);
}

QPen SView::sceneToolPen() const
{
    SScene *s = dynamic_cast<SScene*>(scene());
    if (s)
        return s->toolPen();
    else
        return QPen();
}

void SView::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
    {
        scale(1.1, 1.1);
    }
    else
    {
        scale(1/1.1, 1/1.1);
    }
}

void SView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mIsLBtnOnPress = true;
        mLBtnPos = e->pos();
        if (mTool == Pen)
        {

        }
    }
    else if (e->button() & Qt::RightButton)
    {
        mIsRBtnOnPress = true;
        mRBtnPos = e->pos();
    }
    return QGraphicsView::mousePressEvent(e);
}

void SView::mouseMoveEvent(QMouseEvent *e)
{
    if (mIsLBtnOnPress)
    {
        if (mTool == Pen)
        {

        }
    }
    else if (mIsRBtnOnPress)
    {

    }
    return QGraphicsView::mouseMoveEvent(e);
}

void SView::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mIsLBtnOnPress = false;
        if (mTool == Pen)
        {

        }
    }
    else if (e->button() & Qt::RightButton)
    {
        mIsRBtnOnPress = false;
    }
    return QGraphicsView::mouseReleaseEvent(e);
}

bool SView::viewportEvent(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    case QEvent::TouchCancel:
        return true;
        break;
    default:
        break;
    }
    return QGraphicsView::viewportEvent(e);
}

void SView::paintEvent(QPaintEvent *e)
{
    qDebug() << "SView::paintEvent";
    return QGraphicsView::paintEvent(e);
}

void SView::resizeEvent(QResizeEvent *e)
{
    qDebug() << "SView::resizeEvent";
    viewport()->update();
    return QGraphicsView::resizeEvent(e);
}














