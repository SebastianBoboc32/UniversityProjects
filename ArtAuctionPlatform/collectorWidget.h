#pragma once

#include <QWidget>
#include "ui_collectorWidget.h"
#include "service.h"

class collectorWidget : public QWidget
{
	Q_OBJECT

public:
	collectorWidget(Service&,User&,QWidget *parent = nullptr);
	~collectorWidget();
	void populate_list();
	void connect_signals_and_slots();
	void populate_item_offers(QListWidgetItem* item);
	void populate_combo_box();
	void comboIndexChanged(int index);
	void make_a_bid();
private:
	Ui::collectorWidgetClass ui;
	Service& serv;
	User user;
};
