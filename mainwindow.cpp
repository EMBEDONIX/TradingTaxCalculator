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

#ifdef __DEBUG__
    mCapitalComTable->loadFile(R"(H:\GoogleDrive\Accounting\Brokers\Capital\TRADING\all_20240928.csv)");
#endif

    connect(ui->action_Open, &QAction::triggered,
            this, [this]() {
              QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CSV Files (*.csv)"));
              if (!fileName.isEmpty()) {
                mCapitalComTable->loadFile(fileName);
              }
            });

    connect(mCapitalComTable, &AssetResultTableModelCapitalCom::setOfYearsInData,
            this, &MainWindow::receiveYears, Qt::QueuedConnection);

    connect(ui->comboBoxYears, &QComboBox::currentTextChanged,
            mCapitalComTable, &AssetResultTableModelCapitalCom::filterDataForYear);
  }

  MainWindow::~MainWindow() {
    delete ui;
  }

  void MainWindow::receiveYears(const QStringList& years) {
    ui->comboBoxYears->clear();
    for (const auto& year: years) {
      ui->comboBoxYears->addItem(year);
    }
  }

} // embedonix_tax_calculator_ui
