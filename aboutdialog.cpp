#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->ProgramVerLabel->setText(COMMUTE_VER);
    ui->CalculationsVersionLabel->setText(VERSION_OF_MATTCALCULATIONS);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
