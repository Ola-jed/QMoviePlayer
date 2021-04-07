// You may need to build the project (run Qt uic code generator) to get "ui_Window.h" resolved
#include "window.hpp"
#include "ui_Window.h"

Window::Window(QMainWindow *parent) :
        QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    applyLayout();
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setVideoOutput(ui->videoWidget);
    makeConnections();
}

Window::~Window()
{
    delete player;
    delete ui;
}

void Window::applyLayout()
{
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                    size(),QGuiApplication::primaryScreen()->availableGeometry()));
    resize(QGuiApplication::primaryScreen()->availableSize() * 3/5);
}

void Window::makeConnections()
{
    makeMenuConnections();
    makeButtonConnections();
    connect(player,&QMediaPlayer::volumeChanged,this,&Window::onUpdateVolumeLabel);
    connect(ui->volumeSlider,&QSlider::valueChanged,this,&Window::setVolume);
    connect(ui->durationSlider,&QSlider::valueChanged,this,&Window::updateSlider);
    connect(playlist,&QMediaPlaylist::loadFailed,this,&Window::onLoadFailed);
    connect(player,&QMediaPlayer::durationChanged,this,&Window::onUpdateTotalDuration);
    connect(player,&QMediaPlayer::positionChanged,this,&Window::onUpdateDurationLabel);
}

void Window::makeMenuConnections()
{
    connect(ui->openFile,&QAction::triggered,this,&Window::onOpenFile);
    connect(ui->openFolder,&QAction::triggered,this,&Window::onOpenFolder);
    connect(ui->quit,&QAction::triggered,this,&Window::onQuit);
    connect(ui->playAction,&QAction::triggered,this,&Window::onPlay);
    connect(ui->pauseAction,&QAction::triggered,this,&Window::onPause);
    connect(ui->previousAction,&QAction::triggered,this,&Window::onPrevious);
    connect(ui->nextAction,&QAction::triggered,this,&Window::onNext);
    connect(ui->increaseSound,&QAction::triggered,this,&Window::onVolumeUp);
    connect(ui->decreaseSound,&QAction::triggered,this,&Window::onVolumeDown);
    connect(ui->mute,&QAction::triggered,this,&Window::onVolumeMute);
    connect(ui->fullscreen,&QAction::triggered,this,&Window::onFullscreen);
    connect(ui->screenshot,&QAction::triggered,this,&Window::onScreenshot);
    connect(ui->settings,&QAction::triggered,this,&Window::onSettings);
    connect(ui->mediaInfos,&QAction::triggered,this,&Window::onInfo);
    connect(ui->about,&QAction::triggered,this,&Window::onAbout);
    connect(ui->aboutQt,&QAction::triggered,this,&QApplication::aboutQt);
}

void Window::makeButtonConnections()
{
    connect(ui->playPause,&QPushButton::clicked,this,&Window::onPlayOrPause);
    connect(ui->stop,&QPushButton::clicked,this,&Window::onStop);
    connect(ui->previous,&QPushButton::clicked,this,&Window::onPrevious);
    connect(ui->next,&QPushButton::clicked,this,&Window::onNext);
    connect(ui->rewind,&QPushButton::clicked,this,&Window::onRewind);
    connect(ui->fastForward,&QPushButton::clicked,this,&Window::onFastForward);
    connect(ui->firstMedia,&QPushButton::clicked,this,&Window::onFirst);
    connect(ui->lastMedia,&QPushButton::clicked,this,&Window::onLast);
    connect(ui->randomMedia,&QPushButton::clicked,this,&Window::onRandom);
    connect(ui->reload,&QPushButton::clicked,this,&Window::onReplay);
    connect(ui->repeat,&QPushButton::clicked,this,&Window::onLoop);
}

void Window::onOpenFile()
{
    auto const fileToOpen{QFileDialog::getOpenFileName(this,"Open a file","",
                                                       tr("Videos (*.mov *.mp4 *.mpg *.m4v *.3gp *.avi *.3g2)"))};
    if(fileToOpen.isEmpty())
    {
        QMessageBox::warning(this,"Open","Invalid file name");
        return;
    }
    playMedia(fileToOpen);
}

void Window::onOpenFolder()
{
    auto const dirToOpen{QFileDialog::getExistingDirectory(this,"Open a folder")};
    if(dirToOpen.isEmpty())
    {
        QMessageBox::warning(this,"Open","Invalid directory");
        return;
    }
    QList<QMediaContent> mediaInDir{};
    QDirIterator mediaDirIterator{dirToOpen};
    QString tmpMedia;
    while(mediaDirIterator.hasNext() && QFileInfo(tmpMedia = mediaDirIterator.next()).isReadable())
    {
        if(mediaIsSupported(tmpMedia))
        {
            mediaInDir.push_back(QUrl::fromLocalFile(tmpMedia));
        }
    }
    playPlaylist(mediaInDir);
}

void Window::onQuit()
{
    qApp->quit();
}

void Window::onPlay()
{
    onPlaying = true;
    player->play();
}

void Window::onPause()
{
    onPlaying = false;
    player->pause();
}

void Window::onPlayOrPause()
{
    if(onPlaying)
    {
        onPause();
    }
    else
    {
        onPlay();
    }
}

void Window::onStop()
{
    player->stop();
}

void Window::onPrevious()
{
    if(playlist->currentIndex() - 1 >= 0)
    {
        playlist->previous();
    }
}

void Window::onNext()
{
    if(playlist->currentIndex() < playlist->mediaCount() - 1)
    {
        playlist->next();
    }
}

void Window::onRewind()
{
    if(player->position() - 10 > 0)
    {
        onUpdatePositionSlider(player->position() - 10);
    }
}

void Window::onFastForward()
{
    if(player->position() + 10 < player->duration())
    {
        onUpdatePositionSlider(player->position() + 10);
    }
}

void Window::onFirst()
{
    playlist->setCurrentIndex(0);
}

void Window::onLast()
{
    playlist->setCurrentIndex(playlist->mediaCount() - 1);
}

void Window::onRandom()
{
    playlist->shuffle();
    onNext();
}

void Window::onReplay()
{
    playlist->setCurrentIndex(playlist->currentIndex());
}

void Window::onLoop()
{
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}

void Window::onVolumeUp()
{
    auto const currentVolume{player->volume()};
    if(currentVolume + 5 > 100)
    {
        return;
    }
    setVolume(currentVolume + 5);
}

void Window::onVolumeDown()
{
    auto const currentVolume{player->volume()};
    if(currentVolume - 5 > 100)
    {
        return;
    }
    setVolume(currentVolume - 5);
}

void Window::onVolumeMute()
{
    player->setMuted(ui->mute->isChecked());
}

void Window::setVolume(int volumeToSet)
{
    if((volumeToSet < 0) || (volumeToSet > 100))
    {
        return;
    }
    player->setVolume(volumeToSet);
    ui->volumeSlider->setValue(volumeToSet);
}

void Window::onUpdateVolumeLabel(int volume)
{
    ui->volumeIndication->setText(QString("%1 %").arg(volume));
}

void Window::onFullscreen()
{
    if(ui->fullscreen->isChecked())
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
}

void Window::onScreenshot()
{
    onPause();
    auto screen = QGuiApplication::primaryScreen();
    if(screen == nullptr)
    {
        return;
    }
    auto const screenName = QFileDialog::getSaveFileName(this,"Screenshot","screenshot.png");
    if(screenName.isEmpty())
    {
        QMessageBox::warning(this,"Save screenshot","Invalid filename");
    }
    else
    {
        if(screen->grabWindow(winId()).toImage().save(screenName))
        {
            QApplication::beep();
        }
        else
        {
            QMessageBox::warning(this,"Screenshot","Could not take the screenshot");
        }
    }
    onPlay();
}

void Window::onAbout()
{
    auto aboutDialog = new AboutDialog(this);
    aboutDialog->show();
}

void Window::playMedia(const QString &mediaPath)
{
    playlist->addMedia(QUrl::fromLocalFile(mediaPath));
    player->setPlaylist(playlist);
    player->play();
}

void Window::playPlaylist(const QList<QMediaContent> &contentToPlay)
{
    playlist->addMedia(contentToPlay);
    player->setPlaylist(playlist);
    player->play();
}

bool Window::mediaIsSupported(const QString &mediaPath) const
{
    auto const ext{QFileInfo{mediaPath}.suffix()};
    return SUPPORTED_FORMATS.contains(ext);
}

void Window::onLoadFailed()
{
    QMessageBox::warning(this,"Loading","Loading failed : "+playlist->errorString());
}

void Window::onUpdateTotalDuration(qint64 duration)
{
    const auto h = duration / 3600000;
    duration -= h * 3600000;
    const auto m = duration / 60000;
    duration -= m * 60000;
    const auto s = duration / 1000;
    durationAsStr = QStringLiteral("%1").arg(h,2,10,QLatin1Char('0')) + ":" +
                    QStringLiteral("%1").arg(m,2,10, QLatin1Char('0')) + ":" +
                    QStringLiteral("%1").arg(s,2,10, QLatin1Char('0'));
    ui->durationSlider->setMaximum(player->duration());
    onUpdatePositionSlider(duration);
}

void Window::onUpdateDurationLabel(qint64 duration)
{
    onUpdatePositionSlider(duration);
    const auto h = duration / 3600000;
    duration -= h * 3600000;
    const auto m = duration / 60000;
    duration -= m * 60000;
    const auto s = duration / 1000;
    const QString currentDuration{QStringLiteral("%1").arg(h,2,10,QLatin1Char('0')) + ":" +
                    QStringLiteral("%1").arg(m,2,10, QLatin1Char('0')) + ":" +
                    QStringLiteral("%1").arg(s,2,10, QLatin1Char('0'))};
    ui->durationLabel->setText(currentDuration+" / "+durationAsStr);
}

void Window::onUpdatePositionSlider(qint64 duration)
{
    ui->durationSlider->setValue(duration);
}

void Window::updateSlider(int positionToSet)
{
    player->setPosition(positionToSet);
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void Window::dropEvent(QDropEvent *event)
{
    const auto mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        const auto urlList {mimeData->urls()};
        playMedia(urlList[0].toString().right(urlList[0].toString().length() - 7));
    }
}

void Window::onSettings()
{
    auto settings = new Settings(this,ui->videoWidget->brightness(),
                ui->videoWidget->hue(),ui->videoWidget->saturation(),ui->videoWidget->contrast());
    connect(settings,&Settings::brightnessChanged,this,[&](int value){
        ui->videoWidget->setBrightness(value);
    });
    connect(settings,&Settings::hueChanged,this,[&](int value){
        ui->videoWidget->setHue(value);
    });
    connect(settings,&Settings::saturationChanged,this,[&](int value){
        ui->videoWidget->setSaturation(value);
    });
    connect(settings,&Settings::contrastChanged,this,[&](int value){
        ui->videoWidget->setContrast(value);
    });
    settings->show();
}

void Window::onInfo()
{
    auto infoWindow = new Info(this,player);
    infoWindow->show();
}