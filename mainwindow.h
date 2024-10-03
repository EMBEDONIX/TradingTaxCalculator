//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <QObject>
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QListWidgetItem>

#include "capitalcom_asset_result_table_model.h"

namespace embedonix::trading_tax_calculator::qt {

  QT_BEGIN_NAMESPACE
  namespace Ui { class MainWindow; }
  QT_END_NAMESPACE

  class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;

  private:
    Ui::MainWindow* ui;
    AssetResultTableModelCapitalCom* mCapitalComTable;

  private slots:

    void updateAssetListByYear(const QString& year);

    void updateResultForSymbol(const QString& symbol);


  };
} // end namespace

