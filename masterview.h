#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "welcomeview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView();
    void goPatientView();
    void goPreviousView();

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogOut_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    bool isFromLogout = false;

    Ui::MasterView *ui;

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientEditView *patientEditView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientView *patientView;
};
#endif // MASTERVIEW_H
