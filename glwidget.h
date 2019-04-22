#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void paintEvent(QPaintEvent *e);
};

#endif // GLWIDGET_H
