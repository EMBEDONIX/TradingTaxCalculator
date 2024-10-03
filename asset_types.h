//
// Created by Saeid Yazdani on 10/3/2024.
//

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

#include <string>
#include <stdexcept>

namespace embedonix::trading_tax_calculator {



  /**
   * @enum AssetType
   * @brief Enumeration representing various types of financial assets.
   *
   * The AssetType enum class includes a comprehensive list of asset categories
   * that are commonly traded or invested in the financial markets.
   *
   * @var AssetType::Stock
   * Represents shares of a corporation.
   *
   * @var AssetType::Bond
   * Represents fixed income instruments issued by governments or corporations.
   *
   * @var AssetType::Commodity
   * Represents basic goods like oil, gold, or agricultural products.
   *
   * @var AssetType::Forex
   * Represents currency pairs traded in the foreign exchange market.
   *
   * @var AssetType::Cryptocurrency
   * Represents digital or virtual currencies like Bitcoin or Ethereum.
   *
   * @var AssetType::RealEstate
   * Represents property such as land and buildings.
   *
   * @var AssetType::Derivative
   * Represents financial contracts whose value is derived from underlying assets.
   *
   * @var AssetType::MutualFund
   * Represents investment vehicles pooling money from many investors to purchase securities.
   *
   * @var AssetType::ETF
   * Represents Exchange-Traded Funds, which are marketable securities tracking an index, commodity, or a basket of assets.
   *
   * @var AssetType::PreciousMetal
   * Represents rare, naturally occurring metallic elements like gold or silver.
   *
   * @var AssetType::Collectible
   * Represents items that are worth collecting due to their rarity or popularity, such as art or vintage wines.
   *
   * @var AssetType::CFD
   * Represents Contracts for Difference, which are derivatives used to speculate on the price movement of underlying assets without owning them.
   */
  enum class AssetType {
    Stock,
    Bond,
    Commodity,
    Forex,
    Cryptocurrency,
    RealEstate,
    Derivative,
    MutualFund,
    ETF,
    PreciousMetal,
    Collectible,
    CFD
  };

  /**
   * Converts an AssetType enumeration value to its corresponding string representation.
   *
   * @param asset The AssetType enumeration value to be converted.
   * @return A string representation of the given AssetType.
   */
  std::string
  assetTypeToString(AssetType asset);

  /**
   * Converts a string representation of an asset to its corresponding AssetType enumeration value.
   *
   * This function takes a string that represents an asset type and converts it to the corresponding
   * AssetType enumeration. If the string does not match any known asset types, the function's behavior
   * depends on its implementation, which may include returning a default value or throwing an exception.
   *
   * @param assetString The string representation of the asset type to be converted.
   * @return The AssetType enumeration value corresponding to the given string.
   */
  AssetType
  stringToAssetType(const std::string& assetString);

}