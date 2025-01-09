#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QLabel>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>
#include "scienceview.h"
#include "dateview.h"
#include "capacityconversionview.h"
#include <QStackedWidget>

#include <QMenuBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QString operand;
    QString opcode;
    QStack <QString> operands;
    QStack <QString> opcodes;//操作符
    QMap<int,QPushButton*> digitBTNs;
    QMap<char,QPushButton*> operatorBTNs;

    QString calculation(bool *ok=NULL);

    QString memoryValue;


private slots:
    void on_scienceShow_triggered();
    void on_dateShow_triggered();
    void on_capacityShow_triggered();
    void on_mainShow_triggered();

    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClear_clicked();

    void on_btnEqual_clicked();

    void btnPlusMinusClicked();

    virtual void keyPressEvent(QKeyEvent *event);
    //void on_pushButton_18_clicked();

    //void on_btnPlusMinus_clicked();

    void on_btnMS_clicked();

    void on_btnMR_clicked();

    void on_btnMC_clicked();

private:
    Ui::MainWindow *ui;
    scienceview *scienceView;
    dateview *dateView;
    CapacityConversionView *capacityconversionView;
    QStackedWidget *stackedWidget;


};
#endif // MAINWINDOW_H
