#pragma once
#include <qabstractitemmodel.h>
#include <algorithm>
#include "repository.h"

class BacteriaTableModel :
    public QAbstractTableModel
{
private:
    Repository& repo;
    //Biologist biol;
    mutable std::vector<Bacterium>output_data;
public:
    BacteriaTableModel(Repository& rep) :repo(rep) {
    }
    BacteriaTableModel(const BacteriaTableModel& other) : output_data(other.output_data),repo(other.repo){};
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    //void setOutputData(const std::vector<Bacterium>& new_output);
    //void updateOutputData();
    Qt::ItemFlags flags(const QModelIndex& index) const;
};

