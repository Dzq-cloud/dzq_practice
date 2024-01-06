#ifndef CARDISPWIDGET_H
#define CARDISPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

namespace Ui {
class CarDispWidget;
}

class CarDispWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CarDispWidget(QWidget *parent = 0);
    ~CarDispWidget();
public:
    void setValues(qreal iValues);
    void paintEvent(QPaintEvent *event) override;

private:
    qreal qValues;

    const static int radius;

      const static int maxV;
        const static int minV;


private:
    Ui::CarDispWidget *ui;
};

#endif // CARDISPWIDGET_H
