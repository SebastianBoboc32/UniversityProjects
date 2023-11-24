#pragma once

#include <QWidget>
#include "ui_BiologistWidget.h"
#include "BacteriaTableModel.h"
#include <qsortfilterproxymodel.h>
#include "biologistproxymodel.h"

class BiologistWidget : public QWidget
{
	Q_OBJECT

public:
	BiologistWidget(BiologistProxyModel* model,Repository& repo,Biologist biol,QWidget *parent = nullptr);
	~BiologistWidget();
	void populate_combo_box();
	void connect_signals_and_slots();
	//void filterData(int index);
	void updateDataInModel();
	void setModelData();
	void updateProxyModel();
private:
	Ui::BiologistWidgetClass ui;
	BiologistProxyModel* model;
	std::vector<Bacterium>instance_data;
	Repository& repo;
	Biologist biol;
};
