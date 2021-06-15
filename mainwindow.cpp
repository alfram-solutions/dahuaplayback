#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include<string>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ds.init_test();
    ui->infoLabel->setText(QString::number(ds.sdk_status));
    ds.run_test();
    ds.end_test();



}

MainWindow::~MainWindow()
{

    delete ui;
}



