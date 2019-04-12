#ifndef SVIEW_H
#define SVIEW_H

#include <QGraphicsView>

class SScene;
class SView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SView(QWidget *parent = 0);
    ~SView();

public slots:
    void setSceneToolPen(const QPen &p);
    void setSceneTool(int tool);
    QPen sceneToolPen() const;

protected:
    virtual void wheelEvent(QWheelEvent *e);

};

#endif // SVIEW_H
