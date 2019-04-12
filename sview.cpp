#include "sview.h"
#include "sscene.h"
#include <QWheelEvent>

SView::SView(QWidget *parent) :
    QGraphicsView(parent)
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
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
