//
// Created by Saeid Yazdani on 9/30/2024.
//

#include "transaction.h"

namespace embedonix {
  namespace trading_tax_calculator {
    Transaction::Transaction(const Asset &asset, TransactionType type, const std::string &dateString, double value)
            : mAsset(asset), mType(type), mDateString(dateString), mValue(value) {}

    const Asset &Transaction::getAsset() const {
      return mAsset;
    }

    TransactionType Transaction::getType() const {
      return mType;
    }

    const std::string &Transaction::getDateString() const {
      return mDateString;
    }

    double Transaction::getValue() const {
      return mValue;
    }

    void Transaction::setAsset(const Asset &asset) {
      mAsset = asset;
    }

    void Transaction::setType(TransactionType type) {
      mType = type;
    }

    void Transaction::setDateString(const std::string &dateString) {
      mDateString = dateString;
    }

    void Transaction::setValue(double value) {
      mValue = value;
    }

    TransactionType getTransactionTypeFromString(std::string_view typeString) noexcept {
      namespace sl = embedonix::simplelibs;
      std::string lowerCase{typeString};
      sl::stringtools::trim::both_sides(lowerCase);
      std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);

      if (lowerCase == "trade") {
        return TransactionType::Trade;
      } else if (lowerCase == "swap") {
        return TransactionType::Swap;
      } else if (lowerCase == "corporate_action") {
        return TransactionType::Dividend;
      } else if (lowerCase == "transfer") {
        return TransactionType::Transfer;
      } else if (lowerCase == "deposit") {
        return TransactionType::Deposit;
      } else {
        return TransactionType::Unknown;
      }
    }
  } // trading_tax_calculator
} // embedonix