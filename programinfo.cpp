#include "programinfo.h"
#include "ui_programinfo.h"

programInfo::programInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::programInfo)
{
    ui->setupUi(this);
}

void programInfo::setTitle(QString Title)
{
    ui->programTitle->setText(Title);

}

void programInfo::setSubtitle(QString subtitle)
{
    ui->programSubtitle->setText(subtitle);

}

void programInfo::setDescription(QString description)
{
    ui->textEdit->setText(description);

}

void programInfo::setIcon(QPixmap Icon)
{
    ui->channelIcon->setPixmap(Icon);
}

programInfo::~programInfo()
{
    delete ui;
}
