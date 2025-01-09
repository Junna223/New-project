#include "capacityconversionview.h"
#include "ui_capacityconversionview.h"
#include <QDoubleValidator>

CapacityConversionView::CapacityConversionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CapacityConversionView)
{
    ui->setupUi(this);

    // 设置QLineEdit的验证器，确保输入的是数字
    QDoubleValidator *validator = new QDoubleValidator(this);
    ui->line1Edit->setValidator(validator);
    ui->line2Edit->setValidator(validator);

    // 连接textChanged信号到槽函数，以便在输入变化时更新换算结果
    connect(ui->line1Edit, &QLineEdit::textChanged, this, &CapacityConversionView::updateConversion);
    connect(ui->comboBox1, &QComboBox::currentTextChanged, this, &CapacityConversionView::updateConversion);
    connect(ui->comboBox2, &QComboBox::currentTextChanged, this, &CapacityConversionView::updateConversion);
}

CapacityConversionView::~CapacityConversionView()
{
    delete ui;
}

void CapacityConversionView::updateConversion()
{
    bool ok;
    double value1 = ui->line1Edit->text().toDouble(&ok);
    if (!ok) {
        ui->line2Edit->clear();  // 清除结果，如果输入不是数字
        return;
    }

    int fromUnitIndex = ui->comboBox1->currentIndex();
    int toUnitIndex = ui->comboBox2->currentIndex();
    double result = value1;  // 默认结果为输入值

    // 根据选择的单位进行换算
    switch (fromUnitIndex) {
        case 0:  // 升
            switch (toUnitIndex) {
                case 1:  // 毫升
                    result *= 1000;
                    break;
                case 2:  // 加仑
                    result *= 3.78541;
                    break;
                case 3:  // 立方米
                    result /= 1000;
                    break;
                case 4:  // 立方厘米
                    result *= 1000000;
                    break;
            }
            break;
        case 1:  // 毫升
            switch (toUnitIndex) {
                case 0:  // 升
                    result /= 1000;
                    break;
                case 2:  // 加仑
                    result /= 3785.41;
                    break;
                case 3:  // 立方米
                    result /= 1000000;
                    break;
                case 4:  // 立方厘米
                    result *= 1;
                    break;
            }
            break;
        case 2:  // 加仑
            switch (toUnitIndex) {
                case 0:  // 升
                    result /= 3.78541;
                    break;
                case 1:  // 毫升
                    result *= 3785.41;
                    break;
                case 3:  // 立方米
                    result /= 3.78541 * 1000;
                    break;
                case 4:  // 立方厘米
                    result *= 3785.41 * 1000;
                    break;
            }
            break;
        case 3:  // 立方米
            switch (toUnitIndex) {
                case 0:  // 升
                    result *= 1000;
                    break;
                case 1:  // 毫升
                    result *= 1000000;
                    break;
                case 2:  // 加仑
                    result *= 1000 * 3.78541;
                    break;
                case 4:  // 立方厘米
                    result *= 1000000000;
                    break;
            }
            break;
        case 4:  // 立方厘米
            switch (toUnitIndex) {
                case 0:  // 升
                    result /= 1000000;
                    break;
                case 1:  // 毫升
                    result /= 1000;
                    break;
                case 2:  // 加仑
                    result /= (3785.41 * 1000);
                    break;
                case 3:  // 立方米
                    result /= 1000000000;
                    break;
            }
            break;
    }

    ui->line2Edit->setText(QString::number(result, 'f', 2));  // 设置结果，保留两位小数
}
