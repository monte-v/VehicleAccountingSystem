#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VehicleAccountingSystem.h"
#include "VehicleModel.h"
#include "VehicleDialog.h"

class VehicleAccountingSystem : public QMainWindow
{
    Q_OBJECT

public:
    VehicleAccountingSystem(QWidget *parent = nullptr);
    ~VehicleAccountingSystem();

private:
    Ui::VehicleAccountingSystemClass ui;
    VehicleModel m_model;

private slots:
    void on_btnTest_clicked();
    void on_btnDelete_clicked();
    void on_btnAdd_clicked();
};

