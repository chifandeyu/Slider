#include "myslider.h"
#include <QEvent>
#include <QApplication>
#include <QMouseEvent>
MySlider::MySlider(QWidget *parent) : QSlider(parent)
{
}

void MySlider::mousePressEvent(QMouseEvent * ev)
{
    ev->ignore();
    m_bPressed = true;
    //获取鼠标的位置，这里并不能直接从ev中取值（因为如果是拖动的话，鼠标开始点击的位置没有意义了）
    double pos = ev->pos().x() / (double)width();
    int position = pos * (maximum() - minimum()) + minimum();
    setValue(position);
    //发送自定义的鼠标单击信号
    emit costomSliderClicked(position);
    //QEvent evEvent(static_cast<QEvent::Type>(QEvent::User + 1));
    //QCoreApplication::sendEvent(parentWidget(), &evEvent);
}

void MySlider::mouseMoveEvent(QMouseEvent* ev)
{
    QSlider::mouseMoveEvent(ev);
    if (m_bPressed) {
        double pos = ev->pos().x() / (double)width();
        int position = pos * (maximum() - minimum()) + minimum();
        setValue(position);
        //QEvent evEvent(static_cast<QEvent::Type>(QEvent::User + 2));
        //QCoreApplication::sendEvent(parentWidget(), &evEvent);
        //发送自定义的鼠标单击信号
        emit costomSliderClicked(position);
    }
}

void MySlider::mouseReleaseEvent(QMouseEvent* ev)
{
    QSlider::mouseReleaseEvent(ev);
    m_bPressed = false;
}
