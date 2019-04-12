#include "drawcurvedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawCurveDialog w;
    w.show();

    return a.exec();
}
