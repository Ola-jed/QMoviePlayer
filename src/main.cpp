#include "window.hpp"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("QMoviePlayer");
    QCoreApplication::setOrganizationName("QMoviePlayer");
    QCoreApplication::setApplicationVersion("1.0");
    Window w;
    if(argc > 1)
    {
        QList<QMediaContent> params{};
        for(auto i = 1;i < argc;i++) // Loading the given params for the playlist
        {
            params.append(QUrl::fromLocalFile(argv[i]));
        }
        w.playPlaylist(params);
    }
    w.show();
    return QApplication::exec();
}