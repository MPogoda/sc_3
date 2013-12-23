#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model{ new QStandardItemModel(0, 3) }
{
    ui->setupUi(this);

    model->setHorizontalHeaderItem(0, new QStandardItem{ QString{ "Name" } } );
    model->setHorizontalHeaderItem(1, new QStandardItem{ QString{ "Weight" } });
    model->setHorizontalHeaderItem(2, new QStandardItem{ QString{ "Value" } });

    ui->tableValues->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
