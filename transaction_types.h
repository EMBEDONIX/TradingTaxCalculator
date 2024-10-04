//
// Created by Saeid Yazdani on 10/2/2024.
//

#pragma once

#include <string>

namespace embedonix::trading_tax_calculator {

  /**
   * @brief Enumeration representing the types of financial transactions.
   *
   * This enum class categorizes various types of financial transactions
   * that can occur. Each enumerated value signifies a specific kind of
   * transaction, aiding in the organization and processing of different
   * transactions.
   */
  enum class TransactionType {
    Unknown = 0,
    Trade,
    Swap,
    Dividend,
    Deposit,
    Transfer,
    Withdrawal,
    Adjustment,
    Correction,
    Commision,
    Settlement
  };


  /**
   * @brief Converts a TransactionType enum value to its corresponding string representation.
   * 
   * @param transaction The TransactionType enum value to convert.
   * @return A std::string containing the string representation of the transaction type.
   */
  std::string
  transactionTypeToString(TransactionType transaction);

  /**
   * @brief Converts a transaction type string to its corresponding TransactionType enum value.
   * 
   * @param transactionString The string containing the transaction type.
   * @return The corresponding TransactionType enum value.
   */
  TransactionType
  stringToTransactionType(const std::string& transactionString);


}