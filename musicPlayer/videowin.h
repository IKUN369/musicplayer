#ifndef VIDEOWIN_H
#define VIDEOWIN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QtMultimediaWidgets>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QVideoWidget>

namespace Ui {
class VideoWin;
}

class VideoWin : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWin(QWidget *parent = nullptr);
    ~VideoWin();
public slots:

   void getvideoshow();


    void onStateChanged(QMediaPlayer::State state);
    //    void onPlaylistChanged(int postion);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
signals:
    void soundwinshow();//返回主界面


private slots:
    void on_buttonplay_clicked();

    void on_buttonselect_clicked();

    void on_buttonstop_clicked();

    void on_buttonback_clicked();

    void on_buttonsound_clicked();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::VideoWin *ui;

    QGraphicsScene *scene;//设置场景
    QGraphicsVideoItem *videoItem;

    QVideoWidget *videowidget;

//    QMediaPlaylist  *playlist;//播放列表
    QMediaPlayer    *player;//播放器
    QString  m_durationTime;//总长度
    QString  m_positionTime;//当前播放到位置

    bool m_playflag = false;        //播放标志
//    int i = 0;                      //测试变量
    bool m_soundflag = false;       //声音标志
    int  m_soundvalue;      //当前音量
};

#endif // VIDEOWIN_H
