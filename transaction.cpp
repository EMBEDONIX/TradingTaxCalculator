//
// Created by Saeid Yazdani on 9/30/2024.
//

#include <algorithm>

#include "transaction.h"

namespace embedonix::trading_tax_calculator {

  Transaction::Transaction(const Asset& asset, TransactionType type, const std::string& dateString, double value)
          : mAsset(asset), mType(type), mDateString(dateString), mValue(value) {}

  Transaction::Transaction(const Asset& asset, TransactionType type, const std::string& dateString, double value,
                           std::string currency) : mCurrency(currency) {
    Transaction(asset, type, dateString, value);
  }

  const Asset&
  Transaction::getAsset() const {
    return mAsset;
  }

  TransactionType
  Transaction::getType() const {
    return mType;
  }

  const std::string&
  Transaction::getDateString() const {
    return mDateString;
  }

  double
  Transaction::getValue() const {
    return mValue;
  }

  void
  Transaction::setAsset(const Asset& asset) {
    mAsset = asset;
  }

  void
  Transaction::setType(TransactionType type) {
    mType = type;
  }

  void
  Transaction::setDateString(const std::string& dateString) {
    mDateString = dateString;
  }

  void
  Transaction::setValue(double value) {
    mValue = value;
  }

  void
  Transaction::setCurrency(const std::string& currency) {
    Transaction::mCurrency = currency;
  }

  std::string
  Transaction::getCurrency() const {
    return mCurrency;
  }

} // End
