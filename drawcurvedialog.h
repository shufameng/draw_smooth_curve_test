#ifndef DRAWCURVEDIALOG_H
#define DRAWCURVEDIALOG_H

#include <QDialog>

namespace Ui {
class DrawCurveDialog;
}

class DrawCurveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawCurveDialog(QWidget *parent = 0);
    ~DrawCurveDialog();

private slots:
    void on_toolButtonPen1_clicked();

    void on_toolButtonPen2_clicked();

    void on_toolButtonPenColor_clicked();

    void on_horizontalSliderPenWidth_valueChanged(int value);

    void updateUI();

    QCursor generatePenCursor(const QPen &p);
    void on_toolButtonResetTransform_clicked();

    void on_toolButton_clicked();

    void on_toolButtonPen3_clicked();

    void on_toolButtonPen4_clicked();

private:
    Ui::DrawCurveDialog *ui;
};

#endif // DRAWCURVEDIALOG_H
