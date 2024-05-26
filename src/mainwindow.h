#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
//#include "credit.h"


#ifdef __cplusplus

extern "C" {
#endif

#include "polish_notation.h"
#include "stack.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double x;//todo
    bool isX;
    int Lb;


private:
    Ui::MainWindow *ui;
    //Credit *creditWindow;

private slots:
    void digit_numbers();
    void on_pushButton_x_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_drow_clicked();
    void on_credit_clicked();
};

#endif // MAINWINDOW_H
