#ifndef CLOCK_H
#define CLOCK_H

#include <QtGui/QWidget>

#include <QTimer>
#include <QPainter>
#include <QTime>


class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

    void paintEvent(QPaintEvent *event);

    int angle;
    //void change(int temp);

    QTimer *time;

private slots:
    //void change_speed();
};

#endif // CLOCK_H
