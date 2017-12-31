#include "commute.h"
#include "ui_commute.h"

Commute::Commute(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Commute)
{
    ui->setupUi(this);
    ui->numberOfCommuteDaysPerWeekSpinBox->setValue(m_nDefaultNumOfWorkDaysPerWeek);
    ui->label_7->hide(); // Depreciation label
    ui->ResultDeprciationlabel->hide();
    loadDefaultsFromFile();
    refreshFields();
}

Commute::~Commute()
{

    delete ui;
}
void Commute::refreshFields()
{
    calculateCommuteDaysPerMonth();
    refreshRadioButtonText();
    calculateMonthlyCostOfGas();
    calcTimeSpentCommuting();
    //calcDepreciation();
    addOtherCommuteCosts();
}

void Commute::loadDefaultsFromFile()
{
    QFile file(strFileName);
    if(file.exists())
    {
    file.open(QIODevice::ReadWrite);
    QDataStream in(&file);

    in >>
           m_d87Price >>
           m_d89Price >>
           m_d91Price >>
           m_dDieselPrice;
    file.close();
    }
}
void Commute::SaveDefaultsToFile()
{
    QDir mDir;
    if (!mDir.exists("ModeRNCommuteInfo"))
    {
        mDir.mkdir("ModeRNCommuteInfo");
    }


    QFile file(strFileName);
    file.open(QIODevice::ReadWrite);
    QDataStream out(&file);

    out <<
           m_d87Price <<
           m_d89Price <<
           m_d91Price <<
           m_dDieselPrice;
    file.close();
}

void Commute::refreshRadioButtonText()
{
    QString strTemp;
    strTemp.append("87 - ");
    strTemp.append(doubleToCurrency( m_d87Price,3,US_DOLLARS ));
    ui->Grade87RadioButton->setText(strTemp);

    strTemp.clear();
    strTemp.append("89 - ");
    strTemp.append(doubleToCurrency( m_d89Price,3,US_DOLLARS ));
    ui->Grade89RadioButton->setText(strTemp);

    strTemp.clear();
    strTemp.append("91 - ");
    strTemp.append(doubleToCurrency( m_d91Price,3,US_DOLLARS ));
    ui->Grade91RadioButton->setText(strTemp);

    strTemp.clear();
    strTemp.append("Diesel - ");
    strTemp.append(doubleToCurrency( m_dDieselPrice,3,US_DOLLARS ));
    ui->GradeDieselRadioButton->setText(strTemp);

}

void Commute::on_actionChange_Default_Values_triggered()
{
    ChangeDefaultsDialog *x = new ChangeDefaultsDialog(this);
    x->exec();
    delete x;
}

void Commute::on_actionAbout_triggered()
{
    AboutDialog *x = new AboutDialog(this);
    x->exec();
}

// Public Enter Functions -----------------------------------------------------

void Commute::enter87Price(double d87Price)
{
    if(m_d87Price != d87Price && d87Price >= 0 )
    {
        m_d87Price = d87Price;
        refreshFields();
    }

}
void Commute::enter89Price(double d89Price)
{
    if(m_d89Price != d89Price && d89Price >= 0 )
    {
        m_d89Price = d89Price;
        refreshFields();
    }
}
void Commute::enter91Price(double d91Price)
{
    if(m_d91Price != d91Price && d91Price >= 0 )
    {
        m_d91Price = d91Price;
        refreshFields();
    }
}
void Commute::enterDieselPrice(double dDieselPrice)
{
    if(m_dDieselPrice != dDieselPrice && dDieselPrice >= 0 )
    {
        m_dDieselPrice = dDieselPrice;
        refreshFields();
    }
}
// public get functions ------------------------------------

double Commute::get87Price()
{
    return m_d87Price;
}

double Commute::get89Price()
{
    return m_d89Price;
}

double Commute::get91Price()
{
    return m_d91Price;
}

double Commute::getDieselPrice()
{
    return m_dDieselPrice;
}


// Private CalcFuncitions ----------------------------------
void Commute::calculateCommuteDaysPerMonth()
{
    m_dNumberOfWorkDaysPerMonth = ((static_cast<double>(ui->numberOfCommuteDaysPerWeekSpinBox->value()) * static_cast<double>(cnstNumberOfWeeksInAYear)) / static_cast<double>(cnstNumberOfMonthsInAYear));
}

void Commute::calculateMonthlyCostOfGas()
{
    double dGallonsUsed = 0;
    int nNumberOfCommutesPerDay = 2;
    if(ui->gasMilageDoubleSpinBox->value()> 0)
        dGallonsUsed = nNumberOfCommutesPerDay * ((ui->distanceDoubleSpinBox->value())/(ui->gasMilageDoubleSpinBox->value()));
    else
        dGallonsUsed = 0;
    if(ui->Grade87RadioButton->isChecked())
    {
        m_dMonthlyCostOfGas = m_d87Price * dGallonsUsed * m_dNumberOfWorkDaysPerMonth;
    }
    if(ui->Grade89RadioButton->isChecked())
    {
        m_dMonthlyCostOfGas = m_d89Price * dGallonsUsed * m_dNumberOfWorkDaysPerMonth;
    }
    if(ui->Grade91RadioButton->isChecked())
    {
        m_dMonthlyCostOfGas = m_d91Price * dGallonsUsed * m_dNumberOfWorkDaysPerMonth;
    }
    if(ui->GradeDieselRadioButton->isChecked())
    {
        m_dMonthlyCostOfGas = m_dDieselPrice * dGallonsUsed * m_dNumberOfWorkDaysPerMonth;
    }
    if(!(m_dMonthlyCostOfGas > 0))
        m_dMonthlyCostOfGas = 0;
    ui->ResultMonthlyFuelLabel->setText(doubleToCurrency(m_dMonthlyCostOfGas,0,US_DOLLARS));
}
void Commute::calcTimeSpentCommuting()
{
    m_nMonthlyTotalCommuteTimeInMS = m_dNumberOfWorkDaysPerMonth * (
               (ui->morningHoursSpinBox->value() * cnstNumberOfMillisecondsPerHour) +
               (ui->morningMinSpinBox->value() * cnstNumberOfMillisecondsPerMinute) +
               (ui->ReturnHoursSpinBox->value() * cnstNumberOfMillisecondsPerHour) +
               (ui->ReturnMinSpinBox->value() * cnstNumberOfMillisecondsPerMinute)
                );
    ui->ResultTotalTimelabel->setText(millisecondsToHoursMinsSec(m_nMonthlyTotalCommuteTimeInMS ));
}
void Commute::calcDepreciation()
{

}
void Commute::addOtherCommuteCosts()
{
    double dTemp = usDollarsStringToDouble(ui->OtherCostLineEdit->text());
    ui->OtherCostLineEdit->setText(doubleToCurrency( dTemp,2,US_DOLLARS));
    dTemp = (dTemp * m_dNumberOfWorkDaysPerMonth) + m_dMonthlyCostOfGas;
    ui->ResultTotalCostLabel->setText(doubleToCurrency( dTemp,2,US_DOLLARS));
}


// Slots ----------------------------------------------------


void Commute::on_distanceDoubleSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_morningHoursSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_morningMinSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_ReturnHoursSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_ReturnMinSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_gasMilageDoubleSpinBox_editingFinished()
{
    refreshFields();
}

void Commute::on_Grade87RadioButton_clicked()
{
    refreshFields();
}

void Commute::on_Grade89RadioButton_clicked()
{
    refreshFields();
}

void Commute::on_Grade91RadioButton_clicked()
{
    refreshFields();
}

void Commute::on_GradeDieselRadioButton_clicked()
{
    refreshFields();
}

void Commute::on_OtherCostLineEdit_editingFinished()
{
    refreshFields();
}


void Commute::on_numberOfCommuteDaysPerWeekSpinBox_valueChanged()
{
    refreshFields();
}

void Commute::on_morningHoursSpinBox_valueChanged()
{
    if(ui->ReturnMinSpinBox->value() == ui->morningMinSpinBox->value() &&
       ui->ReturnHoursSpinBox->value() == ui->morningHoursSpinBox->value())
        m_bLinkCommuteTimes = true;
    if(m_bLinkCommuteTimes)
        ui->ReturnHoursSpinBox->setValue(ui->morningHoursSpinBox->value());
    refreshFields();
}

void Commute::on_morningMinSpinBox_valueChanged()
{
    if(ui->ReturnMinSpinBox->value() == ui->morningMinSpinBox->value() &&
       ui->ReturnHoursSpinBox->value() == ui->morningHoursSpinBox->value() )
        m_bLinkCommuteTimes = true;
    if(m_bLinkCommuteTimes)
        ui->ReturnMinSpinBox->setValue(ui->morningMinSpinBox->value());
    refreshFields();
}

void Commute::on_ReturnHoursSpinBox_valueChanged()
{
    if(ui->ReturnHoursSpinBox->value() != ui->morningHoursSpinBox->value())
        m_bLinkCommuteTimes = false;
    refreshFields();
}

void Commute::on_ReturnMinSpinBox_valueChanged()
{
    if(ui->ReturnMinSpinBox->value() != ui->morningMinSpinBox->value())
        m_bLinkCommuteTimes = false;
    refreshFields();
}
