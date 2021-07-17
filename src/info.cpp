#include "info.hpp"
#include "../include/ui_Info.h"

Info::Info(QWidget *parent,QMediaPlayer *player) :
        QDialog(parent), ui(new Ui::Info)
{
    ui->setupUi(this);
    const auto metadataList{player->availableMetaData()};
    for(auto const &tempMetaDataKey: metadataList)
    {
        ui->lbl->setText(
            ui->lbl->text()
                .append(tempMetaDataKey + "    :    " + player->metaData(tempMetaDataKey).toString()) + "\n"
        );
    }
}

Info::~Info()
{
    delete ui;
}