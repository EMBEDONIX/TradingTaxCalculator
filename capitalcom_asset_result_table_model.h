//
// Created by Saeid Yazdani on 10/2/2024.
//

#pragma once

#include <QAbstractTableModel>
#include <QStringLiteral>

#include "capital_com_loader.h"

namespace embedonix::trading_tax_calculator::qt {

  struct TableRow {
    Asset asset;
    QSet<QString> years;
    QMap<QString, double> map;
    // FIXME need a new map < pair<string, string>, double >
    // For   <year, type>, value
  };

  struct DataCache {
    std::vector<Transaction> transactions;
    std::unordered_set<Asset> uniqueAssets;
    std::unordered_set<std::string> uniqueYears;
    std::unordered_set<TransactionType> involvedTypes;
    QVector<TableRow> rows;

    ~DataCache() {
      invalidate();
    }

    void invalidate() {
      transactions.clear();
      transactions.shrink_to_fit();
      uniqueAssets.clear();
      uniqueYears.clear();
      involvedTypes.clear();
      rows.clear();
      rows.shrink_to_fit();
    }
  };

  class AssetResultTableModelCapitalCom : public QAbstractTableModel {

  Q_OBJECT

  public:

    const QString AllYearsOption = QString("All");

    AssetResultTableModelCapitalCom(QObject* parent = nullptr);

    AssetResultTableModelCapitalCom(QVector<QStringList> data, QObject* parent = nullptr);

    int
    rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int
    columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant
    data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant
    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  public slots:

    void
    loadFile(const QString& fileName);

    void
    filterDataForYear(const QString& year);

  signals:

    void
    setOfYearsInData(const QStringList& years);

  private:
    DataCache mDataCache;
    QVector<QStringList> mResults;
    QVector<QString> mHeaders;

    bool
    updateCachedData(std::vector<Transaction>& transactions);

    void
    updateHeaders();

    void
    updateResuts(const QString& year = "all");

  };

} // qt
