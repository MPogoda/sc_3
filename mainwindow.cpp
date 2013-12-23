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

    ui->leMaxWeight->setValidator( new QIntValidator(1, 2000) );

    model->setHorizontalHeaderItem(0, new QStandardItem{ QString{ "Name" } } );
    model->setHorizontalHeaderItem(1, new QStandardItem{ QString{ "Weight (hg)" } });
    model->setHorizontalHeaderItem(2, new QStandardItem{ QString{ "Value" } });
    ui->tableValues->setModel(model);

    mItems = { { "map", 1, 150 }
               , { "compass", 4 , 35 }
               , { "water", 20, 200 }
               , { "sandwich", 5, 160 }
               , { "glucose", 2, 60 }
               , { "tin", 3, 45 }
               , { "banana", 2, 60 }
               , { "apple", 1, 40 }
               , { "cheese", 3, 30 }
               , { "beer", 30, 10 }
               , { "suntan cream", 1, 70 }
               , { "camera", 15, 30 }
               , { "t-shirt", 2, 15 }
               , { "trousers", 5, 10 }
               , { "umbrella", 16, 40 }
               , { "waterproof trousers", 4, 70 }
               , { "waterproof overclothes", 19, 75 }
               , { "note-case", 6, 80 }
               , { "sunglasses", 2, 20 }
               , { "towel",  5, 12 }
               , { "socks", 1, 50 }
               , { "book", 5, 10 }
               , { "notebook", 3, 1 }
               , { "tent", 40, 150 }
               , { "shotgun", 63, 20 }
               , { "baseball bat", 15, 50 }
               , { "shotgun ammo", 20, 15 }
               , { "handgun", 17, 25 }
               , { "handgun ammo", 10, 20 }
               , { "helmet", 8, 30 }
               , { "first-aid kit", 21, 100 }
               , { "knife", 3, 50 }
               , { "napalm", 70, 10 }
               , { "medical alcohol", 10, 80}
            };
    displayPreset( mItems );
}

MainWindow::~MainWindow()
{
    delete ui;
}
void
MainWindow::on_cbValuePreset_currentIndexChanged(int index)
{
//TODO: adjust values
    switch (index) {
    case 0: //trip
        mItems = { { "map", 1, 150 }
                   , { "compass", 4 , 35 }
                   , { "water", 20, 200 }
                   , { "sandwich", 5, 160 }
                   , { "glucose", 2, 60 }
                   , { "tin", 3, 45 }
                   , { "banana", 2, 60 }
                   , { "apple", 1, 40 }
                   , { "cheese", 3, 30 }
                   , { "beer", 30, 10 }
                   , { "suntan cream", 1, 70 }
                   , { "camera", 15, 30 }
                   , { "t-shirt", 2, 15 }
                   , { "trousers", 5, 10 }
                   , { "umbrella", 16, 40 }
                   , { "waterproof trousers", 4, 70 }
                   , { "waterproof overclothes", 19, 75 }
                   , { "note-case", 6, 80 }
                   , { "sunglasses", 2, 20 }
                   , { "towel",  5, 12 }
                   , { "socks", 1, 50 }
                   , { "book", 5, 10 }
                   , { "notebook", 3, 1 }
                   , { "tent", 40, 150 }
                   , { "shotgun", 63, 20 }
                   , { "baseball bat", 15, 50 }
                   , { "shotgun ammo", 20, 15 }
                   , { "handgun", 17, 25 }
                   , { "handgun ammo", 10, 20 }
                   , { "helmet", 8, 30 }
                   , { "first-aid kit", 21, 100 }
                   , { "knife", 3, 50 }
                   , { "napalm", 60, 10 }
                   , { "medical alcohol", 10, 80}
                 };
        break;
    case 1: //alpinism
        mItems = { { "map", 1, 100 }
                   , { "compass", 4 , 170 }
                   , { "water", 20, 200 }
                   , { "sandwich", 5, 160 }
                   , { "glucose", 2, 150 }
                   , { "tin", 3, 200 }
                   , { "banana", 2, 50 }
                   , { "apple", 1, 70 }
                   , { "cheese", 3, 180 }
                   , { "beer", 30, 10 }
                   , { "suntan cream", 1, 10 }
                   , { "camera", 15, 60 }
                   , { "t-shirt", 2, 15 }
                   , { "trousers", 5, 10 }
                   , { "umbrella", 16, 40 }
                   , { "waterproof trousers", 4, 20 }
                   , { "waterproof overclothes", 19, 25 }
                   , { "note-case", 6, 60 }
                   , { "sunglasses", 2, 10 }
                   , { "towel",  5, 12 }
                   , { "socks", 1, 60 }
                   , { "book", 5, 10 }
                   , { "notebook", 3, 10 }
                   , { "tent", 40, 200 }
                   , { "shotgun", 63, 10 }
                   , { "baseball bat", 15, 10 }
                   , { "shotgun ammo", 20, 5 }
                   , { "handgun", 17, 25 }
                   , { "handgun ammo", 10, 20 }
                   , { "helmet", 8, 140 }
                   , { "first-aid kit", 21, 100 }
                   , { "knife", 3, 70 }
                   , { "napalm", 60, 10 }
                   , { "medical alcohol", 10, 160}
                 };
        break;
    case 2: //zombie apocalypse
        mItems = { { "map", 1, 150 }
                   , { "compass", 4 , 135 }
                   , { "water", 20, 200 }
                   , { "sandwich", 5, 180 }
                   , { "glucose", 2, 150 }
                   , { "tin", 3, 190 }
                   , { "banana", 2, 160 }
                   , { "apple", 1, 140 }
                   , { "cheese", 3, 180 }
                   , { "beer", 30, 150 }
                   , { "suntan cream", 1, 20 }
                   , { "camera", 15, 10 }
                   , { "t-shirt", 2, 15 }
                   , { "trousers", 5, 10 }
                   , { "umbrella", 16, 60 }
                   , { "waterproof trousers", 4, 10 }
                   , { "waterproof overclothes", 19, 15 }
                   , { "note-case", 6, 20 }
                   , { "sunglasses", 2, 80 }
                   , { "towel",  5, 12 }
                   , { "socks", 1, 50 }
                   , { "book", 5, 30 }
                   , { "notebook", 3, 20 }
                   , { "tent", 40, 90 }
                   , { "shotgun", 63, 170 }
                   , { "baseball bat", 15, 130 }
                   , { "shotgun ammo", 20, 120 }
                   , { "handgun", 17, 190 }
                   , { "handgun ammo", 10, 150 }
                   , { "helmet", 8, 100 }
                   , { "first-aid kit", 21, 140 }
                   , { "knife", 3, 200 }
                   , { "napalm", 60, 150 }
                   , { "medical alcohol", 10, 120}
                 };
        break;
    case 3: //test
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
    default:
        break;
    }
    displayPreset( mItems );
}

void
MainWindow::on_buttonCalculate_clicked()
{
    std::sort( mItems.begin(), mItems.end() );
    uint64_t maxWeight = ui->leMaxWeight->text().toULong();
    maxWeight *= 10; //to g*10^2

    KnapsackProblem problem{ mItems, maxWeight };
    KnapsackSolver solver{ problem };
    solver.set_two_point_crossover(true);
    KnapsackSolution solution = solver.run();
    displayKnapsackSolution( solution );
}

void
MainWindow::displayPreset(const KnapsackItemsDeque &items)
{
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem{ QString{ "Name" } } );
    model->setHorizontalHeaderItem(1, new QStandardItem{ QString{ "Weight (hg)" } });
    model->setHorizontalHeaderItem(2, new QStandardItem{ QString{ "Value" } });
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

KnapsackItemsDeque
MainWindow::genotypeToPhenotype(const KnapsackSolution::Genome &genotype)
{
    KnapsackItemsDeque phenotype;
    for (unsigned i=0; i<genotype.size(); ++i) {
        if (genotype[i]) {
            phenotype.push_back( mItems[i] );
        }
    }
    return phenotype;
}

void
MainWindow::displayKnapsackSolution(const KnapsackSolution &solution)
{
    KnapsackItemsDeque phenotype = genotypeToPhenotype( solution.genome() );
    QString knapsackContents;
    double weight = 0;
    for ( const KnapsackItem& kItem : phenotype ) {
        knapsackContents += QString::fromStdString("- " + kItem.name + "\n");
        weight += kItem.cost;
    }
    ui->lbKnapsack->setText(knapsackContents);

    weight /= 10;
    ui->lbKnapsackWeight->setText(QString::number(weight, 'f', 1));
}

} //sc3 namespace
