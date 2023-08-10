#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    void onStateChanged(QMediaPlayer::State state);
    void onPlaylistChanged(int postion);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

    void on_selectfile_clicked();

    void on_playlist_clicked();
    
    void on_listWidget_doubleClicked(const QModelIndex &index);
    
    void on_play_clicked();

    void on_soundSlider_valueChanged(int value);

    void on_sound_clicked();

    void on_playSlider_valueChanged(int value);

    void on_video_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer    *player;//播放器
    QMediaPlaylist  *playlist;//播放列表

    QString  m_durationTime;//总长度
    QString  m_positionTime;//当前播放到位置
    bool m_playflag = false;        //播放标志
    int i = 0;
    bool m_soundflag = false;       //声音标志
    int  m_soundvalue;      //当前音量

};
#endif // WIDGET_H
