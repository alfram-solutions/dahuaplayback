#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include<string>

#include "DahuaStatus.hpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DWORD my_sdk_status = 0;
    DWORD* p_my_sdk_status = &my_sdk_status;
    init_test(p_my_sdk_status);
    run_test();
    end_test();
    ui->infoLabel->setText(QString::number(my_sdk_status));



}

MainWindow::~MainWindow()
{

    delete ui;
}



