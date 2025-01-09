#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // 初始化 scienceview 并隐藏
    scienceView = new scienceview(this);
    scienceView->hide();

    dateView = new dateview(this);
    dateView->hide();

    capacityconversionView = new CapacityConversionView(this);
    capacityconversionView->hide();

    connect(ui->scienceShow, &QAction::triggered, this, &MainWindow::on_scienceShow_triggered);
    connect(ui->dateShow, &QAction::triggered, this, &MainWindow::on_dateShow_triggered);




    // 初始化数字按钮和操作符按钮的连接
    digitBTNs = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };

    foreach(auto btn, digitBTNs)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    operatorBTNs = {
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Minus, ui->btnMinus},
        {Qt::Key_Asterisk, ui->btnMultipe},
        {Qt::Key_Slash, ui->btnDivide},
        {Qt::Key_Percent, ui->btnPercentage},
    };

    foreach(auto btn, operatorBTNs)
    connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));

    connect(ui->btnMS, SIGNAL(clicked()), this, SLOT(on_btnMS_clicked()));
    connect(ui->btnMR, SIGNAL(clicked()), this, SLOT(on_btnMR_clicked()));
    connect(ui->btnMC, SIGNAL(clicked()), this, SLOT(on_btnMC_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scienceShow_triggered()
{
    scienceView->show();  // 显示 scienceview
    setCentralWidget(scienceView);
}

void MainWindow::on_dateShow_triggered()
{
    dateView->show();
    setCentralWidget(dateView);

}

void MainWindow::on_capacityShow_triggered()
{
    capacityconversionView->show();
    setCentralWidget(capacityconversionView);
}

void MainWindow::on_mainShow_triggered()
{
    // 假设 mainWidget 是 MainWindow 的主界面 widget
    QWidget *mainWidget = ui->centralwidget; // 或者是你设置为主界面的 widget
    mainWidget->show();
}

QString MainWindow::calculation(bool *ok)
{
    ui->statusbar->showMessage("calculation is in progress");
    double result = 0;

    while (operands.size() >= 2 && !opcodes.isEmpty())
    {
        // 取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        // 取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        // 根据操作符进行相应计算
        if (op == "+")
        {
            result = operand1 + operand2;
        }
        else if (op == "-")
        {
            result = operand1 - operand2;
        }
        else if (op == "×")
        {
            result = operand1 * operand2;
        }
        else if (op == "÷")
        {
            if (operand2 == 0)
            {
                ui->statusbar->showMessage("Error: Division by zero");
                return "Error";
            }
            result = operand1 / operand2;
        }

        // 将本次计算结果压入操作数栈
        operands.push_front(QString::number(result));
    }

    // 如果最后只剩一个操作数且操作符栈为空，直接返回该操作数作为最终结果
    if (operands.size() == 1 && opcodes.isEmpty())
    {
        result = operands.front().toDouble();
    }
    else
    {
        ui->statusbar->showMessage("Invalid input: not enough operands or operators");
    }

    return QString::number(result);
}



void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (operand == "0" && digit != "0")
        operand = "";
    operand += digit;

    ui->display->setText(operand);
}

void MainWindow::on_btnPeriod_clicked()
{
    if (!operand.contains("."))
        operand += ".";
    ui->display->setText(operand);
}

void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText("0");
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    if (!operand.isEmpty())
    {
        operands.push_back(operand);
        operand = "";
        opcodes.push_back(opcode);

        // 如果已经有两个操作数，则进行计算
        if (operands.size() == 2)
        {
            QString result = calculation();
            ui->display->setText(result);
            operand = result; // 将结果存储为下一个操作数
            operands.clear(); // 清空操作数栈，以便开始新的计算
            opcodes.clear();  // 清空操作符栈
        }
    }
}

void MainWindow::btnUnaryOperatorClicked()
{
    if (!operand.isEmpty())
    {
        double result = operand.toDouble();
        operand = "";

        QString op = qobject_cast<QPushButton*>(sender())->text();

        if (op == "%")
            result /= 100.0;
        else if (op == "1/x")
            result = 1 / result;
        else if (op == "x^2")
            result *= result;
        else if (op == "√")
            result = sqrt(result);

        ui->display->setText(QString::number(result));
        operand = QString::number(result);
    }
}

void MainWindow::on_btnEqual_clicked()
{
    if (!operand.isEmpty())
    {
        operands.push_back(operand);
    }

    if (operands.size() >= 2)
    {
        QString result = calculation();
        ui->display->setText(result);
        operand = result; // 将结果存储为下一个操作数
        operands.clear(); // 清空操作数栈，以便开始新的计算
        opcodes.clear();  // 清空操作符栈
    }
    else
    {
        ui->statusbar->showMessage("Invalid input: not enough operands or operators");
        ui->display->setText("0");
    }
}

void MainWindow::btnPlusMinusClicked()
{
    if (!operand.isEmpty())
    {
        double value = operand.toDouble();
        value = -value;
        operand = QString::number(value);
        ui->display->setText(operand);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach (auto btnKey, digitBTNs.keys())
    {
        if (event->key() == btnKey)
            digitBTNs[btnKey]->animateClick(100);
    }

    foreach (auto btnKey, operatorBTNs.keys())
    {
        if (event->key() == btnKey)
        {
            operatorBTNs[btnKey]->animateClick(100);
            return;
        }
    }
}

void MainWindow::on_btnMS_clicked()
{
    memoryValue = ui->display->text();
}

void MainWindow::on_btnMR_clicked()
{
    if (!operand.isEmpty() || !operands.isEmpty() || !opcodes.isEmpty())
    {
        int choice = QMessageBox::question(this, "Memory Recall", "Do you want to use the memory value as a new operand and continue the current calculation?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (choice == QMessageBox::Yes)
        {
            operand = memoryValue;
            ui->display->setText(operand);
        }
        else if (choice == QMessageBox::No)
        {
            operand.clear();
            operands.clear();
            opcodes.clear();
            ui->display->setText(memoryValue);
        }
        else
        {
            // 用户取消操作，不做任何处理
        }
    }
    else
    {
        ui->display->setText(memoryValue);
    }
}

void MainWindow::on_btnMC_clicked()
{
    memoryValue = "";
}
