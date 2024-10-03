//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <iostream>


#include "asset.h"

namespace embedonix::trading_tax_calculator {

  /**
   * The Transaction class represents a financial transaction involving an asset.
   */
  class Transaction {

  private:
    Asset mAsset;
    TransactionType mType = TransactionType::Unknown;
    std::string mDateString;
    double mValue;
    std::string mCurrency;

  public:
    Transaction() = default;

    Transaction(const Asset& asset, TransactionType type, const std::string& dateString, double value);

    Transaction(const Asset& asset, TransactionType type, const std::string& dateString, double value,
                std::string currency);

    /**
     * Retrieves the asset associated with the transaction.
     *
     * @return A const reference to the asset of the transaction.
     */
    const Asset&
    getAsset() const;

    /**
     * Retrieves the type of the transaction.
     *
     * @return The type of the transaction as a TransactionType enum.
     */
    TransactionType
    getType() const;

    /**
     * Retrieves the date string associated with the transaction.
     *
     * @return A const reference to the date string of the transaction.
     */
    const
    std::string& getDateString() const;

    /**
     * Retrieves the value associated with the transaction.
     *
     * @return The value of the transaction in double.
     */
    double
    getValue() const;

    void
    setAsset(const Asset& asset);

    void
    setType(TransactionType type);

    void
    setDateString(const std::string& dateString);

    void
    setValue(double value);

    void
    setCurrency(const std::string& currency);

    std::string
    getCurrency() const;

/**
 * Overload of the output stream operator for the Transaction class.
 *
 * @param os The output stream.
 * @param transaction The transaction object to output.
 * @return The output stream with the transaction information.
 */
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
      os << "Transaction("
         << "Asset: " << transaction.getAsset() << ", "
         << "Type: " << static_cast<std::underlying_type_t<TransactionType>>(transaction.getType()) << ", "
         << "Date: " << transaction.getDateString() << ", "
         << "Value: " << transaction.getValue() << " " << transaction.getCurrency()
         << ")";
      return os;
    }
  };

}
