#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DriveConnect.h"

class DriveConnect : public QMainWindow
{
    Q_OBJECT

public:
    DriveConnect(QWidget *parent = nullptr);
    ~DriveConnect();

private:
    Ui::DriveConnectClass ui;
};
