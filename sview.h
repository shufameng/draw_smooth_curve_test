#ifndef SVIEW_H
#define SVIEW_H

#include <QGraphicsView>

class SScene;
class SView : public QGraphicsView
{
    Q_OBJECT

public:
    enum Tool { Pen };

    explicit SView(QWidget *parent = 0);
    ~SView();

public slots:
    void setSceneToolPen(const QPen &p);
    void setSceneTool(int tool);
    QPen sceneToolPen() const;

protected:
    virtual void wheelEvent(QWheelEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual bool viewportEvent(QEvent *e);

private:
    Tool mTool;
    bool mIsLBtnOnPress;
    QPoint mLBtnPos;
    bool mIsRBtnOnPress;
    QPoint mRBtnPos;
};

#endif // SVIEW_H
