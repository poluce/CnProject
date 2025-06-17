#include "myusepage.h"
#include "ui_myusepage.h"

#include <QDebug>
#include <QIntValidator>

UsePage::UsePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsePage)
{
    ui->setupUi(this);
    m_initCtrol();
}

UsePage::~UsePage()
{
    delete ui;
}

void UsePage::m_initCtrol()
{
    ui->btn_pre->setText("◀");
    QFont font = ui->btn_pre->font();
    font.setPointSize(15);
    ui->btn_pre->setFont(font);
    ui->btn_next->setText("▶");
    ui->btn_next->setFont(font);

    //允许用户输入任意长度的正整数
    QIntValidator *validator = new QIntValidator(0, INT_MAX, this);
    ui->lineEdit->setValidator(validator);

}

void UsePage::on_btn_first_clicked()
{
    SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_first);
}

void UsePage::on_btn_pre_clicked()
{
    SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_pre);
}

void UsePage::on_btn_next_clicked()
{
    SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_next);
}

void UsePage::on_btn_last_clicked()
{
    SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_last);
}

void UsePage::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text().isEmpty() )
        return;
     SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_topage,
                                   ui->lineEdit->text().toInt());

//     qDebug()<<"输入的字符：："<<ui->lineEdit->text().toInt();
}

void UsePage::on_lineEdit_returnPressed()
{
    if(ui->lineEdit->text().isEmpty() )
        return;
     SignalHub::instance().postMsg(MySignal::WidgetType::Navigation_topage,
                                   ui->lineEdit->text().toInt());
}
