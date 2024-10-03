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
    return mHeaders.size() + 3;
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

      for (size_t i = 0; i < mHeaders.size(); ++i) {
        if (i == section) {
          return mHeaders.at(i);
        }
      }

    } else {
      return QString("Row %1").arg(section + 1);
    }

    return QVariant("__BAD__"); // if nothing to do, return something
  }

  void AssetResultTableModelCapitalCom::loadFile(const QString& fileName) {
    auto transactions =
            capitalcom::generateTransactionsFromCsvFile(fileName.toStdString());
    auto assets =
            capitalcom::getUniqueAssetsInTransactions(transactions);

    if (!assets.size()) {
      return;
    }

//    QVector<QPair<Asset, QVector<TransactionType>>> assetsWithTypes;
//    for (const auto& asset: assets) {
//      auto types = capitalcom::getTransactionTypesForAsset(transactions, asset);
//      QPair<Asset, QVector<TransactionType>> pair;
//      pair.first = asset;
//      for (const auto& type: types) {
//        pair.second.push_back(type);
//      }
//      std::sort(pair.second.begin(), pair.second.end());
//      assetsWithTypes.push_back(pair);
//    }
//
//    // Find out the asset with highers number of transactiontypes involved
//    auto maxTypesIt = std::max_element(assetsWithTypes.begin(), assetsWithTypes.end(),
//                                       [](const auto& a,
//                                          const auto& b) {
//                                         return a.second.size() < b.second.size();
//                                       });

    auto involvedTypes = capitalcom::getTypesInTransactions(transactions);

    beginResetModel();

    // Update header of the table according to involved transaction types
    mHeaders.clear();
    mHeaders.shrink_to_fit();

    mHeaders << "Date";
    mHeaders << "Symbol";
    mHeaders << "Name";

    for (const auto& type: involvedTypes) {
      mHeaders << QString::fromStdString(transactionTypeToString(type));
    }

    mResults.clear();
    mResults.resize(assets.size());
    auto it = assets.begin();
    for (size_t i = 0; i < assets.size(); ++i) {

      mResults[i] << QString::fromStdString(it->getSymbol());
      mResults[i] << QString::fromStdString(it->getName());
      mResults[i] << QString::fromStdString(assetTypeToString(it->getAssetType()));

      for (size_t j = 0; j < mHeaders.size(); ++j) {
        mResults[i] << "000";
      }
      it++;
    }

    endResetModel();


  }


} // qt