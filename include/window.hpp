#ifndef QMOVIEPLAYER_WINDOW_HPP
#define QMOVIEPLAYER_WINDOW_HPP

#include "info.hpp"
#include "settings.hpp"
#include "aboutdialog.hpp"
#include "recentfilesmanager.hpp"
#include <QSet>
#include <QStyle>
#include <QScreen>
#include <QFileInfo>
#include <QMimeData>
#include <QMainWindow>
#include <QFileDialog>
#include <QCloseEvent>
#include <QApplication>
#include <QDirIterator>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QGuiApplication>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
Q_OBJECT

public:
    explicit Window(QMainWindow *parent = nullptr);
    ~Window() override;

public slots:
    void playMedia(const QString &mediaPath);
    void playPlaylist(const QList<QMediaContent> &contentToPlay);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    RecentFilesManager  recentFilesManager;
    const QSet<QString> SUPPORTED_FORMATS{"mov", "mp4", "mpg", "m4v", "3gp", "avi", "3g2"};
    Ui::Window          *ui;
    QMediaPlayer        *player;
    QMediaPlaylist      *playlist;
    bool                onPlaying{true};
    QString             durationAsStr;
    [[nodiscard]] bool mediaIsSupported(const QString &mediaPath) const;

    void makeConnections();
    void makeMenuConnections();
    void makeButtonConnections();
    void applyLayout();
    void buildRecentlyOpenedList();

private slots:
    void onOpenFile();
    void onOpenFolder();
    void onPlay();
    void onPause();
    void onPlayOrPause();
    void onStop();
    void onPrevious();
    void onNext();
    void onRewind();
    void onFastForward();
    void onFirst();
    void onLast();
    void onRandom();
    void onReplay();
    void onLoop();
    void onVolumeUp();
    void onVolumeDown();
    void onVolumeMute();
    void onFullscreen();
    void onScreenshot();
    void onAbout();
    void onUpdateVolumeLabel(int volume);
    void setVolume(int volumeToSet);
    void onLoadFailed();
    void onUpdateTotalDuration(qint64 duration);
    void onUpdateDurationLabel(qint64 duration);
    void onUpdatePositionSlider(qint64 duration);
    void updateSlider(int positionToSet);
    void onSettings();
    void onInfo();
};

#endif //QMOVIEPLAYER_WINDOW_HPP