#include "DriveConnect.h"
#include <QtWidgets/QApplication>
#include "DriversWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo("drivers.txt", "reports.txt", "messages.txt");
    std::vector<DriversWidget*>windows;
    for (auto it : repo.get_drivers()) {
        DriversWidget* dw = new DriversWidget(repo, it);
        repo.add_observer(dw);
        windows.push_back(dw);
    }
    for (auto it : windows)
        it->show();
    return a.exec();
}
