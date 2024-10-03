//
// Created by Saeid Yazdani on 9/30/2024.
//

#include "asset.h"

namespace embedonix::trading_tax_calculator {

  Asset::Asset(const std::string& mName, const std::string& mSymbol) : mName(mName), mSymbol(mSymbol) {}

  const
  std::string& Asset::getName() const {
    return mName;
  }

  const
  std::string& Asset::getSymbol() const {
    return mSymbol;
  }

  void
  Asset::setSymbol(const std::string& symbol) {
    mSymbol = symbol;
  }

  void
  Asset::setName(const std::string& name) {
    mName = name;
  }

  bool
  Asset::addTransactionType(TransactionType type) {
    auto ret = mTransactionTypes.insert(type);
    return ret.second; // false if duplicate/insertion fail
  }

  AssetType
  Asset::getAssetType() const { return mAssetType; }

  void
  Asset::setAssetType(AssetType assetType) { mAssetType = assetType; }

  void
  Asset::setTransactionTypes(const std::set<TransactionType>& typesSet) {
    mTransactionTypes.clear();
    mTransactionTypes = typesSet;
  }


}