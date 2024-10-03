//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <unordered_set>

#include <embedonix/simplelibs/fileio/filereader.h>
#include <embedonix/simplelibs/stringtools/trim.h>
#include <embedonix/simplelibs/stringtools/print.h>
#include <embedonix/simplelibs/parsers/csvparser.h>
#include <embedonix/simplelibs/utilities/benchmark.h>

#include "transaction.h"

namespace embedonix::trading_tax_calculator::capitalcom {

  std::vector<Transaction>
  generateTransactionsFromCsvFile(std::string file);

  std::unordered_set<Asset>
  getUniqueAssetsInTransactions(const std::vector<Transaction>& transactions);

  std::unordered_set<TransactionType>
  getTypesInTransactions(const std::vector<Transaction>& transactions);

  std::unordered_set<TransactionType>
  getTransactionTypesForAsset(const std::vector<Transaction> transactions, const Asset& asset);


} // end NS