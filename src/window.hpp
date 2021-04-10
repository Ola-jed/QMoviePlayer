#ifndef QMOVIEPLAYER_WINDOW_HPP
#define QMOVIEPLAYER_WINDOW_HPP

#include "aboutdialog.hpp"
#include "settings.hpp"
#include "info.hpp"
#include <QMainWindow>
#include <QApplication>
#include <QMimeData>
#include <QDirIterator>
#include <QFileInfo>
#include <QScreen>
#include <QString>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>
#include <QMediaPlaylist>
#include <QSet>
#include <QList>

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
        const QSet<QString> SUPPORTED_FORMATS {"mov","mp4","mpg","m4v","3gp","avi","3g2"}; // Supported extensions
        Ui::Window *ui;
        QMediaPlayer *player;
        QMediaPlaylist *playlist;
        bool onPlaying{true};
        QString durationAsStr;
        bool mediaIsSupported(const QString &mediaPath) const;

        void makeConnections();
        void makeMenuConnections();
        void makeButtonConnections();
        void applyLayout();

    private slots:
        void onOpenFile();
        void onOpenFolder();
        void onQuit();
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