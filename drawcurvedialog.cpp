#include "drawcurvedialog.h"
#include "ui_drawcurvedialog.h"
#include "sscene.h"
#include <QColorDialog>
#include <QPainter>

DrawCurveDialog::DrawCurveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawCurveDialog)
{
    ui->setupUi(this);
    resize(800, 600);

    ui->widgetView->setScene(new SScene(this));
    QPen p;
    p.setJoinStyle(Qt::RoundJoin);
    p.setCapStyle(Qt::RoundCap);
    p.setColor(Qt::red);
    p.setWidth(6);
    dynamic_cast<SScene*>(ui->widgetView->scene())->setToolPen(p);

    QButtonGroup *g = new QButtonGroup(this);
    g->addButton(ui->toolButtonPen1);
    g->addButton(ui->toolButtonPen2);
    g->addButton(ui->toolButtonPen3);
    g->addButton(ui->toolButtonPen4);

    updateUI();
}

DrawCurveDialog::~DrawCurveDialog()
{
    delete ui;
}

void DrawCurveDialog::on_toolButtonPen1_clicked()
{
    ui->widgetView->setSceneTool((int)SScene::Pen1);
}

void DrawCurveDialog::on_toolButtonPen2_clicked()
{
    ui->widgetView->setSceneTool((int)SScene::Pen2);
}

void DrawCurveDialog::on_toolButtonPenColor_clicked()
{
    QColor c = QColorDialog::getColor();
    if (c.isValid())
    {
        QPen p = ui->widgetView->sceneToolPen();
        p.setColor(c);
        ui->widgetView->setSceneToolPen(p);
        updateUI();
        //setCursor(generatePenCursor(p));
    }
}

void DrawCurveDialog::on_horizontalSliderPenWidth_valueChanged(int value)
{
    QPen p = ui->widgetView->sceneToolPen();
    p.setWidth(value);
    ui->widgetView->setSceneToolPen(p);
    updateUI();

    //setCursor(generatePenCursor(p));
}

void DrawCurveDialog::updateUI()
{
    QPen p = ui->widgetView->sceneToolPen();

    QPixmap pixmap(24, 24);
    pixmap.fill(p.color());
    ui->toolButtonPenColor->setIcon(QIcon(pixmap));
    ui->horizontalSliderPenWidth->setValue(p.width());
    ui->labelPenWidth->setText(QString("%1").arg(p.width()));
}

QCursor DrawCurveDialog::generatePenCursor(const QPen &p)
{
    QImage img(p.width() + 2, p.width() + 2, QImage::Format_RGBA8888);
    img.fill(Qt::transparent);
    QPainter painter(&img);
    painter.setRenderHints(QPainter::Antialiasing);

    QColor c;
    int temp = 0xffffff;
    QRgb rgb = p.color().rgb();
    c.setRgb(rgb^temp);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(c);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawEllipse(img.rect().adjusted(1, 1, -1, -1));
    QCursor cs(QPixmap::fromImage(img));
    return cs;
}

void DrawCurveDialog::on_toolButtonResetTransform_clicked()
{
    ui->widgetView->resetTransform();
}

void DrawCurveDialog::on_toolButton_clicked()
{
    ui->widgetView->scene()->clear();
}

void DrawCurveDialog::on_toolButtonPen3_clicked()
{
    ui->widgetView->setSceneTool((int)SScene::Pen3);
}

void DrawCurveDialog::on_toolButtonPen4_clicked()
{
    ui->widgetView->setSceneTool((int)SScene::Pen4);
}
