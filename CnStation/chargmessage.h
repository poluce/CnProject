#ifndef CHARGMESSAGE_H
#define CHARGMESSAGE_H

#include <QWidget>

namespace Ui {
class ChargMessage;
}

class ChargMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ChargMessage(QWidget *parent = nullptr);
    ~ChargMessage();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ChargMessage *ui;
};

#endif // CHARGMESSAGE_H
