#include "chargmessage.h"
#include "ui_chargmessage.h"

#include <QPainter>

ChargMessage::ChargMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChargMessage)
{
    ui->setupUi(this);


//    QPalette pal = palette();
//    pal.setColor(QPalette::Window, QColor("#3b7d89"));
//    setAutoFillBackground(true);  // 必须启用自动填充背景
//    setPalette(pal);


//    setAutoFillBackground(true);
//    setStyleSheet("background-color: #3b7d89; border: 1px solid transparent;");


}

ChargMessage::~ChargMessage()
{
    delete ui;
}

void ChargMessage::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 画背景（相当于 QFrame）
    p.setBrush(QColor("#3b7d89"));
    p.setPen(Qt::NoPen);
    p.drawRect(this->rect());
}
