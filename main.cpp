#include "window.hpp"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("QMoviePlayer");
    QCoreApplication::setOrganizationName("QMoviePlayer");
    QCoreApplication::setApplicationVersion("1.0");
    Window w;
    if (argc > 1) // We load all the media given in a playlist
    {
        QList<QMediaContent> params{};
        for (auto            i = 1; i < argc; i++)
        {
            params.append(QUrl::fromLocalFile(argv[i]));
        }
        w.playPlaylist(params);
    }
    w.show();
    return QApplication::exec();
}