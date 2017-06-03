#include "clock.h"
#include <QPen>
#include <QDebug>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{

    angle = 0;
    time = new QTimer;


    //update()���Զ������ػ���Ϣ������paintEvent()

    time->start(1000);   //������ʱ��
    resize(300, 300);  //���ô����С
    setWindowTitle(tr("clock"));

    connect(time, SIGNAL(timeout()), this, SLOT(update()));  //�����źŲۣ���ʱ����ʱ�����������

    //connect(time, SIGNAL(timeout()), this, SLOT(change_speed()));

}

Clock::~Clock()
{

}

void Clock::paintEvent(QPaintEvent *event)
{
    //���������������㣬�Ա��������
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
    int side = qMin(width(), height());//���Ƶķ�Χ
    QTime time = QTime::currentTime();//��ȡ����ʱ��
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);//���Ƶ�ͼ�񷴾��
    painter.translate(width()/2, height()/2);//���¶�λ������ʼ�㣬ԭ��ŵ���������
    painter.scale(side/300.0, side/300.0);//���û����ı߽磬�ô����ߵ���Сֵ������ʱ�ӵĴ�С����ֹ�������쵼�µ�ʱ�ӱ����Լ���ʾ��ȫ

    painter.setPen(Qt::red);
    QString timeStr = QTime::currentTime().toString();//���Ƶ�ǰʱ��
    painter.drawText(-40, 30, 80, 30, Qt::AlignHCenter | Qt::AlignTop, timeStr);

    //painter.drawText(50, 50, 50, 50, Qt::AlignHCenter | Qt::AlignTop, "kdfjkd");
    painter.setPen(Qt::NoPen);//���ָ�룬����Ҫ����
    //painter.setPen(QPen(Qt::green));
    painter.setBrush(Qt::green);//

    painter.save();//����Painter��״̬��������ǵ�ǰ������״̬����������棬���������ı䲻���㻭��һ��
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    //painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(hourHand, 3);//���ʱ�������
    //painter.drawPolygon(Hand, 4);
    //painter.drawLine(0, 0, 60, 60);
    painter.restore();//�ظ�����ϵ�����ظ��޷�ȷ��ʱ����ĽǶ�

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

       //�������������������������������㣬�Ա��������
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
        };//����
        //���������ɫ
        QColor hourColor(127, 0, 127);  //������ɫ(���ĸ���ʾ��͸����)
        QColor minuteColor(0, 127, 127, 191);
        QColor secondColor(127, 127, 0, 127);
        //...





        int side = qMin(width(), height());  //���Ƶķ�Χ(��������Сֵ)
        QTime time = QTime::currentTime();   //��ȡ��ǰ��ʱ��
        QPainter painter(this);              //����������ͼ�õ�painter

        painter.setRenderHint(QPainter::Antialiasing);//���Ƶ�ͼ�񷴾��
        painter.translate(width() / 2, height() / 2);//���¶�λ������ʼ�㣬������ԭ��ŵ����������
        painter.scale(side / 300.0, side / 300.0);//�趨�����ı߽�,�ô����ߵ���Сֵ������ʱ�ӵĴ�С����ֹ�������쵼�µ�ʱ�ӱ����Լ���ʾ��ȫ



        painter.setPen(Qt::red);   //���ʱ�룬����Ҫ��������NoPen
        QString timeStr= QTime::currentTime().toString();     //���Ƶ�ǰ��ʱ��
        painter.drawText(-40,30,80,30,Qt::AlignHCenter | Qt::AlignTop, timeStr);



        //...
        painter.setPen(Qt::NoPen);   //���ʱ�룬����Ҫ��������NoPen
        painter.setBrush(hourColor);  //��ˢ��ɫ�趨
        painter.save();  //����painter��״̬��������ǵ�ǰ������״̬����������棬����֮�������Ըı䲻���㻭��һ��
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0))); //��painter���ġ��ӽǡ�������ʱ�����ת��(30�� * (Сʱ + ���� / 60))
        painter.drawConvexPolygon(hourHand, 3);  //���ʱ�������
        painter.restore();

         //����ĸ�ǰ������ƣ��ֱ�����˷�������룬����Ӧ�Ŀ̶�
        painter.setPen(Qt::NoPen);
        painter.setBrush(minuteColor);
        painter.save();
        painter.rotate(6.0 * (time.minute() + time.second() / 60.0));  //����ת(�Ƕ� = 6�� * (���� + �� / 60))
        painter.drawConvexPolygon(minuteHand, 3);  //�����벿��
        painter.restore();

        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);
        painter.save();
        painter.rotate(6.0 * time.second());  //������ת(6�� * ��)
        painter.drawConvexPolygon(secondHand, 3);  //�������
        painter.restore();
        //...


      //...
        painter.setPen(minuteColor);
        for (int j = 0; j < 60; ++j) {  //ѭ��60�Σ����Ʊ��̣���ʵ���Դ�1��ʼ����59�����һ��Ч�ʣ�
            if ((j % 5) != 0)           //�ж��Ƿ��ܱ�5����(�ܱ�5������ʾ������̶ȣ��ݲ�����)
                painter.drawLine(0, -92, 0, -96);  //��������̶ȣ����Ƴ�4�����ص�ֱ��
            painter.rotate(6.0);   //ѭ��60�Σ�ÿ����ת6�ȣ����Բ���save��restore
        }
        painter.setPen(hourColor);    //���滭��ʾСʱ�Ŀ̶ȣ���ʱҪ�õ����ʣ���ΪҪ���ߣ�
        for (int i = 0; i < 12; ++i) {
            painter.drawLine(0, -88, 0, -96);     //д�Ͽ̶�����
            if (i == 0)  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(12));
            else  painter.drawText(-10,-88,20,20,Qt::AlignHCenter | Qt::AlignTop,QString::number(i));
            painter.rotate(30.0);
        }



        //...
        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);
        painter.save();
        painter.rotate(6.0 * time.second());  //������ת(6�� * ��)
        painter.drawConvexPolygon(secondHand, 3);  //�������
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

//    //���������������㣬�Ա��������
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


