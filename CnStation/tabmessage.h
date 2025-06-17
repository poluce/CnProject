#ifndef TABMESSAGE_H
#define TABMESSAGE_H

#include <QWidget>

namespace Ui {
class tabMessage;
}

class tabMessage : public QWidget
{
    Q_OBJECT

public:
    explicit tabMessage(QWidget *parent = nullptr);
    ~tabMessage();

private:
    Ui::tabMessage *ui;
};

#endif // TABMESSAGE_H
