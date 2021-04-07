// You may need to build the project (run Qt uic code generator) to get "ui_Settings.h" resolved

#include "settings.hpp"
#include "ui_Settings.h"

Settings::Settings(QWidget *parent,int brightness,
                    int hue,int saturation,int contrast) :
        QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->brightnessSlider->setValue(brightness);
    ui->hueSlider->setValue(hue);
    ui->contrastSlider->setValue(contrast);
    ui->saturationSlider->setValue(saturation);
    connect(ui->cancel,&QPushButton::clicked,this,[&]{
        close();
    });
    connect(ui->ok,&QPushButton::clicked,this,[&]{
        emit brightnessChanged(ui->brightnessSlider->value());
        emit saturationChanged(ui->saturationSlider->value());
        emit hueChanged(ui->hueSlider->value());
        emit contrastChanged(ui->contrastSlider->value());
        close();
    });
}

Settings::~Settings()
{
    delete ui;
}