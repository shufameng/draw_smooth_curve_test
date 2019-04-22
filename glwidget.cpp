#include "glwidget.h"
#include <QDebug>
#include <QOpenGLFunctions_1_0>
#include <QPainter>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{qDebug() << "GLWidget::initializeGL()";
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//    f->glEnable(GL_MULTISAMPLE);
//    f->glEnable(GL_BLEND);
//    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    f->glEnable(GL_POINT_SMOOTH);
//    f->glEnable(GL_LINE_SMOOTH);
//    f->glEnable(GL_POLYGON_SMOOTH);
//    f->glClearColor(1, 1, 1, 0);
}

void GLWidget::resizeGL(int w, int h)
{qDebug() << "GLWidget::resizeGL()" << w << h;
    //return GLWidget::resizeGL(w, h);
}

void GLWidget::paintGL()
{qDebug() << "GLWidget::paintGL()";
    return QOpenGLWidget::paintGL();
    QOpenGLFunctions_1_0 *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_1_0>();
    if (!f)
    {
        qDebug() << "f is null";
        return;
    }

    QPainter painter(this);
    QPen p;
    p.setColor(Qt::black);
    p.setWidth(8);
    painter.setPen(p);
    painter.beginNativePainting();
    painter.drawLine(0, 0, 100, 100);
    painter.endNativePainting();

//    f->glViewport(0, 0, width(), height());
//    f->glClear(GL_COLOR_BUFFER_BIT);

//    f->glLineWidth(8);
//    f->glBegin(GL_LINES);
//    f->glColor4f(0, 0, 0, 1);
//    f->glVertex2f(0, 0);
//    f->glVertex2f(1, 1);
//    f->glVertex2f(1.5, 1.5);
//    f->glEnd();
//    f->glFlush();
}

void GLWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen p;
    p.setColor(Qt::black);
    p.setWidth(8);
    painter.setPen(p);
    painter.beginNativePainting();
    painter.setRenderHints(QPainter::Antialiasing);
    painter.drawLine(0, 0, 100, 100);
    painter.drawLine(100, 100, 300, 105);
    painter.endNativePainting();

    return QOpenGLWidget::paintEvent(e);
}
