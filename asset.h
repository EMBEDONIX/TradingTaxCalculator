//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once


#include <iostream>
#include <string>
#include <set>

#include "asset_types.h"
#include "transaction_types.h"

namespace embedonix::trading_tax_calculator {

  class Asset {
  private:
    std::string mName;
    std::string mSymbol;
    AssetType mAssetType;
    std::set<TransactionType> mTransactionTypes;

  public:
    const std::string& getName() const;

    void
    setName(const std::string& name);

    const
    std::string& getSymbol() const;

    void
    setSymbol(const std::string& symbol);

    AssetType
    getAssetType() const;

    void
    setAssetType(AssetType assetType);

    void
    setTransactionTypes(const std::set<TransactionType>& typesSet);


  public:
    Asset() = default;

    Asset(const std::string& mName, const std::string& mSymbol);

    bool
    operator==(const Asset& other) const noexcept {
      return mName == other.mName && mSymbol == other.mSymbol
             && mAssetType == other.mAssetType;
    }

    // FIXME this is potentially expensive to have a set for each asset/transaction
    bool
    addTransactionType(TransactionType type);

    auto
    getTransactionTypes() const { return mTransactionTypes; }


    friend std::ostream&
    operator<<(std::ostream& os, const Asset& asset) {
      os << "Asset(Name: " << asset.getName() << ", Symbol: " << asset.getSymbol() << ")";

      // Print the transaction types
      os << ", Transaction Types: [";
      for (const auto& type: asset.getTransactionTypes()) {
        switch (type) {
          case TransactionType::Unknown:
            os << "Unknown";
            break;
          case TransactionType::Trade:
            os << "Trade";
            break;
          case TransactionType::Swap:
            os << "Swap";
            break;
          case TransactionType::Dividend:
            os << "Dividend";
            break;
          case TransactionType::Deposit:
            os << "Deposit";
            break;
          case TransactionType::Transfer:
            os << "Transfer";
            break;
        }
        if (&type != &*--asset.getTransactionTypes().end()) {
          os << ", ";
        }
      }
      os << "]";
      return os;
    }

  };

} // End namespace embedonix::trading_tax_calculator


namespace std {
  template<>
  struct hash<embedonix::trading_tax_calculator::Asset> {
    std::size_t operator()(const embedonix::trading_tax_calculator::Asset& asset) const noexcept {
      return hash<std::string>()(asset.getName())
             ^ (hash<std::string>()(asset.getSymbol()) << 1)
             ^ (hash<int>()(static_cast<int>(asset.getAssetType())) << 2);
    }
  };
}
