#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/knapsack_solver.h"

#include <QIntValidator>
#include <memory>

namespace sc3
{
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model{ new QStandardItemModel(0, 3) }
{
    ui->setupUi(this);

    ui->leMaxWeight->setValidator( new QIntValidator(0, 2000) );

    model->setHorizontalHeaderItem(0, new QStandardItem{ QString{ "Name" } } );
    model->setHorizontalHeaderItem(1, new QStandardItem{ QString{ "Weight" } });
    model->setHorizontalHeaderItem(2, new QStandardItem{ QString{ "Value" } });
    ui->tableValues->setModel(model);

    mItems = { { "map", 9, 150 }
                                       , { "compass", 13, 35 }
                                       , { "water", 153, 200 }
                                       , { "sandwich", 50, 160 }
                                       , { "glucose", 15, 60 }
                                       , { "tin", 68, 45 }
                                       , { "banana", 27, 60 }
                                       , { "apple", 39, 40 }
                                       , { "cheese", 23, 30 }
                                       , { "beer", 52, 10 }
                                       , { "suntan cream", 11, 70 }
                                       , { "camera", 32, 30 }
                                       , { "t-shirt", 24, 15 }
                                       , { "trousers", 48, 10 }
                                       , { "umbrella", 73, 40 }
                                       , { "waterproof trousers", 42, 70 }
                                       , { "waterproof overclothes", 43, 75 }
                                       , { "note-case", 22, 80 }
                                       , { "sunglasses", 7, 20 }
                                       , { "towel",  18, 12 }
                                       , { "socks", 4, 50 }
                                       , { "book", 30, 10 }
                                       , { "notebook", 90, 1 }
                                       , { "tent", 200, 150 }
                               };
    displayPreset( mItems );
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_cbValuePreset_currentIndexChanged(int index)
{
//TODO: adjust values
    switch (index) {
    case 0: //trip
        mItems = { { "map", 9, 150 }
                                               , { "compass", 13, 35 }
                                               , { "water", 153, 200 }
                                               , { "sandwich", 50, 160 }
                                               , { "glucose", 15, 60 }
                                               , { "tin", 68, 45 }
                                               , { "banana", 27, 60 }
                                               , { "apple", 39, 40 }
                                               , { "cheese", 23, 30 }
                                               , { "beer", 52, 10 }
                                               , { "suntan cream", 11, 70 }
                                               , { "camera", 32, 30 }
                                               , { "t-shirt", 24, 15 }
                                               , { "trousers", 48, 10 }
                                               , { "umbrella", 73, 40 }
                                               , { "waterproof trousers", 42, 70 }
                                               , { "waterproof overclothes", 43, 75 }
                                               , { "note-case", 22, 80 }
                                               , { "sunglasses", 7, 20 }
                                               , { "towel",  18, 12 }
                                               , { "socks", 4, 50 }
                                               , { "book", 30, 10 }
                                               , { "notebook", 90, 1 }
                                               , { "tent", 200, 150 }
                                       };
        break;
    case 1: //alpinism
        mItems = { { "map", 9, 150 }
                                               , { "compass", 13, 35 }
                                               , { "water", 153, 200 }
                                               , { "sandwich", 50, 160 }
                                               , { "glucose", 15, 60 }
                                               , { "tin", 68, 45 }
                                               , { "banana", 27, 60 }
                                               , { "apple", 39, 40 }
                                               , { "cheese", 23, 30 }
                                               , { "beer", 52, 10 }
                                               , { "suntan cream", 11, 70 }
                                               , { "camera", 32, 30 }
                                               , { "t-shirt", 24, 15 }
                                               , { "trousers", 48, 10 }
                                               , { "umbrella", 73, 40 }
                                               , { "waterproof trousers", 42, 70 }
                                               , { "waterproof overclothes", 43, 75 }
                                               , { "note-case", 22, 80 }
                                               , { "sunglasses", 7, 20 }
                                               , { "towel",  18, 12 }
                                               , { "socks", 4, 50 }
                                               , { "book", 30, 10 }
                                               , { "notebook", 90, 1 }
                                               , { "tent", 200, 150 }
                                       };
    case 2: //zombie apocalypse
        mItems = { { "map", 9, 150 }
                                               , { "compass", 13, 35 }
                                               , { "water", 153, 200 }
                                               , { "sandwich", 50, 160 }
                                               , { "glucose", 15, 60 }
                                               , { "tin", 68, 45 }
                                               , { "banana", 27, 60 }
                                               , { "apple", 39, 40 }
                                               , { "cheese", 23, 30 }
                                               , { "beer", 52, 10 }
                                               , { "suntan cream", 11, 70 }
                                               , { "camera", 32, 30 }
                                               , { "t-shirt", 24, 15 }
                                               , { "trousers", 48, 10 }
                                               , { "umbrella", 73, 40 }
                                               , { "waterproof trousers", 42, 70 }
                                               , { "waterproof overclothes", 43, 75 }
                                               , { "note-case", 22, 80 }
                                               , { "sunglasses", 7, 20 }
                                               , { "towel",  18, 12 }
                                               , { "socks", 4, 50 }
                                               , { "book", 30, 10 }
                                               , { "notebook", 90, 1 }
                                               , { "tent", 200, 150 }
                                       };
    default:
        break;
    }
}

void MainWindow::on_buttonCalculate_clicked()
{
    std::sort( mItems.begin(), mItems.end() );
    uint64_t maxWeight = ui->leMaxWeight->text().toULong();

    KnapsackProblem problem{ mItems, maxWeight };
    KnapsackSolver solver{ problem };
    solver.set_two_point_crossover(true);
    KnapsackSolver::Genome = solver.run().genome();
}

void MainWindow::displayPreset(const KnapsackItemsDeque &items)
{
    for( const KnapsackItem& kItem : items ) {
        int rows = ui->tableValues->model()->rowCount();
        std::unique_ptr<QStandardItem> item1{ new QStandardItem( QString::fromStdString(kItem.name) ) };
        model->setItem( rows, 0, item1.release() );
        std::unique_ptr<QStandardItem> item2{ new QStandardItem{ QString::number(kItem.cost) } };
        model->setItem( rows, 1, item2.release() );
        std::unique_ptr<QStandardItem> item3{ new QStandardItem{ QString::number(kItem.value) } };
        model->setItem( rows, 2, item3.release() );
    }
    ui->tableValues->setModel( model );
    ui->tableValues->resizeColumnsToContents();
}
} //sc3 namespace
