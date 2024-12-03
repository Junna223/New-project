#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit * textEdit) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    // 去除对话框右上角的问号
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    pTextEdit = textEdit;

    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btFindNext_clicked()
{
    QString target=ui->searchText->text();//获取查找框中的内容
    if(target == "" || pTextEdit == nullptr)
        return;

    QString text=pTextEdit->toPlainText();//文本框内容
    QTextCursor c=pTextEdit->textCursor();//获取当前光标的位置

    int index =-1;

    if(ui->rbDown->isChecked()){
        index = text.indexOf(target,c.position(),
                             ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);//根据cbCaseSensetive的选中状态决定查找是否区分大小写

        if(index >= 0){// 当找到目标字符串
            // 从起始位置到结束位置的文本被选中（保持锚点）
            c.setPosition(index);//将文本光标c的位置设置为找到的目标字符串的起始位置
            c.setPosition(index+target.length(),QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target,c.position()-text.length()-1,ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index+target.length());//移动光标
            c.setPosition(index,QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }

    }
    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("提示");
        msg.setText(QString("找不到")+target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplaceDialog::on_btReplace_clicked()
{
    QString target=ui->searchText->text();
    QString to=ui->targetText->text();

    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QString selText=pTextEdit->textCursor().selectedText();//光标选中的内容
        if( selText == target){
            pTextEdit->insertPlainText(to);
        }

        on_btFindNext_clicked();
    }



}


void ReplaceDialog::on_btReplaceAll_clicked()
{
    QString target=ui->searchText->text();
    QString to=ui->targetText->text();
    if((pTextEdit != nullptr) && (target != "") && (to != "")){
        QString text=pTextEdit->toPlainText();//获取整个文本框中的内容
        text.replace(target,to,ui->cbCaseSensetive->isChecked()? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();
        pTextEdit->insertPlainText(text);
    }

}


void ReplaceDialog::on_btCancel_clicked()
{
    accept();
}

