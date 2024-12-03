#ifndef SERCHDIALOG_H
#define SERCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class SerchDialog;
}

class SerchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerchDialog(QWidget *parent = nullptr,QPlainTextEdit * textEdit=nullptr);
    ~SerchDialog();

private slots:
    void on_btFindNext_clicked();

    void on_btCancel_clicked();

private:
    Ui::SerchDialog *ui;

    QPlainTextEdit *pTextEdit;
};

#endif // SERCHDIALOG_H
