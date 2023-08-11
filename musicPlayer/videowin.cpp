#include "videowin.h"
#include "ui_videowin.h"

#include <QFileDialog>
#include <QFileInfo>

VideoWin::VideoWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWin)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/video.png"));
    setWindowTitle("视频播放器1.0");
    this->resize(1920, 1080);
    ui->label->resize(1500, 800);


    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop); //循环模式
    videowidget = new QVideoWidget(ui->label);
    videowidget->resize(ui->label->size());
    player->setPlaylist(playlist);
    player->setVideoOutput(videowidget);  //设置视频显示图形界面组

    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onStateChanged(QMediaPlayer::State)));

    connect(player,SIGNAL(positionChanged(qint64)),
            this, SLOT(onPositionChanged(qint64)));

    connect(player,SIGNAL(durationChanged(qint64)),
            this, SLOT(onDurationChanged(qint64)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),
            this, SLOT(onPlaylistChanged(int)));
}

VideoWin::~VideoWin()
{
    delete ui;
}

void VideoWin::getvideoshow()
{
    this->show();
}

//根据播放状态调节图标
void VideoWin::onStateChanged(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PausedState)
    {
        ui->buttonplay->setIcon(QIcon(":/image/stop.png"));
    }
    if(state == QMediaPlayer::PlayingState)
    {
        ui->buttonplay->setIcon(QIcon(":/image/play.png"));
    }
    if(state == QMediaPlayer::StoppedState)
    {
        ui->buttonplay->setIcon(QIcon(":/image/X.png"));
    }
}
//获取播放总时长
void VideoWin::onDurationChanged(qint64 duration)
{
    ui->Slidervideo->setMaximum(duration);
    int secs = duration / 1000; //s
    int mins = secs / 60;       //m
    secs = secs % 60;           //余秒
    m_durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->labelTome->setText(m_positionTime + "/" + m_durationTime);
}
//获取当前播放时间
void VideoWin::onPositionChanged(qint64 position)
{
    if (ui->Slidervideo->isSliderDown()) //正处于手动调整
        return;
    ui->Slidervideo->setSliderPosition(position);
    int secs = position / 1000; //s
    int mins = secs / 60;       //m
    secs = secs % 60;           //余秒
    m_positionTime = QString::asprintf("%d:%d", mins, secs);
    ui->labelTome->setText(m_positionTime + "/" + m_durationTime);
}

void VideoWin::onPlaylistChanged(int postion)
{
    ui->listWidget->setCurrentRow(postion);
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item)
    {
        ui->labelcurmedia->setText(item->text());
    }
}

// 打开文件
void VideoWin::on_buttonselect_clicked()
{
    QString dlgTitle="选择视频文件";
    QString filter="mp4文件(*.mp4);;所有文件(*.*);;wmv文件(*.wmv)";
    QStringList filenamelist = QFileDialog::getOpenFileNames(this,dlgTitle,"E://QT//视频素材",filter);
    if(filenamelist.isEmpty()){
        return;
    }
    playlist->clear();
    for(int i = 0;i<filenamelist.count();i++)
    {
        //将选择的文件加入播放列表
        playlist->addMedia(QUrl::fromLocalFile(filenamelist.at(i)));
        //将选择的文件显示在文本框上
        QFileInfo fileInfo(filenamelist.at(i));
        ui->listWidget->addItem(fileInfo.fileName());
    }

    if (player->state() != QMediaPlayer::PlayingState)
    {
        playlist->setCurrentIndex(0);
    }
    player->play();
}

//开始与暂停播放
void VideoWin::on_buttonplay_clicked()
{
    if (m_playflag)
        player->play();
    else
        player->pause();
    m_playflag = !m_playflag;
}

//清空播放列表播放
void VideoWin::on_buttonstop_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    player->stop();
}

//调节音量
void VideoWin::on_Slidersound_valueChanged(int value)
{
    player->setVolume(value);
    if (ui->Slidersound->value() == 0)
    {
        ui->buttonsound->setIcon(QIcon(":/image/mute.png"));
    }
    else
    {
        ui->buttonsound->setIcon(QIcon(":/image/sound.png"));
    }
}
//静音
void VideoWin::on_buttonsound_clicked()
{

    if (!m_soundflag)
    {
        ui->buttonsound->setIcon(QIcon(":/image/mute.png"));
        m_soundvalue = ui->Slidersound->value();
        ui->Slidersound->setValue(0);
    }
    else
    {
        ui->buttonsound->setIcon(QIcon(":/image/sound.png"));
        ui->Slidersound->setValue(m_soundvalue);
    }
    m_soundflag = !m_soundflag;
}

//返回上个界面
void VideoWin::on_buttonback_clicked()
{
    emit soundwinshow();
    this->close();
}

//选择视频
void VideoWin::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo = index.row();
    playlist->setCurrentIndex(rowNo);
}

void VideoWin::on_Slidervideo_valueChanged(int value)
{
    player->setPosition(value);
}
