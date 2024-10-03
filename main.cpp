#include <iostream>


#include <unordered_set>

#include <QApplication>

#include "mainwindow.h"
#include "capital_com_loader.h"

namespace sl = embedonix::simplelibs;
namespace tc = embedonix::trading_tax_calculator;
namespace tcq = embedonix::trading_tax_calculator::qt;

int main(int argc, char* argv[]) {

  std::ios::sync_with_stdio(false);

  QApplication app(argc, argv);
  embedonix::trading_tax_calculator::qt::MainWindow window;

  auto stocksFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\ITM-STOCKS\all.csv)";
  auto cryptoFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\ITM-CRYPTO\all.csv)";
  std::string tradingFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\TRADING\all_20240928.csv)";



  window.show();

  return app.exec();

}
