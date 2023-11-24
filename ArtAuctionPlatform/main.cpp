#include "ArtAuctionPlatform.h"
#include <QtWidgets/QApplication>
#include "collectorWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArtAuctionPlatform w;
    std::vector<collectorWidget*>windows;
    Repository repo{ "users.txt","items.txt" };
    //ert(repo.get_all_items().size() == 0);
    for (auto it : repo.get_all_users()) {
        Service serv{ it,repo };
        collectorWidget* temp = new collectorWidget(serv, it);
        windows.push_back(temp);
    }
    for (auto it : windows)
        it->show();
    w.show();
    return a.exec();
}
