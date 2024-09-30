//
// Created by Saeid Yazdani on 9/30/2024.
//

#include "capital_com_loader.h"

namespace embedonix::trading_tax_calculator {

  auto generateTransactionsFromCsvFile(std::string_view file) -> std::vector<Transaction> {
    namespace sl = embedonix::simplelibs;

    auto rows = std::move(sl::parsers::csv_file_with_wrapper(
            sl::fileio::readers::read_file_string(file), ',', '"', false));

    auto transactions = std::vector<Transaction>(rows.size() / 2); // A safe allocation
    for (const auto &row: rows) {

      auto action = Transaction();
      action.setType(getTransactionTypeFromString(row[4]));

      // Assign asset by type
      switch (action.getType()) {
        case TransactionType::Transfer: // Transfer has no asset name
          action.setAsset({"transfer", "transfer"});

          break;
        case TransactionType::Deposit: // Deposit has no asset name
          action.setAsset({"deposit", "deposit"});
          break;
        default:
          action.setAsset({row[9], row[8]});
          break;
      }

      action.setValue(atof(row[2].c_str())); // Amount
      action.setDateString(row[6]);

      transactions.emplace_back(action);
    }

    return transactions;
  }

} // end NS
