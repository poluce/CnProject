#include "tabmessage.h"
#include "ui_tabmessage.h"

tabMessage::tabMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabMessage)
{
    ui->setupUi(this);
}

tabMessage::~tabMessage()
{
    delete ui;
}
