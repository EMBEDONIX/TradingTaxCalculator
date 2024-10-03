//
// Created by Saeid Yazdani on 9/30/2024.
//

#include <algorithm>


#include "macros.h"
#include "capital_com_loader.h"


namespace embedonix::trading_tax_calculator::capitalcom {

  auto
  generateTransactionsFromCsvFile(std::string file) -> std::vector<Transaction> {
    __BENCHMARK_TIMER_START(timer)

    namespace sl = embedonix::simplelibs;

    auto rows = std::move(sl::parsers::csv_file_with_wrapper(
            sl::fileio::readers::read_file_string(file), ',', '"', true));

    auto transactions = std::vector<Transaction>();
    for (const auto& row: rows) {

      auto action = Transaction();
      Asset asset;
      action.setType(stringToTransactionType(row[4]));

      // Assign asset by type
      switch (action.getType()) {
        case TransactionType::Transfer: // Transfer has no asset name
          asset = {"transfer", "transfer"};
          break;
        case TransactionType::Deposit: // Deposit has no asset name
          asset = {"deposit", "deposit"};
          break;
        default:
          asset = {row[9], row[8]};
          break;
      }

      asset.setAssetType(stringToAssetType(row[11]));
      action.setAsset(asset);
      action.setValue(atof(row[2].c_str())); // Amount
      action.setDateString(row[6]);
      action.setCurrency(row[3]);

      transactions.emplace_back(action);
    }

    __BENCHMARK_TIMER_STOP(timer)
    return transactions;
  }

  std::unordered_set<Asset>
  getUniqueAssetsInTransactions(const std::vector<Transaction>& transactions) {
    __BENCHMARK_TIMER_START(timer);
    std::unordered_set<Asset> assets;
#ifdef __DEBUG__
    int numDuplicates = 0;
    int numUniqueAssts = 0;

#endif
    for (const auto& tr: transactions) {

#ifdef __DEBUG__
      assets.insert(tr.getAsset()).second ? numUniqueAssts++ : numDuplicates++;
#else
      assets.insert(tr.getAsset());
#endif
    }
#ifdef __DEBUG__
    auto debugLine = std::format("Found {} unique and {} duplicate assets",
                                 numUniqueAssts, numDuplicates);
    puts(debugLine.c_str());
#endif
    __BENCHMARK_TIMER_STOP(timer);
    return assets;
  }

  std::unordered_set<TransactionType>
  getTransactionTypesForAsset(const std::vector<Transaction> transactions, const Asset& asset) {
    __BENCHMARK_TIMER_START(timer);

    auto set = std::unordered_set<TransactionType>();

    for (const auto& action: transactions) {
      if (action.getAsset() == asset) {
        set.insert(action.getType());
      }
    }

    __BENCHMARK_TIMER_STOP(timer);
    return set;
  }

  std::unordered_set<TransactionType> getTypesInTransactions(const std::vector<Transaction>& transactions) {
    __BENCHMARK_TIMER_START(timer)

    auto involvedTypes = std::unordered_set<TransactionType>();
    for (const auto& tr: transactions) {
      involvedTypes.insert(tr.getType());
    }

    return involvedTypes;
    __BENCHMARK_TIMER_STOP(timer)
  }


} // end NS
