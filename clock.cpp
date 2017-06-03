#include "clock.h"
#include <QPen>
#include <QDebug>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{

    angle = 0;
    time = new QTimer;


    //update()会自动产生重绘消息，调用paintEvent()

    time->start(1000);   //启动定时器
    resize(300, 300);  //设置窗体大小
    setWindowTitle(tr("clock"));

    connect(time, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新

    //connect(time, SIGNAL(timeout()), this, SLOT(change_speed()));

}

Clock::~Clock()
{

}

void Clock::paintEvent(QPaintEvent *event)
{
    //定义表针的三个顶点，以便后面的填充
    static const QPoint hourHand[3] =
    {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(0, -40)
    };

    static const QPoint minuteHand[3] =
    {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(0, -70)
    };
    static const QPoint secondHand[3] =
    {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(0, -90)

    };

    static const QPoint Hand[4] =
    {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(2, -90),
        QPoint(-2, -90)
    };
    int side = qMin(width(), height());//绘制的范围
    QTime time = QTime::currentTime();//获取当期时间
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);//绘制的图像反锯齿
    painter.translate(width()/2, height()/2);//重新定位坐标起始点，原点放到窗体中央
    painter.scale(side/300.0, side/300.0);//设置画布的边界，用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

    painter.setPen(Qt::red);
    QString timeStr = QTime::currentTime().toString();//绘制当前时间
    painter.drawText(-40, 30, 80, 30, Qt::AlignHCenter | Qt::AlignTop, timeStr);

    //painter.drawText(50, 50, 50, 50, Qt::AlignHCenter | Qt::AlignTop, "kdfjkd");
    painter.setPen(Qt::NoPen);//填充指针，不需要边线
    //painter.setPen(QPen(Qt::green));
    painter.setBrush(Qt::green);//

    painter.save();//保存Painter的状态，保存的是当前的坐标状态，如果不保存，画完后坐标改变不方便画下一个
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    //painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(hourHand, 3);//填充时针的区域
    //painter.drawPolygon(Hand, 4);
    //painter.drawLine(0, 0, 60, 60);
    painter.restore();//回复坐标系，不回复无法确定时分针的角度

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();

    painter.setPen(Qt::red);
    for(int j = 0; j < 60; j++)
    {
        if((j % 5) != 0)
            painter.drawLine(0, -92, 0, -96);
        painter.rotate(6.0);
    }

    painter.setPen(Qt::blue);
    for(int i = 0; i < 12; i++)
    {

        painter.drawLine(0, -88, 0, -96);
        if(i == 0)
            painter.drawText(-10, -80, 20, 20, Qt::AlignHCenter | Qt::AlignTop, QString::number(12));
        else
            painter.drawText(-10, -80, 20, 20, Qt::AlignHCenter | Qt::AlignTop, QString::number(i));

        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();

    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0, 0), 2, 2);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPoint(0,0),97,97);

//    painter.setBrush(Qt::NoBrush);
//    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
//    painter.drawEllipse(QPoint(0, 0), 100, 100);


}

/*void Clock::paintEvent(QPaintEvent *event)
{

       //下面三个数组用来定义表针的三个顶点，以便后面的填充
        static const QPoint hourHand[3] = {
            QPoint(3, 8),
            QPoint(-3, 8),
            QPoint(0, -40)
        };
        static const QPoint minuteHand[3] = {
            QPoint(3, 8),
            QPoint(-3, 8),
            QPoint(0, -70)
        };
        static const QPoint secondHand[3] = {
            QPoint(3, 8),
            QPoint(-3, 8),
            QPoint(0, -90)
        };//秒针
        //填充表针的颜色
        QColor hourColor(127, 0, 127);  //分针颜色(第四个表示不透明度)
        QColor minuteColor(0, 127, 127, 191);
        QColor secondColor(127, 127, 0, 127);
        //...





        int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)
        QTime time = QTime::currentTime();   //获取当前的时间
        QPainter painter(this);              //声明用来绘图用的painter

        painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
        painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央
        painter.scale(side / 300.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全



        painter.setPen(Qt::red);   //填充时针，不需要边线所以NoPen
        QString timeStr= QTime::currentTime().toString();     //绘制当前的时间
        painter.drawText(-40,30,80,30,Qt::AlignHCenter | Qt::AlignTop, timeStr);



        //...
        painter.setPen(Qt::NoPen);   //填充时针，不需要边线所以NoPen
        painter.setBrush(hourColor);  //画刷颜色设定
        painter.save();  //保存painter的状态，保存的是当前的坐标状态，如果不保存，画完之后坐标以改变不方便画下一个
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0))); //将painter（的”视角“）根据时间参数转移(30° * (小时 + 分钟 / 60))
        painter.drawConvexPolygon(hourHand, 3);  //填充时针的区域
        painter.restore();

         //后面的跟前面的类似，分别绘制了分针和秒针，及相应的刻度
        painter.setPen(Qt::NoPen);
        painter.setBrush(minuteColor);
        painter.save();
        painter.rotate(6.0 * (time.minute() + time.second() / 60.0));  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
        painter.drawConvexPolygon(minuteHand, 3);  //填充分针部分
        painter.restore();

        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);
        painter.save();
        painter.rotate(6.0 * time.second());  //设置旋转(6° * 秒)
        painter.drawConvexPolygon(secondHand, 3);  //设置填充
        painter.restore();
        //...


      //...
        painter.setPen(minuteColor);
        for (int j = 0; j < 60; ++j) {  //循环60次，绘制表盘（其实可以从1开始，到59，提高一点效率）
            if ((j % 5) != 0)           //判断是否能被5整除(能被5整除表示是正点刻度，暂不绘制)
                painter.drawLine(0, -92, 0, -96);  //不是正点刻度，绘制长4个像素的直线
            painter.rotate(6.0);   //循环60次，每次旋转6度，所以不用save和restore
        }
        painter.setPen(hourColor);    //下面画表示小时的刻度，此时要用到画笔（因为要划线）
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(0, -88, 0, -96);     //写上刻度数字
            if (i == 0)  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(12));
            else  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(i));
            painter.rotate(30.0);
        }



        //...
        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);
        painter.save();
        painter.rotate(6.0 * time.second());  //设置旋转(6° * 秒)
        painter.drawConvexPolygon(secondHand, 3);  //设置填充
        painter.restore();

        painter.setBrush(Qt::black);
        painter.drawEllipse(QPoint(0,0),2,2);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::black);
        painter.drawEllipse(QPoint(0,0),97,97);
        //...



}*/

//void Clock::paintEvent(QPaintEvent *event)
//{
//    static const QPoint hourHand1[3] = {
//        QPoint(200, 195),
//        QPoint(200, 205),
//        QPoint(100, 200)
//    };

//    //定义表针的三个顶点，以便后面的填充
//    static const QPoint hourHand[3] =
//    {
//        QPoint(3, 8),
//        QPoint(-3, 8),
//        QPoint(0, -40)
//    };

//    QColor hourColor(127, 0, 127);

//    QTime time = QTime::currentTime();

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
////    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
////    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
//    painter.translate(100, 100);
////    painter.drawEllipse(0, 0, 200, 200);
////    //painter.drawEllipse();
////    painter.save();
////    painter.restore();


////    painter.setPen(Qt::NoPen);
////    painter.setBrush(hourColor);
////    painter.save();
////    painter.rotate(30.0);
////    painter.drawConvexPolygon(hourHand, 3);
////    painter.restore();

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QBrush(Qt::red));
//    painter.save();
//    painter.rotate(6.0 * time.second());
//    //painter.drawLine(0, 0, 30, 30);
//    painter.drawConvexPolygon(hourHand, 3);

//    qDebug() << angle << endl;

//    painter.restore();

////    QPainterPath path;
////    path.moveTo(80, 320);
////    path.cubicTo(200, 80, 320, 80, 480, 320);

////    painter.setPen(QPen(Qt::black, 8));
//    //    painter.drawPath(path);
//}
////static int T = 0;
////void Clock::change_speed()
////{
////    T += 5;
////    change(T);
////}

////void Clock::change(int temp)
////{
////    angle = temp;
////    update();
////}


