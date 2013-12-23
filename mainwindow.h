#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QString>

#include "lib/knapsack.h"

namespace Ui {
class MainWindow;
}

namespace sc3
{
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_cbValuePreset_currentIndexChanged(int index);

    void on_buttonCalculate_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *model;
    KnapsackItemsDeque mItems;

    void displayPreset( const KnapsackItemsDeque& items );
};
} //sc3 namespace
#endif // MAINWINDOW_H
