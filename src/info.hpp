#ifndef QMOVIEPLAYER_INFO_HPP
#define QMOVIEPLAYER_INFO_HPP

#include <QDialog>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Info;
}
QT_END_NAMESPACE

class Info : public QDialog
{
    Q_OBJECT

    public:
        explicit Info(QWidget *parent = nullptr,QMediaPlayer* player = nullptr);
        ~Info() override;

    private:
        Ui::Info *ui;
};

#endif //QMOVIEPLAYER_INFO_HPP