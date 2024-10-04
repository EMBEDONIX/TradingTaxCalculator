//
// Created by Saeid Yazdani on 10/2/2024.
//

#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <embedonix/simplelibs/stringtools/trim.h>

#include "transaction_types.h"

namespace embedonix::trading_tax_calculator {

  std::string
  transactionTypeToString(TransactionType transaction) {
    switch (transaction) {
      case TransactionType::Unknown:
        return "Unknown";
      case TransactionType::Trade:
        return "Trade";
      case TransactionType::Correction:
        return "Correction";
      case TransactionType::Swap:
        return "Swap";
      case TransactionType::Dividend:
        return "Dividend";
      case TransactionType::Deposit:
        return "Deposit";
      case TransactionType::Transfer:
        return "Transfer";
      case TransactionType::Withdrawal:
        return "Withdrawal";
      case TransactionType::Adjustment:
        return "Adjustment";
      case TransactionType::Commision:
        return "Commision";
      case TransactionType::Settlement:
        return "Settlement";
      default:
        throw std::invalid_argument("Invalid TransactionType");
    }
  }

  TransactionType
  stringToTransactionType(const std::string& transactionString) {
    // Convert input string to lowercase
    std::string lowerCaseTransaction = transactionString;
    embedonix::simplelibs::stringtools::trim::both_sides(lowerCaseTransaction);
    std::transform(lowerCaseTransaction.begin(), lowerCaseTransaction.end(),
                   lowerCaseTransaction.begin(), ::tolower);

    static const std::unordered_map<std::string, TransactionType>
            transactionMap = {
            {"unknown",                     TransactionType::Unknown},
            {"void",                        TransactionType::Unknown},
            {"trade",                       TransactionType::Trade},
            {"buy",                         TransactionType::Trade},
            {"sell",                        TransactionType::Trade},
            {"swap",                        TransactionType::Swap},
            {"exchange",                    TransactionType::Swap},
            {"overnightfee",                TransactionType::Swap},
            {"weekendovernightfee",         TransactionType::Swap},
            {"corporate_action",            TransactionType::Dividend},
            {"dividend",                    TransactionType::Dividend},
            {"dividends",                   TransactionType::Dividend},
            {"deposit",                     TransactionType::Deposit},
            {"withdrawal",                  TransactionType::Withdrawal},
            {"withdraw",                    TransactionType::Withdrawal},
            {"transfer",                    TransactionType::Transfer},
            {"move",                        TransactionType::Transfer},
            {"send",                        TransactionType::Transfer},
            {"receive",                     TransactionType::Transfer},
            {"adjustment",                  TransactionType::Adjustment},
            {"adjustments",                 TransactionType::Adjustment},
            {"cash_adjustment_commodities", TransactionType::Adjustment},
            {"trade_correction",            TransactionType::Correction},
            {"trade_commission_gsl",        TransactionType::Correction},
            {"settlement",                  TransactionType::Settlement},
            {"complaint_settlement",        TransactionType::Settlement}
    };

    auto it = transactionMap.find(lowerCaseTransaction);
    if (it != transactionMap.end()) {
      return it->second;
    } else {
      throw std::invalid_argument("Invalid transaction type string: "
                                  + transactionString);
    }
  }
}