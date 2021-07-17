#ifndef QMOVIEPLAYER_RECENTFILESMANAGER_HPP
#define QMOVIEPLAYER_RECENTFILESMANAGER_HPP

#include <QList>
#include <QString>
#include <QSettings>

class RecentFilesManager
{
    public:
        RecentFilesManager();
        QList<QVariant> recentFiles() const;
        void addRecentFile(const QString &filePath);
        const QString RECENT_FILES = "recent files";

    private:
        QList<QVariant> recentFilesList;
        QSettings settings;
};

#endif //QMOVIEPLAYER_RECENTFILESMANAGER_HPP
