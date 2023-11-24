#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ArtAuctionPlatform.h"

class ArtAuctionPlatform : public QMainWindow
{
    Q_OBJECT

public:
    ArtAuctionPlatform(QWidget *parent = nullptr);
    ~ArtAuctionPlatform();

private:
    Ui::ArtAuctionPlatformClass ui;
};
