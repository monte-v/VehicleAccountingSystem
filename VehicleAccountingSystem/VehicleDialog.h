#pragma once

#include <QDialog>

#include "Vehicle.h"
#include "ui_VehicleDialog.h"

class VehicleDialog : public QDialog
{
    Q_OBJECT

public:
    VehicleDialog(QWidget* parent = nullptr);
    ~VehicleDialog();

    void setVehicle(const Vehicle& vehicle);
    Vehicle vehicle() const;

private:
    Ui::VehicleDialog ui;
};