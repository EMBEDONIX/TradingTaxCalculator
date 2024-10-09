//
// Created by Saeid Yazdani on 10/2/2024.
//

#pragma once

#include <QAbstractTableModel>
#include <QStringLiteral>

#include "capital_com_loader.h"

namespace embedonix::trading_tax_calculator::qt {

  const QString AllYearsOption = QString("All");

  /**
   * @brief Represents a row in a table with associated data.
   *
   * The TableRow struct encapsulates a row that consists of:
   * - An asset of type Asset.
   * - A set of years for which the data is relevant.
   * - A map containing all value types and their corresponding values.
   * - A nested map that stores values for each type and year.
   *
   * The asset represents a financial or tangible item with attributes like name, symbol, and types.
   * The years set is used for storing the different years of data.
   * The allValuesPerTypeMap is a single-level map that associates each value type with its corresponding value.
   * The valuesPerTypePerYearMap is a multi-level map that associates a pair of type and year with a value.
   */
  struct TableRow {
    Asset asset;
    QSet<QString> years;
    QMap<QString, double> allValuesPerTypeMap;

    QMap<QPair<QString, QString>, double> valuesPerTypePerYearMap;
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

    /**
     * @brief Calculates the total sum for a given transaction type across
     * all years.
     *
     * This function iterates through all available table rows and accumulates
     * the sum of values associated with the specified TransactionType.
     *
     * @param type The type of transaction as defined by the TransactionType
     * enum.
     * @return The calculated sum of all values for the specified transaction
     * type over all years.
     */
    double
    getSumPerTypeAllYears(TransactionType type) {
      double sum = 0;
      for (const auto& row: rows) {

        sum += row.allValuesPerTypeMap[QString::fromStdString(
                transactionTypeToString(type))];
      }
      return sum;
    }

    /**
     * @brief Calculates the total sum for a given transaction type in a specific year.
     *
     * This function determines whether to calculate the sum for all available years
     * or for a specific year based on the provided year parameter. If the year is
     * specified as "All", it will call getSumPerTypeAllYears to calculate the sum
     * across all years. Otherwise, it calculates the sum specifically for the provided
     * year.
     *
     * @param type The type of transaction as defined by the TransactionType enum.
     * @param year The year for which to calculate the sum. It can be a specific year
     * or "All" to indicate all years.
     * @return The calculated sum of transactions for the specified type and year.
     */
    double
    getSumPerTypePerYear(TransactionType type, QString year) {
      bool all = (year.toLower() == AllYearsOption.toLower());
      if (all) {
        return getSumPerTypeAllYears(type);
      }

      QString typeStr = QString::fromStdString(transactionTypeToString(type));

      double sum = 0;
      for (const auto& row: rows) {

      }

      return sum;
    }


    /**
     * @brief Calculates the total sum for a given transaction type in a
     * specific year or across all years.
     *
     * This function checks whether the provided year parameter corresponds to
     * all years or a specific year.
     * If the year is specified as "All" (case-insensitive), it calls
     * getSumPerTypeAllYears to calculate the sum
     * across all years. Otherwise, it calls getSumPerTypePerYear to calculate
     * the sum for the specified year.
     *
     * @param typeStr The type of transaction as a QString.
     * @param year The year for which to calculate the sum, or "All" to indicate
     * all years.
     * @return The calculated sum of transactions for the specified type and
     * year.
     */
    double getSumPerTypePerYear(QString typeStr, QString year) {
      bool all = (year.toLower() == AllYearsOption.toLower());
      if (all) {
        return getSumPerTypeAllYears(
                stringToTransactionType(typeStr.toStdString()));
      }

      return getSumPerTypePerYear(
              stringToTransactionType(typeStr.toStdString()), year);
    }

    double getSumPerTypeAllYears(QString typeStr) {
      double sum = 0;
      for (const auto& row: rows) {
        sum += row.allValuesPerTypeMap[typeStr];
      }
      return sum;
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


    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

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
