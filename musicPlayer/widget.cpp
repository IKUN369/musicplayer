#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/music.png"));
    setWindowTitle("音乐播放器1.0");

    //实例化一个媒体播放类和一个播放列表类
    player = new QMediaPlayer(this);//播放器
    playlist = new QMediaPlaylist(this);//播放列表
    playlist->setPlaybackMode(QMediaPlaylist::Loop); //循环模式
    player->setPlaylist(playlist);//获取将播放列表要播放的文件
    //信号与自定义槽进行连接
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onStateChanged(QMediaPlayer::State)));

    connect(player,SIGNAL(positionChanged(qint64)),
            this, SLOT(onPositionChanged(qint64)));

    connect(player,SIGNAL(durationChanged(qint64)),
            this, SLOT(onDurationChanged(qint64)));

    connect(playlist,SIGNAL(currentIndexChanged(int)),
            this, SLOT(onPlaylistChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

//播放状态变化更改图标
void Widget::onStateChanged(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PausedState)
    {
        ui->play->setIcon(QIcon(":/image/stop.png"));
    }
    if(state == QMediaPlayer::PlayingState)
    {
        ui->play->setIcon(QIcon(":/image/play.png"));
    }
    if(state == QMediaPlayer::StoppedState)
    {
        ui->play->setIcon(QIcon(":/image/pause.png"));
    }
}

//更新当前播放歌曲
void Widget::onPlaylistChanged(int postion)
{
    ui->listWidget->setCurrentRow(postion);
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item)
    {
        ui->labCurMedia->setText(item->text());
    }
}

//文件时长变化，更新进度条时长
void Widget::onDurationChanged(qint64 duration)
{
    ui->playSlider->setMaximum(duration);
    int secs = duration / 1000; //s
    int mins = secs / 60;       //m
    secs = secs % 60;           //余秒
    m_durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->labRatio->setText(m_positionTime + "/" + m_durationTime);
}

//当前文件播放位置变换，更新进度显示
void Widget::onPositionChanged(qint64 position)
{
    if (ui->playSlider->isSliderDown()) //正处于手动调整
        return;
    ui->playSlider->setSliderPosition(position);
    int secs = position / 1000; //s
    int mins = secs / 60;       //m
    secs = secs % 60;           //余秒
    m_positionTime = QString::asprintf("%d:%d", mins, secs);
    ui->labRatio->setText(m_positionTime + "/" + m_durationTime);
}


//添加本地歌曲到播放列表
void Widget::on_selectfile_clicked()
{
    //    QString curPash =QDir::currentPath();
    QString dlgTitle="选择音频文件";
    QString filter="音频文件(*.mp3 *.wav *.wma);;lrc文件(*.lrc);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this,dlgTitle,"../musicPlayer/music",filter);
    if(fileList.count()<1)
        return;
    for(int i = 0;i<fileList.count();i++)
    {
        QFileInfo fileInfo(fileList.at(i));
        //将选择的文件加入播放列表
        playlist->addMedia(QUrl::fromLocalFile(fileList.at(i)));
        //将选择的文件显示在文本框上
        ui->listWidget->addItem(fileInfo.fileName());
    }
    
    if (player->state() != QMediaPlayer::PlayingState)
    {
        playlist->setCurrentIndex(0);
    }
    player->play();
}

//清空播放列表
void Widget::on_playlist_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    player->stop();
}
//歌曲选择
void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo = index.row();
    playlist->setCurrentIndex(rowNo);
    
}
//播放与暂停
void Widget::on_play_clicked()
{
    if (playlist->currentIndex() < 0)
        playlist->setCurrentIndex(0);
    if (!m_playflag)
        player->play();
    else
        player->pause();
    m_playflag = !m_playflag;
}
//调节音量
void Widget::on_soundSlider_valueChanged(int value)
{
    player->setVolume(value);
    if (ui->soundSlider->value() == 0)
    {
        ui->sound->setIcon(QIcon(":/image/mute.png"));
    }
    else
    {
        ui->sound->setIcon(QIcon(":/image/sound.png"));
    }
}
//静音
void Widget::on_sound_clicked()
{
    if (!m_soundflag)
    {
        ui->sound->setIcon(QIcon(":/image/mute.png"));
        m_soundvalue = ui->soundSlider->value();
        ui->soundSlider->setValue(0);
    }
    else
    {
        ui->sound->setIcon(QIcon(":/image/sound.png"));
        ui->soundSlider->setValue(m_soundvalue);
    }
    m_soundflag = !m_soundflag;
}

void Widget::on_playSlider_valueChanged(int value)
{
    player->setPosition(value);
}

void Widget::on_video_clicked()
{

}
