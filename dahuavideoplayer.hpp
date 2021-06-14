#ifndef DAHUAVIDEOPLAYER_HPP
#define DAHUAVIDEOPLAYER_HPP

#include <QMainWindow>
#include <QWidget>

class DahuaVideoPlayer : public QMainWindow
{
    Q_OBJECT
public:
    explicit DahuaVideoPlayer(QWidget *parent = nullptr);

signals:

};

#endif // DAHUAVIDEOPLAYER_HPP

/**
 * Merge the dahu sdk methods into the gui class so that the vidoe buffer data
 * is easily available to the window class from the realplay callback
 *
 * Design a window button to start, login, play video and then end process
 *
 * May need to use vlc-qt library to play video
 *
  **/
