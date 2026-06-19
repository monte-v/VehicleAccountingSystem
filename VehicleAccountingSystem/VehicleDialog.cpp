#include "VehicleDialog.h"
#include "ui_VehicleDialog.h"

VehicleDialog::VehicleDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

VehicleDialog::~VehicleDialog()
{
}

void VehicleDialog::setVehicle(const Vehicle& vehicle)
{
    ui.leType->setText(vehicle.type);
    ui.leBrand->setText(vehicle.brand);
    ui.leModel->setText(vehicle.model);
    ui.sbYear->setValue(vehicle.year);
    ui.dsbWeight->setValue(vehicle.weight);
}

Vehicle VehicleDialog::vehicle() const
{
    Vehicle vehicle;

    vehicle.type = ui.leType->text();
    vehicle.brand = ui.leBrand->text();
    vehicle.model = ui.leModel->text();
    vehicle.year = ui.sbYear->value();
    vehicle.weight = ui.dsbWeight->value();

    return vehicle;
}

