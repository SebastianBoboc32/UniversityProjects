#pragma once
#include <qsortfilterproxymodel.h>
#include "BacteriaTableModel.h"
class BiologistProxyModel : public QSortFilterProxyModel {
public:
    BiologistProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}

    void setSpeciesStudied(const std::vector<std::string>& speciesStudied) {
        speciesStudied_ = speciesStudied;
        invalidateFilter();
    }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override {
        QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent); // Assuming species column is at index 1
        QString species = sourceModel()->data(index).toString();

        auto it = std::find(speciesStudied_.begin(), speciesStudied_.end(), species.toStdString());
        return it != speciesStudied_.end();
    }
private:
    std::vector<std::string> speciesStudied_;
};
