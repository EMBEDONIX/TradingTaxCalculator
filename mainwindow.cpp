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
    mCapitalComTable->loadFile(R"(H:\GoogleDrive\Accounting\Brokers\Capital\all\trading_20241005.csv)");
#endif

    connect(ui->action_Open, &QAction::triggered,
            this, [this]() {
              QString fileName = QFileDialog::getOpenFileName(this,
                                                              tr("Open File"), "", tr("CSV Files (*.csv)"));
              if (!fileName.isEmpty()) {
                mCapitalComTable->loadFile(fileName);
              }
            });

    connect(mCapitalComTable, &AssetResultTableModelCapitalCom::setOfYearsInData,
            this, &MainWindow::receiveYears, Qt::QueuedConnection);
  }

  MainWindow::~MainWindow() {
    delete ui;
  }


  void MainWindow::receiveYears(const QStringList& years) {
    // Disconnect (if connected) to prevent event while adding items to combobox
    disconnect(ui->comboBoxYears, &QComboBox::currentTextChanged,
               mCapitalComTable, &AssetResultTableModelCapitalCom::filterDataForYear);
    ui->comboBoxYears->clear();
    for (const auto& year: years) {
      ui->comboBoxYears->addItem(year);
    }
    // Connect textchanged event again
    connect(ui->comboBoxYears, &QComboBox::currentTextChanged,
            mCapitalComTable, &AssetResultTableModelCapitalCom::filterDataForYear);
  }

} // embedonix_tax_calculator_ui
