#ifndef RUNINGMESSAGE_H
#define RUNINGMESSAGE_H

#include <QWidget>

namespace Ui {
class RuningMessage;
}

class RuningMessage : public QWidget
{
    Q_OBJECT

public:
    explicit RuningMessage(QWidget *parent = nullptr);
    ~RuningMessage();

private:
    Ui::RuningMessage *ui;
};

#endif // RUNINGMESSAGE_H
