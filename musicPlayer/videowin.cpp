#include "videowin.h"
#include "ui_videowin.h"

VideoWin::VideoWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWin)
{
    ui->setupUi(this);
}

VideoWin::~VideoWin()
{
    delete ui;
}

void VideoWin::onStateChanged(QMediaPlayer::State state)
{

}

void VideoWin::onPlaylistChanged(int postion)
{

}

void VideoWin::onDurationChanged(qint64 duration)
{

}

void VideoWin::onPositionChanged(qint64 position)
{

}
