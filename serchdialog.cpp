#include "serchdialog.h"
#include "ui_serchdialog.h"
#include <QMessageBox>

SerchDialog::SerchDialog(QWidget *parent,QPlainTextEdit * textEdit) :
    QDialog(parent),
    ui(new Ui::SerchDialog)
{
    ui->setupUi(this);
    // 去除对话框右上角的问号
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    pTextEdit = textEdit;
}

SerchDialog::~SerchDialog()
{
    delete ui;
}

void SerchDialog::on_btFindNext_clicked()
{
    QString target = ui->serchText->text();
    if(target == "" || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c=pTextEdit->textCursor();
    int index=-1;

    if(ui->rbDown->isChecked()){
        index = text.indexOf(target,c.position(),
                             ui->cbCaseSensetive->isChecked() ?Qt::CaseInsensitive:Qt::CaseInsensitive);
        if(index >=0){
            c.setPosition(index);
            c.setPosition(index + target.length(),QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target,c.position() - text.length() -1,
                                 ui->cbCaseSensetive->isChecked() ?Qt::CaseInsensitive:Qt::CaseInsensitive);
        if(index >=0){
            c.setPosition(index + target.length());
            c.setPosition(index,QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("jishiben");
        msg.setText(QString("找不到")+target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();


    }
}


void SerchDialog::on_btCancel_clicked()
{
    accept();
}

