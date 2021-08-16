#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));      //通过对媒体播放进度的监视,从而控制滑动条的显示状态和位置
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));      //用来设置滑动条的范围
    connect(player, &QMediaPlayer::stateChanged, this, &Widget::stateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Widget::mediaStatusChanged);
    connect(ui->m_pSlider, &MySlider::costomSliderClicked, this, &Widget::slotPos);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_m_pSlider_valueChanged(int value)
{
//    ui->labelValue->setText(QString::number(value));
//    ui->labelSubValue->setText(QString::number(ui->m_pSlider->maximum() - value));
}

void Widget::positionChanged(qint64 position)
{
    ui->m_pSlider->setValue(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->labelValue->setText(duration.toString(tr("mm:ss")));
    QTime sub(0, (ui->m_pSlider->maximum() - position) / 60000, qRound((position % 60000) / 1000.0));
    ui->labelSubValue->setText(sub.toString(tr("mm:ss")));
}

void Widget::durationChanged(qint64 duration)
{
    ui->m_pSlider->setRange(0, duration);
    ui->m_pSlider->setEnabled(duration > 0);
}

void Widget::stateChanged(QMediaPlayer::State newState)
{
    if (newState == QMediaPlayer::State::PlayingState) {
        ui->pushButton_play->setText(QStringLiteral("Pause"));
    }
    else if(newState == QMediaPlayer::State::PausedState){
        ui->pushButton_play->setText(QStringLiteral("Play"));
    }
}

void Widget::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::MediaStatus::EndOfMedia){
       ui->pushButton_play->setText(QStringLiteral("Open"));
       ui->m_pSlider->setValue(ui->m_pSlider->minimum());
       ui->labelValue->setText("");
       ui->labelSubValue->setText("");
    }
}

void Widget::on_pushButton_play_clicked()
{
    if(player->state() == QMediaPlayer::State::PlayingState){
        player->pause();
    }
    else if(player->state() == QMediaPlayer::State::PausedState){
        player->play();
    }
    else{
        const QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("MP3 files(*.mp3)\n WAV(*.wav)\n All files (*.*)"));
        if(filename.length() == 0) {
            QMessageBox::information(NULL, tr("filename"), tr("You didn't select any files."));
        }
        else {
            player->setMedia(QUrl::fromLocalFile(filename));
            player->play();
        }
    }
}

void Widget::slotPos(int position)
{
    if(player->state() == QMediaPlayer::State::StoppedState){
        return;
    }

    if (qAbs(player->position() - position) > 99) {
        player->setPosition(position);
    }
}
