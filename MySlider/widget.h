#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_m_pSlider_valueChanged(int value);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void stateChanged(QMediaPlayer::State newState);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_pushButton_play_clicked();
    void slotPos(int position);

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
};
#endif // WIDGET_H
