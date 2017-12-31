#ifndef COMMUTE_H
#define COMMUTE_H

#define COMMUTE_VER "1.0.0_Beta_Build_2"

#include <QMainWindow>
#include <QDir>
#include "changedefaultsdialog.h"
#include "aboutdialog.h"
#include "../General_Library/mattcalculations.h"


namespace Ui {
class Commute;
}

class Commute : public QMainWindow
{
    Q_OBJECT

public:
    explicit Commute(QWidget *parent = 0);
    ~Commute();
    void refreshFields();
    void SaveDefaultsToFile();

    // Public Enter Functions -----------------------------------------------------

    void enter87Price(double d87Price);
    void enter89Price(double d89Price);
    void enter91Price(double d91Price);
    void enterDieselPrice(double dDieselPrice);


    double get87Price();
    double get89Price();
    double get91Price();
    double getDieselPrice();



private slots:
    void on_actionChange_Default_Values_triggered();

    void on_distanceDoubleSpinBox_editingFinished();

    void on_morningHoursSpinBox_editingFinished();

    void on_morningMinSpinBox_editingFinished();

    void on_ReturnHoursSpinBox_editingFinished();

    void on_ReturnMinSpinBox_editingFinished();

    void on_gasMilageDoubleSpinBox_editingFinished();

    void on_Grade87RadioButton_clicked();

    void on_Grade89RadioButton_clicked();

    void on_Grade91RadioButton_clicked();

    void on_GradeDieselRadioButton_clicked();

    void on_OtherCostLineEdit_editingFinished();

    void on_actionAbout_triggered();

    void on_numberOfCommuteDaysPerWeekSpinBox_valueChanged();

    void on_morningHoursSpinBox_valueChanged();

    void on_morningMinSpinBox_valueChanged();

    void on_ReturnHoursSpinBox_valueChanged();

    void on_ReturnMinSpinBox_valueChanged();

private:
    Ui::Commute *ui;

    const QString strFileName = "ModeRNCommuteInfo/DefaultValues.val";

    double m_dNumberOfWorkDaysPerMonth = 21.66667 ; // (5 workdays * 52 weeks per Year ) / 12 months
    const int cnstNumberOfMonthsInAYear = 12;
    const int cnstNumberOfWeeksInAYear = 52;
    const int cnstNumberOfMillisecondsPerHour = 3600000;
    const int cnstNumberOfMillisecondsPerMinute = 60000;

    const int m_nDefaultNumOfWorkDaysPerWeek = 5;

    unsigned int m_nMonthlyTotalCommuteTimeInMS = 0;
    double m_dMonthlyCostOfGas = 0;
    double m_d87Price = 0;
    double m_d89Price = 0;
    double m_d91Price = 0;
    double m_dDieselPrice = 0;

    bool m_bLinkCommuteTimes = true;

    void loadDefaultsFromFile();
    void refreshRadioButtonText();

    void calculateCommuteDaysPerMonth();
    void calculateMonthlyCostOfGas();
    void calcTimeSpentCommuting();
    void calcDepreciation();

    void addOtherCommuteCosts();

};

#endif // COMMUTE_H
