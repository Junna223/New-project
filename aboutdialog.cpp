#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    // 去除对话框右上角的问号
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
