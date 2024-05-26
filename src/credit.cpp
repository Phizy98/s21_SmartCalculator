#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_pushButton_calc_clicked()
{
    double sum = ui->doubleSpinBox_sum->value();
    double term = ui->doubleSpinBox_term->value();
    double rate = ui->doubleSpinBox_rate->value();
    if(sum == 0) {
        ui->label_monthPayment->setText("0");
        ui->label_overpayment->setText("0");
        ui->label_total->setText("0");
        return;
    }
    if(rate == 0) {
        ui->label_monthPayment->setText(QString::number(sum/term));
        ui->label_overpayment->setText("0");
        ui->label_total->setText(QString::number(sum));
        return;
    }
    double month_payment = 0;
    double max_month_payment = 0;
    double total_payment = 0;
    double overpayment = 0;
    rate = rate / 100.0 / 12.0;
    if(ui->type->currentIndex() == 0) {

        month_payment = sum * (rate + (rate / (pow(1.0 + rate, term) - 1)));
        total_payment = month_payment * term;
        overpayment = total_payment - sum;
        ui->label_monthPayment->setText(QString::number(month_payment));
    } else {
        month_payment = sum / term;
        max_month_payment = month_payment + sum * rate;

        double percentage = 0.0;
        int mounth_count = 0;
        while (mounth_count != term) {
        percentage = month_payment +
                     (sum - month_payment * mounth_count) *
                         rate;
        total_payment += percentage;
        mounth_count++;
        }
        overpayment = total_payment - sum;
        month_payment = percentage;
        ui->label_monthPayment->setText(QString::number(max_month_payment) + "..." + QString::number(month_payment));
    }
    ui->label_overpayment->setText(QString::number(overpayment));
    ui->label_total->setText(QString::number(total_payment));
}


void Credit::on_pushButton_clear_clicked()
{
    ui->label_monthPayment->setText("0");
    ui->label_overpayment->setText("0");
    ui->label_total->setText("0");
    ui->doubleSpinBox_rate->setValue(0);
    ui->doubleSpinBox_sum->setValue(0);
    ui->doubleSpinBox_term->setValue(1);
}

