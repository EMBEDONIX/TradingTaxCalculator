//
// Created by Saeid Yazdani on 9/30/2024.
//

#pragma once

#include <string>

namespace embedonix::trading_tax_calculator {

  class Asset {
  private:
    std::string mName;
    std::string mSymbol;
  public:
    const std::string &getName() const;
    const std::string &getSymbol() const;

    void setSymbol(const std::string &symbol);
    void setName(const std::string &name);

  public:

    Asset();
    Asset(const std::string &mName, const std::string &mSymbol);

    bool operator==(const Asset &other) const noexcept {
      return mName == other.mName && mSymbol == other.mSymbol;
    }


    // Move constructor
    Asset(Asset &&other) noexcept: mName(std::move(other.mName)), mSymbol(std::move(other.mSymbol)) {}

    // Move assignment operator
    Asset &operator=(Asset &&other) noexcept {
      if (this != &other) {
        mName = std::move(other.mName);
        mSymbol = std::move(other.mSymbol);
      }
      return *this;
    }

    // Copy constructor
    Asset(const Asset &other) : mName(other.mName), mSymbol(other.mSymbol) {}

    // Copy assignment operator
    Asset &operator=(const Asset &other) {
      if (this != &other) {
        mName = other.mName;
        mSymbol = other.mSymbol;
      }
      return *this;
    }

  };

}

// Add embedonix::trading_tax_calculator::Asset hash to namespace std
namespace std {
  template<>
  struct hash<embedonix::trading_tax_calculator::Asset> {
    std::size_t operator()(const embedonix::trading_tax_calculator::Asset &asset) const noexcept {
      return hash<std::string>()(asset.getName()) ^ (hash<std::string>()(asset.getName()) << 1);
    }
  };
}