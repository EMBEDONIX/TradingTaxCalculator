//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <embedonix/simplelibs/stringtools/trim.h>
#include <algorithm>

#include "asset.h"

namespace embedonix::trading_tax_calculator {

  /**
   * Enum class representing different types of financial transactions.
   *
   * Enumerators:
   * - Unknown: Represents an unknown or unspecified type of transaction.
   * - Trade: Represents a transaction that involves buying/selling financial instruments.
   * - Swap: Represents a transaction that involves fees.
   * - Dividend: Represents a transaction that involves the redistribution of profit to shareholders.
   * - Deposit: Represents a transaction that involves adding funds to an account.
   * - Transfer: Represents a transaction that involves moving funds from one account to another.
   */
  enum class TransactionType : unsigned char {
    Unknown = 0,
    Trade,
    Swap,
    Dividend,
    Deposit,
    Transfer
  };

  TransactionType getTransactionTypeFromString(std::string_view typeString) noexcept;

  /**
   * The Transaction class represents a financial transaction involving an asset.
   */
  class Transaction {
    Asset mAsset;
    TransactionType mType;
    std::string mDateString;
    double mValue;

  public:
    Transaction() = default;

    Transaction(const Asset &asset, TransactionType type, const std::string &dateString, double value);

    /**
     * Retrieves the asset associated with the transaction.
     *
     * @return A const reference to the asset of the transaction.
     */
    const Asset &getAsset() const;

    /**
     * Retrieves the type of the transaction.
     *
     * @return The type of the transaction as a TransactionType enum.
     */
    TransactionType getType() const;

    /**
     * Retrieves the date string associated with the transaction.
     *
     * @return A const reference to the date string of the transaction.
     */
    const std::string &getDateString() const;

    /**
     * Retrieves the value associated with the transaction.
     *
     * @return The value of the transaction in double.
     */
    double getValue() const;

    void setAsset(const Asset &asset);

    void setType(TransactionType type);

    void setDateString(const std::string &dateString);

    void setValue(double value);

    // Move constructor
    Transaction(Transaction &&other) noexcept
            : mAsset(std::move(other.mAsset)),
              mType(std::move(other.mType)),
              mDateString(std::move(other.mDateString)),
              mValue(other.mValue) {
      other.mValue = 0;
    }

    // Move assignment operator
    Transaction &operator=(Transaction &&other) noexcept {
      if (this != &other) {
        mAsset = std::move(other.mAsset);
        mType = std::move(other.mType);
        mDateString = std::move(other.mDateString);
        mValue = other.mValue;
        other.mValue = 0;
      }
      return *this;
    }

    // Copy constructor
    Transaction(const Transaction &other)
            : mAsset(other.mAsset),
              mType(other.mType),
              mDateString(other.mDateString),
              mValue(other.mValue) {}

    // Copy assignment operator
    Transaction& operator=(const Transaction& other) {
      if (this != &other) {
        mAsset = other.mAsset;
        mType = other.mType;
        mDateString = other.mDateString;
        mValue = other.mValue;
      }
      return *this;
    }

  };

}
