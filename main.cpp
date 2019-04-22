#include "drawcurvedialog.h"
#include <QApplication>
#include <QDebug>
#include <QtMath>
#include "glwidget.h"
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);//a.setAttribute(Qt::AA_UseOpenGLES);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(16);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format); // must be called before the widget or its parent window gets shown

    DrawCurveDialog w;
    //w.showMaximized();
    w.show();

    //qDebug() << qPow(0.9, 10);

    //GLWidget gl;
    //gl.show();

    return a.exec();
}
