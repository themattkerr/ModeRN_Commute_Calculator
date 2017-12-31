#ifndef CHANGEDEFAULTSDIALOG_H
#define CHANGEDEFAULTSDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include "commute.h"
#include "../General_Library/mattcalculations.h"

namespace Ui {
class ChangeDefaultsDialog;
}

class ChangeDefaultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDefaultsDialog(QWidget *parent = 0);
    ~ChangeDefaultsDialog();

private slots:
    void on_pushButtonAccept_clicked();
    void on_pushButtonClear_clicked();

    void on_Grade87PricelineEdit_editingFinished();

    void on_Grade89PricelineEdit_editingFinished();

    void on_Grade91PricelineEdit_editingFinished();

    void on_GradeDiesellineEdit_editingFinished();

    void on_AvgDepriciationLineEdit_editingFinished();



private:
    Ui::ChangeDefaultsDialog *ui;
    void keyPressEvent(QKeyEvent *evt);
    void refreshFields();
    void loadCurrentGasPrices();
};

#endif // CHANGEDEFAULTSDIALOG_H
