#include "aboutdialog.hpp"
#include "../include/ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->ok,&QPushButton::clicked,[this]{
        close();
    });
}

AboutDialog::~AboutDialog()
{
    delete ui;
}