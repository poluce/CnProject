#ifndef USEPAGE_H
#define USEPAGE_H

#include <QWidget>
#include "signalhub.h"

namespace Ui {
class UsePage;
}

class UsePage : public QWidget
{
    Q_OBJECT

public:
    explicit UsePage(QWidget *parent = nullptr);
    ~UsePage();
    void m_initCtrol();

signals:
    void m_firstPage();
    void m_prePage();
    void m_nextPage();
    void m_lastPage();
    void m_toPage(int pages);

private slots:
    void on_btn_first_clicked();

    void on_btn_pre_clicked();

    void on_btn_next_clicked();

    void on_btn_last_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

private:
    Ui::UsePage *ui;
};

#endif // USEPAGE_H
