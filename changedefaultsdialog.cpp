#include "changedefaultsdialog.h"
#include "ui_changedefaultsdialog.h"

ChangeDefaultsDialog::ChangeDefaultsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDefaultsDialog)
{
    ui->setupUi(this);
    ui->AvgDepriciationLineEdit->hide();
    ui->label_6->hide();
    loadCurrentGasPrices();
    refreshFields();
}

ChangeDefaultsDialog::~ChangeDefaultsDialog()
{
    delete ui;
}

void ChangeDefaultsDialog::keyPressEvent(QKeyEvent *evt)
{
    if((evt->key() == Qt::Key_Enter) || (evt->key() == Qt::Key_Return))
        return;
    QDialog::keyPressEvent(evt);
}

 void ChangeDefaultsDialog::refreshFields()
 {

     ui->Grade87PricelineEdit->setText(doubleToCurrency(usDollarsStringToDouble(ui->Grade87PricelineEdit->text()),3, US_DOLLARS));
     ui->Grade89PricelineEdit->setText(doubleToCurrency(usDollarsStringToDouble(ui->Grade89PricelineEdit->text()),3, US_DOLLARS));
     ui->Grade91PricelineEdit->setText(doubleToCurrency(usDollarsStringToDouble(ui->Grade91PricelineEdit->text()),3, US_DOLLARS));
     ui->GradeDiesellineEdit->setText(doubleToCurrency(usDollarsStringToDouble(ui->GradeDiesellineEdit->text()),3, US_DOLLARS));


 }

  void ChangeDefaultsDialog::loadCurrentGasPrices()
 {
      ui->Grade87PricelineEdit->setText(doubleToCurrency(((Commute*)parentWidget())->get87Price() ,3, US_DOLLARS));
      ui->Grade89PricelineEdit->setText(doubleToCurrency(((Commute*)parentWidget())->get89Price() ,3, US_DOLLARS));
      ui->Grade91PricelineEdit->setText(doubleToCurrency(((Commute*)parentWidget())->get91Price() ,3, US_DOLLARS));
      ui->GradeDiesellineEdit->setText(doubleToCurrency(((Commute*)parentWidget())->getDieselPrice() ,3, US_DOLLARS));
 }

void ChangeDefaultsDialog::on_pushButtonAccept_clicked()
{

    ((Commute*)parentWidget())->enter87Price(usDollarsStringToDouble(ui->Grade87PricelineEdit->text()));
    ((Commute*)parentWidget())->enter89Price(usDollarsStringToDouble(ui->Grade89PricelineEdit->text()));
    ((Commute*)parentWidget())->enter91Price(usDollarsStringToDouble(ui->Grade91PricelineEdit->text()));
    ((Commute*)parentWidget())->enterDieselPrice(usDollarsStringToDouble(ui->GradeDiesellineEdit->text()));

    ((Commute*)parentWidget())->SaveDefaultsToFile();
    this->close();
}

void ChangeDefaultsDialog::on_pushButtonClear_clicked()
{
    ui->Grade87PricelineEdit->setText(doubleToCurrency(0,3, US_DOLLARS));
    ui->Grade89PricelineEdit->setText(doubleToCurrency(0,3, US_DOLLARS));
    ui->Grade91PricelineEdit->setText(doubleToCurrency(0,3, US_DOLLARS));
    ui->GradeDiesellineEdit->setText(doubleToCurrency(0,3, US_DOLLARS));
}

void ChangeDefaultsDialog::on_Grade87PricelineEdit_editingFinished()
{
    refreshFields();
}

void ChangeDefaultsDialog::on_Grade89PricelineEdit_editingFinished()
{
    refreshFields();
}

void ChangeDefaultsDialog::on_Grade91PricelineEdit_editingFinished()
{
    refreshFields();
}

void ChangeDefaultsDialog::on_GradeDiesellineEdit_editingFinished()
{
    refreshFields();
}

void ChangeDefaultsDialog::on_AvgDepriciationLineEdit_editingFinished()
{
    refreshFields();
}


