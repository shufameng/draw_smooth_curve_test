#-------------------------------------------------
#
# Project created by QtCreator 2019-04-12T15:03:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw_smooth_curve_test
TEMPLATE = app




SOURCES += main.cpp\
        drawcurvedialog.cpp \
    sview.cpp \
    sscene.cpp \
    linegroupitem.cpp \
    lineitem.cpp \
    pathitem.cpp \
    linesitem.cpp \
    pointitem.cpp \
    sharplineitem.cpp \
    sharppathitem.cpp \
    smoothlineitem.cpp \
    basicdrawitem.cpp \
    glwidget.cpp \
    polygonitem.cpp

HEADERS  += drawcurvedialog.h \
    sview.h \
    sscene.h \
    linegroupitem.h \
    lineitem.h \
    pathitem.h \
    linesitem.h \
    pointitem.h \
    sharplineitem.h \
    sharppathitem.h \
    smoothlineitem.h \
    basicdrawitem.h \
    glwidget.h \
    polygonitem.h

FORMS    += drawcurvedialog.ui
