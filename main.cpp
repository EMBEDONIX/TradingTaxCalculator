#include <iostream>


#include <numeric>
#include <cassert>
#include <vector>
#include <list>
#include <sstream>
#include <set>
#include <unordered_set>
#include <algorithm>


#include <QApplication>

#include "mainwindow.h"

#include "transaction.h"

namespace sl = embedonix::simplelibs;

int main(int argc, char *argv[]) {

  std::ios::sync_with_stdio(false);

  QApplication app(argc, argv);
  embedonix_tax_calculator_ui::MainWindow window;

  auto stocksFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\ITM-STOCKS\all.csv)";
  auto cryptoFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\ITM-CRYPTO\all.csv)";
  auto tradingFile = R"(H:\GoogleDrive\Accounting\Brokers\Capital\TRADING\all_20240928.csv)";

  qDebug() << "hahahhaha!";

  window.show();
  return app.exec();

}
