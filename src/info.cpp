// You may need to build the project (run Qt uic code generator) to get "ui_Info.h" resolved
#include "info.hpp"
#include "ui_Info.h"

Info::Info(QWidget *parent,QMediaPlayer *player) :
        QDialog(parent), ui(new Ui::Info)
{
    ui->setupUi(this);
    const auto metadataList{player->availableMetaData()};
    foreach(auto const &tempMetaDataKey,metadataList)
    {
        ui->lbl->setText(ui->lbl->text().append(tempMetaDataKey + "    :    " + player->metaData(tempMetaDataKey).toString()) + "\n");
    }
}

Info::~Info()
{
    delete ui;
}