//
// Created by Saeid Yazdani on 9/30/2024.
//

#ifndef TRADINGTAXCALCULATOR_MAINWINDOW_H
#define TRADINGTAXCALCULATOR_MAINWINDOW_H

#include <QMainWindow>

namespace embedonix_tax_calculator_ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        void addToAssetLists(QString symbol);

        ~MainWindow() override;

    private:
        Ui::MainWindow *ui;
    };
} // embedonix_tax_calculator_ui

#endif //TRADINGTAXCALCULATOR_MAINWINDOW_H
