//
// Created by Saeid Yazdani on 10/3/2024.
//

#include <unordered_map>
#include <algorithm>

#include "asset_types.h"

namespace embedonix::trading_tax_calculator {

  std::string
  assetTypeToString(AssetType asset) {
    switch (asset) {
      case AssetType::Stock:
        return "Stock";
      case AssetType::Bond:
        return "Bond";
      case AssetType::Commodity:
        return "Commodity";
      case AssetType::Forex:
        return "Forex";
      case AssetType::Cryptocurrency:
        return "Cryptocurrency";
      case AssetType::RealEstate:
        return "RealEstate";
      case AssetType::Derivative:
        return "Derivative";
      case AssetType::MutualFund:
        return "MutualFund";
      case AssetType::ETF:
        return "ETF";
      case AssetType::PreciousMetal:
        return "PreciousMetal";
      case AssetType::Collectible:
        return "Collectible";
      case AssetType::CFD:
        return "CFD";
      default:
        throw std::invalid_argument("Invalid AssetType");
    }
  }

  AssetType
  stringToAssetType(const std::string& assetString) {
    // Convert input string to lowercase
    std::string lowerCaseAsset = assetString;
    std::transform(lowerCaseAsset.begin(), lowerCaseAsset.end(),
                   lowerCaseAsset.begin(), ::tolower);

    static const std::unordered_map<std::string, AssetType> assetMap = {
            {"stock",            AssetType::Stock},
            {"stocks",           AssetType::Stock},           // Plural
            {"bond",             AssetType::Bond},
            {"bonds",            AssetType::Bond},             // Plural
            {"commodity",        AssetType::Commodity},
            {"commodities",      AssetType::Commodity},  // Plural
            {"forex",            AssetType::Forex},
            {"currency",         AssetType::Forex},         // Synonym
            {"cryptocurrency",   AssetType::Cryptocurrency},
            {"cryptocurrencies", AssetType::Cryptocurrency}, // Plural
            {"crypto",           AssetType::Cryptocurrency},  // Common abbr.
            {"realestate",       AssetType::RealEstate},
            {"property",         AssetType::RealEstate},    // Synonym
            {"derivative",       AssetType::Derivative},
            {"derivatives",      AssetType::Derivative}, // Plural
            {"mutualfund",       AssetType::MutualFund},
            {"mutualfunds",      AssetType::MutualFund}, // Plural
            {"etf",              AssetType::ETF},
            {"etfs",             AssetType::ETF},               // Plural
            {"preciousmetal",    AssetType::PreciousMetal},
            {"preciousmetals",   AssetType::PreciousMetal}, // Plural
            {"collectible",      AssetType::Collectible},
            {"collectibles",     AssetType::Collectible}, // Plural
            {"cfd",              AssetType::CFD}, // contract for diff.
            {"cfds",             AssetType::CFD} // Plural CFD
    };

    auto it = assetMap.find(lowerCaseAsset);
    if (it != assetMap.end()) {
      return it->second;
    } else {
      throw std::invalid_argument("Invalid asset type string: " + assetString);
    }
  }

}