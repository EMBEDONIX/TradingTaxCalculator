//
// Created by Saeid Yazdani on 10/2/2024.
//


#include <QMap>

#include "capitalcom_asset_result_table_model.h"
#include "capital_com_loader.h"
#include "mainwindow.h"

namespace embedonix::trading_tax_calculator::qt {

  AssetResultTableModelCapitalCom::AssetResultTableModelCapitalCom(QObject* parent)
          : QAbstractTableModel(parent) {
    /* Nothing to do here */
  }

  AssetResultTableModelCapitalCom::AssetResultTableModelCapitalCom(QVector<QStringList> data,
                                                                   QObject* parent)
          : mResults{data}, QAbstractTableModel{parent} {
    /* Nothing to do here */
  }

  int AssetResultTableModelCapitalCom::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mResults.size();
  }

  int AssetResultTableModelCapitalCom::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mHeaders.size();
  }

  QVariant AssetResultTableModelCapitalCom::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
      return QVariant();
    }

    const auto& item = mResults.at(index.row());
    return item.at(index.column());
  }

  QVariant AssetResultTableModelCapitalCom::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
      return QVariant();
    }

    if (!mHeaders.size()) { // no header available
      return QVariant();
    }

    if (orientation == Qt::Horizontal) {

      for (size_t i = 0; i < mHeaders.size(); ++i) {
        if (i == section) {
          return mHeaders.at(i);
        }
      }

    } else {
      return QString("TableRow %1").arg(section + 1);
    }

    return QVariant("__ERROR__"); // if nothing to do, return something
  }

  void AssetResultTableModelCapitalCom::loadFile(const QString& fileName) {

    {
      auto transactions =
              capitalcom::generateTransactionsFromCsvFile(fileName.toStdString());
      updateCachedData(transactions);
    }

    QStringList years;
    for (const auto& year: mDataCache.uniqueYears) {
      years << QString::fromStdString(year);
    }
    years.sort(); // sort the years
    // We need to insert "All" as the first and default item in the list
    years.prepend(tr("All"));


    beginResetModel(); // Begin update UI
    updateHeaders();
    updateResuts(AllYearsOption);
    endResetModel(); // End update UI

    // FIXME this does not work, does not trigger designated slot in MainWindow
    // emit setOfYearsInData(years);

    // This is a workaround to the problem above. Directly call the slot
    auto mwPtr = dynamic_cast<MainWindow*>(this->parent());
    mwPtr->receiveYears(years);


  }

  void AssetResultTableModelCapitalCom::updateHeaders() {
    // Update header of the table according to involved transaction types
    mHeaders.clear();
    mHeaders.shrink_to_fit();

    mHeaders << "Year";
    mHeaders << "Symbol";
    mHeaders << "Name";
    mHeaders << "Type";

    for (const auto& type: mDataCache.involvedTypes) {
      mHeaders << QString::fromStdString(transactionTypeToString(type));
    }
  }

  bool
  AssetResultTableModelCapitalCom::updateCachedData(std::vector<Transaction>& transactions) {

    auto assets =
            capitalcom::getUniqueAssetsInTransactions(transactions);
    if (!assets.size()) {
      return false;
    }
    auto uniqueYears = capitalcom::getYearsInTransactions(transactions);
    auto involvedTypes = capitalcom::getTypesInTransactions(transactions);

    mDataCache.invalidate();
    mDataCache.transactions = std::move(transactions);
    mDataCache.uniqueAssets = std::move(assets);
    mDataCache.uniqueYears = std::move(uniqueYears);
    mDataCache.involvedTypes = std::move(involvedTypes);

    return true;
  }

  void
  AssetResultTableModelCapitalCom::updateResuts(const QString& year) {

    bool filter = true; // Indicate if filtering by year is needed
    if (year.toLower() == AllYearsOption.toLower()) {
      filter = false;
    }


    QVector<TableRow> rows;

    for (const auto& asset: mDataCache.uniqueAssets) {
      TableRow row;
      row.asset = asset;
      for (const auto& type: mDataCache.involvedTypes) {
        QString typeString = QString::fromStdString(transactionTypeToString(type));
        row.allValuesPerTypeMap[typeString] = 0.0;
        for (const auto& uniqueYear: mDataCache.uniqueYears) {
          row.valuesPerYearPerTypeMap[{typeString, QString::fromStdString(uniqueYear)}] = 0.0;
        }
      }
      rows.push_back(row);
    }

    for (const auto& action: mDataCache.transactions) {
      for (auto& row: rows) {
        if (row.asset == action.getAsset()) {
          row.years.insert(QString::fromStdString(action.getDateString()).left(4));
          QString type = QString::fromStdString(transactionTypeToString(action.getType()));
          row.allValuesPerTypeMap[type] += action.getValue();
          row.valuesPerYearPerTypeMap[{type,
                                       QString::fromStdString(action.getDateString()).left(4)}] += action.getValue();
        }
      }
    }



    // Debug print valuesPerYearPerTypeMap
    for (const auto& row: rows) {
      for (auto it = row.valuesPerYearPerTypeMap.cbegin(); it != row.valuesPerYearPerTypeMap.cend(); ++it) {
        qDebug() << "Year:" << it.key().second << ", Type:" << it.key().first << ", Value:" << it.value();
      }
    }

    // Store in the cache
    mDataCache.rows = rows;

    // Begin updating result vector
    mResults.clear();
    mResults.resize(rows.size());

    for (size_t i = 0; i < rows.size(); ++i) {

      QStringList years = rows[i].years.values();
      years.sort();

      mResults[i] << years.join("\r\n");
      mResults[i] << QString::fromStdString(rows[i].asset.getSymbol());
      mResults[i] << QString::fromStdString(rows[i].asset.getName());
      mResults[i] << QString::fromStdString(assetTypeToString(rows[i].asset.getAssetType()));

      auto it = mDataCache.involvedTypes.begin();

      for (size_t j = 0; j < rows[i].allValuesPerTypeMap.size(); ++j) {
        mResults[i]
                << QString("%1").arg(
                        rows[i].allValuesPerTypeMap.value(QString::fromStdString(transactionTypeToString(*it++)), 0.0));
      }
    }

  }

  void AssetResultTableModelCapitalCom::filterDataForYear(const QString& year) {

    qDebug() << __func__ << "(" << year << ")";

    bool all = (year.toLower() == AllYearsOption.toLower());

    beginResetModel();
    mResults.clear();
    if (!all) {
      mResults.resize(std::count_if(mDataCache.rows.begin(), mDataCache.rows.end(),
                                    [&](TableRow row) {
                                      return row.years.contains(year);
                                    }));
    } else {
      mResults.resize(mDataCache.rows.size());
    }
    int i = 0;
    for (const auto& row: mDataCache.rows) {

      // Only add to mResults when erh
      if (!all && !row.years.contains(year)) {
        continue;
      }

      if (all) { // show all years in the column
        QStringList years = row.years.values();
        years.sort();
        mResults[i] << years.join("\r\n");
      } else if (!all && row.years.contains(year)) { // show only selected year
        mResults[i] << year;
      } else {
        throw std::invalid_argument(std::format("Invalid argument for filter by year '{}'",
                                                year.toStdString()).c_str());
      }

      mResults[i] << QString::fromStdString(row.asset.getSymbol());
      mResults[i] << QString::fromStdString(row.asset.getName());
      mResults[i] << QString::fromStdString(assetTypeToString(row.asset.getAssetType()));

      auto it = mDataCache.involvedTypes.begin();

      for (size_t j = 0; j < row.allValuesPerTypeMap.size(); ++j) {
        QString type = QString::fromStdString(transactionTypeToString(*it++));
        if (all) { // all years
          mResults[i]
                  << QString("%1").arg(
                          row.allValuesPerTypeMap.value(type), 0.0);
        } else { // only specific year
          mResults[i]
                  << QString("%1").arg(row.valuesPerYearPerTypeMap.value({type, year}), 13.0);
        }
      }
      i++;
    }

    endResetModel();
  }

} // End namespace