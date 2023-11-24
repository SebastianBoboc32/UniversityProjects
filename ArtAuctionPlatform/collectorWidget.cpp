#include "collectorWidget.h"
#include <qmessagebox.h>

collectorWidget::collectorWidget(Service& servv,User&usr,QWidget *parent)
	:serv(servv),user(usr), QWidget(parent)
{	
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(user.get_name()));
	populate_list();
	populate_combo_box();
	connect_signals_and_slots();
}

collectorWidget::~collectorWidget()
{}

void collectorWidget::populate_list()
{
	this->ui.entities->clear();
	std::vector<Item> output = serv.get_all_items_sorted();
	for (auto it : output)
		this->ui.entities->addItem(QString::fromStdString(it.to_str()));
}

void collectorWidget::connect_signals_and_slots()
{
	QObject::connect(ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &collectorWidget::comboIndexChanged);
	QObject::connect(ui.entities, &QListWidget::itemClicked, this, &collectorWidget::populate_item_offers);
	QObject::connect(ui.pushButton, &QPushButton::clicked, this, &collectorWidget::make_a_bid);
}

void collectorWidget::populate_item_offers(QListWidgetItem* item)
{
	int index = ui.entities->row(item);
	std::vector<Item>input = serv.get_all_items_sorted();
	if (index > -1 && index < input.size()) {
		this->ui.offersOfItem->clear();
		std::vector<std::tuple<int, std::string, int> > offers = serv.get_all_offers(index);
		for (auto it : offers) {
			std::string output = std::to_string(std::get<0>(it)) + " " + std::get<1>(it) + " " + std::to_string(std::get<2>(it));
			this->ui.offersOfItem->addItem(QString::fromStdString(output));
		}
	}
}

void collectorWidget::populate_combo_box()
{
	std::vector<std::string> categories = serv.all_categories();
	for (auto it : categories)
		this->ui.comboBox->addItem(QString::fromStdString(it));
}

void collectorWidget::comboIndexChanged(int index)
{
	if (index > -1 && index < serv.get_all_items_sorted().size()) {
		QString selected_cat = this->ui.comboBox->itemText(index);
		std::string selected_category = selected_cat.toStdString();
		if (selected_category != "") {
			this->ui.entities->clear();
			std::vector<Item>output = serv.get_all_items_sorted();
			for (auto it : output)
				if (it.get_category() == selected_category)
					this->ui.entities->addItem(QString::fromStdString(it.to_str()));
		}
		else populate_list();
	}
}

void collectorWidget::make_a_bid()
{
	QListWidgetItem* selectedItem = ui.entities->currentItem();
	if (selectedItem) {
		int index = ui.entities->row(selectedItem);
		int amount_of_money = ui.lineEdit->text().toInt();
		if (amount_of_money <= 0)
			QMessageBox::critical(nullptr, "error", "The sum must be greater than 0");
		else {
			if (index > -1 && index < serv.get_all_items_sorted().size()) {
				serv.bid_for_item(index, amount_of_money);
				this->ui.entities->clear();
				std::vector<Item> output = serv.get_all_items_sorted();
				for (auto it : output)
					this->ui.entities->addItem(QString::fromStdString(it.to_str()));
			}
		}
	}
}