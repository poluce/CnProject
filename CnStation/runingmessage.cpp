#include "runingmessage.h"
#include "ui_runingmessage.h"

RuningMessage::RuningMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RuningMessage)
{
    ui->setupUi(this);
}

RuningMessage::~RuningMessage()
{
    delete ui;
}
