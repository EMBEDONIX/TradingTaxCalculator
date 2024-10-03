//
// Created by Saeid Yazdani on 10/2/2024.
//

#pragma once

#include <QAbstractTableModel>
#include <QStringList>

namespace embedonix::trading_tax_calculator::qt {

  class AssetResultTableModelCapitalCom : public QAbstractTableModel {

  Q_OBJECT

  public:

    AssetResultTableModelCapitalCom(QObject* parent = nullptr);

    AssetResultTableModelCapitalCom(QVector<QStringList> data, QObject* parent = nullptr);

    int
    rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int
    columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant
    data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant
    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  public slots:

    void
    loadFile(const QString& fileName);

  private:
    QVector<QStringList> mResults;

  };

} // qt
