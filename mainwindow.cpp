//
// Created by Saeid Yazdani on 9/30/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "capital_com_loader.h"
namespace embedonix::trading_tax_calculator::qt {

  MainWindow::MainWindow(QWidget* parent) :
          QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    new AssetResultTableModelCapitalCom(this);
    mCapitalComTable = new AssetResultTableModelCapitalCom(this);
    ui->tableViewResults->setModel(mCapitalComTable);

    connect(ui->action_Open, &QAction::triggered,
            this, [this](){
      QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CSV Files (*.csv)"));
      if(!fileName.isEmpty()) {
        mCapitalComTable->loadFile(fileName);
      }


    });


    connect(ui->comboBoxYears, &QComboBox::currentTextChanged,
            this, &MainWindow::updateAssetListByYear);

    connect(ui->listWidgetAssets, &QListWidget::currentTextChanged,
            this, &MainWindow::updateResultForSymbol);

  }

  MainWindow::~MainWindow() {
    delete ui;
  }

  void MainWindow::updateAssetListByYear(const QString& year) {
    qDebug() << "Currently we need to show results for the year " << year;
  }

  void MainWindow::updateResultForSymbol(const QString& symbol) {
    ui->textEditResults->clear();
  }

} // embedonix_tax_calculator_ui
