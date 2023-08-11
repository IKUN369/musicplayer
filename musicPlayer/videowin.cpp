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

    videowidget = new QVideoWidget(ui->label);
    videowidget->resize(ui->label->size());
    player = new QMediaPlayer(this);
//    player->setNotifyInterval(2000);//设置更新时间
    player->setVideoOutput(videowidget);  //设置视频显示图形界面组

    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onStateChanged(QMediaPlayer::State)));

    connect(player,SIGNAL(positionChanged(qint64)),
            this, SLOT(onPositionChanged(qint64)));

    connect(player,SIGNAL(durationChanged(qint64)),
            this, SLOT(onDurationChanged(qint64)));
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
        ui->buttonplay->setIcon(QIcon(":/image/pause.png"));
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

// 打开文件
void VideoWin::on_buttonselect_clicked()
{
    QString dlgTitle="选择视频文件";
    QString filter="mp4文件(*.mp4);;wmv文件(*.wmv);;所有文件(*.*)";
    QString afile = QFileDialog::getOpenFileName(this,dlgTitle,"E://QT//视频素材",filter);
    if(afile.isEmpty()){
        return;
    }
    QFileInfo fileInfo(afile);
    //将选择的文件显示在标签框上
    ui->labelcurmedia->setText(fileInfo.fileName());
    //设置播放文件
    player->setMedia(QUrl::fromLocalFile(afile));
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

//停止播放
void VideoWin::on_buttonstop_clicked()
{
    player->stop();
}

//调节音量
void VideoWin::on_verticalSlider_valueChanged(int value)
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
