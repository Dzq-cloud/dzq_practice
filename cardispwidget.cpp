#include "cardispwidget.h"
#include "ui_cardispwidget.h"

#include <QDebug>


const  int CarDispWidget::radius = 150;
const  int CarDispWidget::maxV = 400;
const  int CarDispWidget::minV = 0;


CarDispWidget::CarDispWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarDispWidget)
{
    ui->setupUi(this);
    qValues = 0;
}

CarDispWidget::~CarDispWidget()
{
    delete ui;
}

void CarDispWidget::setValues(qreal iValues)
{

    qValues = iValues;
    update();

}

void CarDispWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint center(width() / 2, height() / 2);
    painter.save(); // 将中心点保存起来

    // 绘制背景圆形
    painter.translate(center); //
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(142, 142, 142));

    const int bkRadius = radius + 3;
    painter.drawEllipse(QPoint(), bkRadius, bkRadius);

    // 绘制刻度线
    painter.rotate(-135);
    const int longStep = 10;
    const int shrtStep =50; // 总步长为50
    for (int i = 0; i <= shrtStep; i++) {
        // 前面80%刻度线为绿色， 后面20%为红色
        painter.setPen((i < shrtStep * 0.8) ? QColor(32, 243, 32) :QColor(243, 32, 32));

        if (i % (shrtStep / longStep) != 0) {
            QPoint p1(0, -(radius - 8));
             QPoint p2(0, -radius);
             painter.drawLine(p1, p2);

        } else {

            QPoint p1(0, -(radius - 14));
             QPoint p2(0, -radius);
             painter.drawLine(p1, p2);

        }
        painter.rotate(270.0 / shrtStep); // 旋转
    }




    // 绘制表盘名称和背景 矩形
    painter.restore();; // 从堆栈中弹出已保存的状态 这里什么
    QFontMetrics fm = painter.fontMetrics();
    int tx = center.x();
    int ty = int(center.y() + (radius / 1.4142));
    QString title = "仪表盘";
    QSize tsz = fm.size(Qt::TextSingleLine, title);

    QRect trect(QPoint(tx - tsz.width() / 2, ty - tsz.height() / 2), tsz);
    painter.setPen(QColor(127, 127, 127));
    painter.setBrush(QColor(173, 163, 163));

    painter.drawRoundedRect(trect.adjusted(-6, -4, 6, 4), 3, 3);

    /*trect.adjusted(-6, -4, 6, 4) 根据指定的参数调整矩形的边界，
     创建了一个新的矩形，参数依次表示左边界减去6个单位，
     上边界减去4个单位，右边界增加6个单位，下边界增加4个单位。
    */
    painter.setPen(QColor(243, 243, 243));
    painter.setBrush(Qt::NoBrush);

    painter.drawText(trect, title); // 绘制仪表盘名称
    painter.setPen(QColor(243, 243, 243));

    const int hand = radius - 21;

    for (int i = 0; i <= longStep; i++) {

        qreal angle = qDegreesToRadians(-135.0 + i*(270.0 / longStep));
        QString etext = QString::number(minV + i * (maxV - minV) / longStep);
        QPointF dirvec(qSin(angle), -qCos(angle));
        QPointF ecenter(center.x() + hand * dirvec.x(), center.y()+hand * dirvec.y());

        QSize esz = fm.size(0, etext); // QSize esz = fm.size(0, etext);：使用 QFontMetrics 对象 fm 计算刻度标签文本 etext 在当前字体下的宽度和高度，并将结果存储在 esz 变量中。


        QRectF erect(QPointF(ecenter.x() - esz.width() / 2, ecenter.y() - esz.height() / 2), esz);

        painter.drawText(erect, etext);


    }


    // 仪表盘的指针绘制
    painter.save();
    QPoint triangle[] = {{-5, 0}, {0, 25-radius}, {5, 0}}; //这里仪表盘指针由一个圆形和一个多边三角形组成
    qreal degree = -135.0 + 270.0 * (qValues - minV) / (maxV - minV);
    qDebug() << (qValues - minV) ;
    painter.translate(center); // 把画家坐标移动到当前画布的中心
    painter.rotate(degree);    // 将坐标新系统旋转到一定角度
    painter.setPen(Qt::NoPen); //设置画笔
    painter.setBrush(Qt::red); //设置画刷颜色
    painter.drawPolygon(triangle, 3); // 绘制多变三角形
    painter.setPen(QPen(QColor(214, 0, 0), 2));
    painter.drawEllipse(QPoint(), 7, 7); // 绘制圆形
    painter.restore(); // 恢复上次保存的坐标状态，操作的是一个对战对象
}
