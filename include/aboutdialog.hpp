#ifndef QMOVIEPLAYER_ABOUTDIALOG_HPP
#define QMOVIEPLAYER_ABOUTDIALOG_HPP

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AboutDialog;
}
QT_END_NAMESPACE

class AboutDialog : public QDialog
{
Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog() override;

private:
    Ui::AboutDialog *ui;
};

#endif //QMOVIEPLAYER_ABOUTDIALOG_HPP
