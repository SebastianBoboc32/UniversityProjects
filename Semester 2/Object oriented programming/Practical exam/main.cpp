#include "BacteriaManagement.h"
#include <QtWidgets/QApplication>
#include "BiologistWidget.h"
#include "biologistproxymodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo("biologists.txt","bacteria.txt");
    //BacteriaTableModel* mdl = new BacteriaTableModel(repo);
   // std::vector<BacteriaTableModel*>models;
    std::vector<BiologistWidget*> windows;
    BacteriaTableModel* mdl = new BacteriaTableModel(repo);
    for (auto it : repo.get_biologists()) {
        BiologistProxyModel* proxyModel = new BiologistProxyModel();
        proxyModel->setSourceModel(mdl);
        BiologistWidget* bwd = new BiologistWidget(proxyModel, repo, it);
        bwd->setModelData();
        windows.push_back(bwd);
    }
    for (auto it : windows)
        it->show();
    return a.exec();
}
