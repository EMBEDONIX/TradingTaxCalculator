//
// Created by Saeid Yazdani on 9/30/2024.
//

#include "asset.h"

namespace embedonix::trading_tax_calculator {

  Asset::Asset(const std::string &mName, const std::string &mSymbol) : mName(mName), mSymbol(mSymbol) {}

  const std::string &Asset::getName() const {
    return mName;
  }

  const std::string &Asset::getSymbol() const {
    return mSymbol;
  }

  Asset::Asset() : mName{"_default_asset_name_"}, mSymbol{"_default_asset_symbol_"} {}

  void Asset::setSymbol(const std::string &symbol) {
    mSymbol = symbol;
  }

  void Asset::setName(const std::string &name) {
    mName = name;
  }
}