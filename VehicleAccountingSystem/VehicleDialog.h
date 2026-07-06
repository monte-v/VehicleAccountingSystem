#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QDate>

#include "Vehicle.h"
#include "Car.h"
#include "Boat.h"
#include "ui_VehicleDialog.h"


class VehicleDialog : public QDialog
{
    Q_OBJECT

public:
    VehicleDialog(QWidget* parent = nullptr);
    ~VehicleDialog();

    void setVehicle(const Vehicle& vehicle);
    std::shared_ptr<Vehicle> vehicle() const;

private:
    Ui::VehicleDialog ui;

protected:
    void accept() override;
};