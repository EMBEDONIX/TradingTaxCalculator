cmake_minimum_required(VERSION 3.25)
project(TradingTaxCalculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:/DevTools/qt/6.7.1/mingw_64")

find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(TradingTaxCalculator main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        asset.cpp
        asset.h
        transaction.cpp
        transaction.h
        capital_com_loader.h
        capital_com_loader.cpp)

target_include_directories(TradingTaxCalculator
        PRIVATE "F:/embedonix/simplelibs-dbg/include"
        )

target_link_directories(TradingTaxCalculator
        PRIVATE "F:/embedonix/simplelibs-dbg"
        )

target_link_libraries(TradingTaxCalculator
        PRIVATE embedonix_simplelibs_fileio
        PRIVATE embedonix_simplelibs_parsers
        PRIVATE embedonix_simplelibs_stringtools
        PUBLIC Qt6::Widgets
        )
