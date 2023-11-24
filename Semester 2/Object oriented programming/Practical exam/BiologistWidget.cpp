#include "BiologistWidget.h"



BiologistWidget::BiologistWidget(BiologistProxyModel* model, Repository& repo, Biologist biol, QWidget* parent)
:model(model),repo(repo),biol(biol),QWidget(parent){
	ui.setupUi(this);
	std::vector<Bacterium>changed_output;
	std::vector<std::string>species_studied = biol.get_species_studied();
	for (auto it : repo.get_bacteria()) {
		auto check = std::find(species_studied.begin(), species_studied.end(), it.get_species());
		if (check != species_studied.end())
			changed_output.push_back(it);
	}
	instance_data = changed_output;
	//model->setOutputData(changed_output);
	this->ui.tableView->setModel(model);
	connect_signals_and_slots();
	populate_combo_box();
}

BiologistWidget::~BiologistWidget()
{}

void BiologistWidget::populate_combo_box()
{
	std::vector<std::string>options = biol.get_species_studied();
	for (auto it : options)
		ui.comboBox->addItem(QString::fromStdString(it));
}

void BiologistWidget::connect_signals_and_slots()
{
	//QObject::connect(this->ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BiologistWidget::filterData);
	QObject::connect(this->model, &QAbstractItemModel::dataChanged, this, &BiologistWidget::updateDataInModel);
}

void BiologistWidget::updateDataInModel()
{
	std::vector<Bacterium>new_bacteria;
	std::vector<std::string>species_studied = biol.get_species_studied();
	for (auto it : repo.get_bacteria()) {
		std::string species = it.get_species();
		auto check = std::find(species_studied.begin(), species_studied.end(), species);
		if (check != species_studied.end())
			new_bacteria.push_back(it);
	}
	instance_data = new_bacteria;
	//model->setOutputData(new_bacteria);
}

void BiologistWidget::setModelData()
{
	//model->setOutputData(instance_data);
}

void BiologistWidget::updateProxyModel() {
	std::vector<std::string> speciesStudied = biol.get_species_studied();
	model->setSpeciesStudied(speciesStudied);
}
