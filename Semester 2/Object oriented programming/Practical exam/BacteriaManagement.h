#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BacteriaManagement.h"

class BacteriaManagement : public QMainWindow
{
    Q_OBJECT

public:
    BacteriaManagement(QWidget *parent = nullptr);
    ~BacteriaManagement();

private:
    Ui::BacteriaManagementClass ui;
};
