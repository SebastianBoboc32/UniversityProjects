#pragma once

#include <QWidget>
#include "ui_DriversWidget.h"
#include "repository.h"
#include <qmessagebox.h>
#include <qfont.h>

class DriversWidget : public QWidget,public Observer
{
	Q_OBJECT

public:
	DriversWidget(Repository& repo,Driver drv,QWidget *parent = nullptr);
	~DriversWidget();
	void populate_lists();
	void connect_signals_and_slots();
	void update()override;
	void send_a_message();
	void add_a_report();
	void validate_a_report(QListWidgetItem* item);

private:
	Ui::DriversWidgetClass ui;
	Repository& repo;
	Driver driver;
};
