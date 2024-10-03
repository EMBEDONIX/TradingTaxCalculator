//
// Created by Saeid Yazdani on 10/2/2024.
//

#include "capitalcom_asset_result_table_model.h"
#include "capital_com_loader.h"

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
    return 5;
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

    if (orientation == Qt::Horizontal) {
      switch (section) {
        case 0:
          return QString("Symbol");
        case 1:
          return QString("Name");
        case 2:
          return QString("Trade");
        case 3:
          return QString("Swap");
        case 4:
          return QString("Dividend");
        default:
          return QVariant();
      }
    } else {
      return QString("Row %1").arg(section + 1);
    }
  }

  void AssetResultTableModelCapitalCom::loadFile(const QString& fileName) {
    auto transactions =
            capitalcom::generateTransactionsFromCsvFile(fileName.toStdString());
    auto assets =
            capitalcom::getUniqueAssetsInTransactions(transactions);

    if (!assets.size()) {
      return;
    }

    beginResetModel();

    mResults.clear();
    mResults.resize(assets.size());
    auto it = assets.begin();
    for (size_t i = 0; i < assets.size(); ++i) {

      mResults[i] << QString::fromStdString(it->getSymbol());
      mResults[i] << QString::fromStdString(it->getName());
      mResults[i] << QString::fromStdString(assetTypeToString(it->getAssetType()));
      mResults[i] << QString::fromStdString("0");
      mResults[i] << QString::fromStdString("1");
      it++;
    }

    endResetModel();


  }


} // qt