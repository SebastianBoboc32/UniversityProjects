#include "DriversWidget.h"



DriversWidget::DriversWidget(Repository& repo, Driver drv, QWidget* parent)
:repo(repo),driver(drv),QWidget(parent){
	ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(drv.get_name()));
    this->ui.locationLabel->setText(QString::fromStdString(std::to_string(drv.get_current_location().first) + " " +
        std::to_string(drv.get_current_location().second)));
    this->ui.scoreLabel->setText(QString::fromStdString(std::to_string(drv.get_score())));
    populate_lists();
    connect_signals_and_slots();
}

DriversWidget::~DriversWidget()
{}

void DriversWidget::populate_lists()
{
	ui.reportsListWidget->clear();
	for (auto it : repo.get_reports())
		if (it.distanceFromDriver(driver) <= 10) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(it.to_str()));
            ui.reportsListWidget->addItem(item);
            if (it.get_valid_stat())
            {
                QFont font = item->font();
                font.setBold(true);
                item->setFont(font);
            }
		}
    ui.chatRoom->clear();
    for (auto it : repo.get_messages())
        ui.chatRoom->addItem(QString::fromStdString(it));
}

void DriversWidget::connect_signals_and_slots()
{
    QObject::connect(ui.sendButton, &QPushButton::clicked, this, &DriversWidget::send_a_message);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &DriversWidget::add_a_report);
    QObject::connect(ui.reportsListWidget, &QListWidget::currentItemChanged, this, &DriversWidget::validate_a_report);
}

void DriversWidget::update()
{
    populate_lists();
}

void DriversWidget::send_a_message()
{
    std::string message = ui.messageLineEdit->text().toStdString();
    repo.add_a_message(driver.get_name() +":"+message);
}

void DriversWidget::add_a_report()
{
    std::string line1 = ui.descriptionLineEdit->text().toStdString();
    if (line1.empty()) {
        QMessageBox::critical(nullptr, "error", "Name must not be empty!");
        return;
    }
    else {
        std::string line2 = ui.coordsLineEdit->text().toStdString();
        std::istringstream get_coords(line2);
        double X, Y;
        get_coords >> X >> Y;
        RoadReport rept = RoadReport(line1, driver.get_name(), X, Y, false);
        if(rept.distanceFromDriver(driver) < 20)
        repo.add_a_report(rept);
        else {
            QMessageBox::critical(nullptr, "error", "Distance must be within 20 units!");
            return;
        }
    }
}

void DriversWidget::validate_a_report(QListWidgetItem* item)
{
    int vrfindx = ui.reportsListWidget->row(item);
    if (vrfindx >= 0 && vrfindx < repo.get_reports().size()) {
        std::string selected_report = item->text().toStdString();
        int index = -1;
        std::vector<RoadReport>repts = repo.get_reports();
        for (int i = 0; i < repts.size() && index == -1; ++i)
            if (repts[i].to_str() == selected_report)
                index = i;
        if (repts[index].get_valid_stat() == false) {
            repo.validate_a_report(index);
            std::vector<Driver>drvs = repo.get_drivers();
            int index_1 = -1;
            for (int i = 0; i < drvs.size() && index_1 == -1; ++i)
                if (drvs[i].get_name() == driver.get_name()) {
                    index_1 = i;
                }
            drvs[index_1].raise_bonus_points();
            if (drvs[index_1].get_bonus_points() % 2 == 0) {
                repo.raise_drivers_score(index_1);
                this->ui.scoreLabel->setText(QString::fromStdString(std::to_string(driver.get_score())));
            }
        }
    }
}
