// You may need to build the project (run Qt uic code generator) to get "ui_AboutDialog.h" resolved

#include "aboutdialog.hpp"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->ok,&QPushButton::clicked,this,[&]{
        close();
    });
}

AboutDialog::~AboutDialog()
{
    delete ui;
}