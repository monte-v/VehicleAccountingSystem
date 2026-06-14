#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VehicleAccountingSystem.h"

class VehicleAccountingSystem : public QMainWindow
{
    Q_OBJECT

public:
    VehicleAccountingSystem(QWidget *parent = nullptr);
    ~VehicleAccountingSystem();

private:
    Ui::VehicleAccountingSystemClass ui;
};

