#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>

class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
signals:
    //自定义的鼠标单击信号，用于捕获并处理
    void costomSliderClicked(int position);

private:
    bool m_bPressed = false;
};

#endif // MYSLIDER_H
