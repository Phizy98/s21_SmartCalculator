#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polish_notation.h"
#include "stack.h"
#include <QInputDialog>
#include "credit.h""

//extern "C" {        //todo
//    #include "polish_notation.h"
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);


    this->x = 0;
    this->isX = false;
    this->Lb = 0;


    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons

    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_mul,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons

    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons

    connect(ui->pushButton_lb,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_rb,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(digit_numbers()));//for all buttons
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::digit_numbers() {
    QPushButton *button = static_cast<QPushButton*>(sender()); // Получение указателя на кнопку, которая вызвала событие. sender() возвращает указатель на объект, который отправил сигнал.
    QString addString = button->text();
    if(addString == '(') this->Lb++;
    if(addString == ')') this->Lb--;
    QString new_string = (ui->resultShow->text() + addString);
    ui->resultShow->setText(new_string);
}




void MainWindow::on_pushButton_x_clicked() {
    this->isX = true;
}


void MainWindow::on_pushButton_equal_clicked() {
    long double xUser = 0;
    if(this->Lb != 0) {
        QMessageBox::about(this, "Warning", "Невозможно произвести вычисления\nЗакройте все скобки");
        return;
    }
    if(this->isX) {
        QString text = QInputDialog::getText(this, "", "Введите значение переменной Х");
        this->x = text.toDouble();
        xUser = this->x;
        //qInfo() << "x -- input" << x;
    }
//    long double xUser = this->x;
    long double result = 0;

//    std::string str = ui->resultShow->text().toStdString();
//    char tmp[256] = "";

//    char *cstr = new char[str.length() + 1];
//    strcpy(tmp, str.c_str());
//    delete [] cstr;


    char tmp[256] = "";
    strcpy(tmp, ui->resultShow->text().toStdString().c_str());
    int res;
    if(this->isX) res = calculate(&result, tmp, &xUser);
    else res = calculate(&result, tmp, NULL);

    //ui->resultShow->setText( );
    if(!res) ui->resultShow->setText(QString::number(result, 'g', 7));
    else ui->resultShow->setText("The string is not valid");
    this->isX = false;
}


void MainWindow::on_pushButton_clear_clicked() {
    ui->resultShow->clear();
    this->isX = false;
    this->Lb = 0;
}


void MainWindow::on_pushButton_drow_clicked() {
    if(!this->isX) {
        QMessageBox::about(this, "Warning", "Невозможно построить график\nВ выражении остутствует переменная");
        return;
    }
    if(this->Lb != 0) {
        QMessageBox::about(this, "Warning", "Невозможно произвести вычисления\nЗакройте все скобки");
        return;
    }

    double x_min = ui->doubleSpinBox_xMin->value();
    double x_max = ui->doubleSpinBox_xMax->value();
    long double res = 0;
    double y_min = 0;
    double y_max = 0;


    double h = ui->doubleSpinBox_step->value();
    if(x_max <= x_min) {
        QMessageBox::about(this, "Warning", "Невозможно построить график\nНеверно заданы границы области определения");
        return;
    }
    QVector<double> x, y;

    char tmp[256] = "";
    strcpy(tmp, ui->resultShow->text().toStdString().c_str());



    long double tmpX = 0;
    for (double X = x_min; X <= x_max; X += h) {
      x.push_back(X);
      tmpX = X;
      calculate(&res, tmp, &tmpX);
      y.push_back((double)res);
    }
    ui->widget->clearGraphs();



    ui->widget->addGraph();

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    ui->widget->graph(0)->setPen(pen);


    // говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);


    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(x_min, x_max);
    y_min = y.value(0);
    y_max = y_min;

    for(double value : y) {
        if(value > y_max) y_max = value;
        if(value < y_min) y_min = value;
    }

    ui->widget->yAxis->setRange(y_min, y_max);//Для оси Oy

    // задаем возможность зумировать график
    ui->widget->setInteraction(QCP::iRangeZoom, true);

    // задаем цвет точки и толщину линии
//    ui->widget->graph(0)->setPen(QColor(61, 82, 62, 255));
//    QPen graphPen = ui->graph_frame->graph(0)->pen();
//    graphPen.setWidth(2);
//    ui->widget->graph(0)->setPen(graphPen);

    // перерисуем график на нашем graph_frame

    ui->widget->replot();
    x.clear();
    y.clear();
}


void MainWindow::on_credit_clicked() {
    Credit credit;
    credit.setModal(true);
    credit.exec();


}

