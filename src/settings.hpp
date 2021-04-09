#ifndef QMOVIEPLAYER_SETTINGS_HPP
#define QMOVIEPLAYER_SETTINGS_HPP

#include <QPushButton>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Settings;
}
QT_END_NAMESPACE

class Settings : public QDialog
{
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr,int brightness = 0,
                        int hue = 0,int saturation = 0,int contrast = 0);
        ~Settings() override;

    private:
        Ui::Settings *ui;

    signals:
        void brightnessChanged(int);
        void hueChanged(int);
        void contrastChanged(int);
        void saturationChanged(int);

};

#endif //QMOVIEPLAYER_SETTINGS_HPP
