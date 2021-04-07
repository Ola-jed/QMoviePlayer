// You may need to build the project (run Qt uic code generator) to get "ui_Info.h" resolved

#include "info.hpp"
#include "ui_Info.h"

Info::Info(QWidget *parent,QMediaPlayer *player) :
        QDialog(parent), ui(new Ui::Info)
{
    ui->setupUi(this);
    const QStringList metadataList = player->availableMetaData();
    const int listSize = metadataList.size();
    QString metadataKey;
    QVariant varData;
    for (int i = 0; i < listSize; i++)
    {
        metadataKey = metadataList.at(i);
        varData = player->metaData(metadataKey);
        ui->lbl->setText(ui->lbl->text().append(metadataKey + "    :    " + varData.toString()) + "\n");
    }
}

Info::~Info()
{
    delete ui;
}