#ifndef VIDEOWIN_H
#define VIDEOWIN_H

#include <QMediaPlayer>
#include <QWidget>


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
    void onStateChanged(QMediaPlayer::State state);
    void onPlaylistChanged(int postion);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

private:
    Ui::VideoWin *ui;

    QMediaPlayer    *player;//播放器
    QMediaPlaylist  *playlist;//播放列表

    QString  m_durationTime;//总长度
    QString  m_positionTime;//当前播放到位置
};

#endif // VIDEOWIN_H
