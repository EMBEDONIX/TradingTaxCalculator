//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <embedonix/simplelibs/fileio/filereader.h>
#include <embedonix/simplelibs/stringtools/trim.h>
#include <embedonix/simplelibs/stringtools/print.h>
#include <embedonix/simplelibs/parsers/csvparser.h>
#include <embedonix/simplelibs/utilities/benchmark.h>

#include "transaction.h"

namespace embedonix::trading_tax_calculator {

  auto generateTransactionsFromCsvFile(std::string_view file) -> std::vector<Transaction>;

} // end NS