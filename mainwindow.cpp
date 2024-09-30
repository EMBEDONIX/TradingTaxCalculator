//
// Created by Saeid Yazdani on 9/30/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"

namespace embedonix_tax_calculator_ui {
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
    }

    void MainWindow::addToAssetLists(QString symbol) {

    }

    MainWindow::~MainWindow() {
        delete ui;
    }
} // embedonix_tax_calculator_ui
