#include "drawcurvedialog.h"
#include <QApplication>
#include <QDebug>
#include <QtMath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawCurveDialog w;
    w.showMaximized();

    //qDebug() << qPow(0.95, 10);

    return a.exec();
}
