#ifndef CAPACITYCONVERSIONVIEW_H
#define CAPACITYCONVERSIONVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class CapacityConversionView; }
QT_END_NAMESPACE

class CapacityConversionView : public QWidget
{
    Q_OBJECT

public:
    explicit CapacityConversionView(QWidget *parent = nullptr);
    ~CapacityConversionView();

private slots:
    void updateConversion();  // 用于更新换算结果的槽函数

private:
    Ui::CapacityConversionView *ui;
//    QLineEdit *line1Edit;
//    QLineEdit *line2Edit;
//    QComboBox *comboBox1;
//    QComboBox *comboBox2;
};

#endif // CAPACITYCONVERSIONVIEW_H
