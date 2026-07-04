#include "VehicleDialog.h"
#include "ui_VehicleDialog.h"

VehicleDialog::VehicleDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
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

void VehicleDialog::accept()
{
    if (ui.leType->text().trimmed().isEmpty() ||
        ui.leBrand->text().trimmed().isEmpty() ||
        ui.leModel->text().trimmed().isEmpty() ||
        ui.dsbWeight->value() <= 0)
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Заполните все поля.\nВес должен быть больше нуля."));
        return;
    }
    if (ui.sbYear->value() > QDate::currentDate().year())
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Год не может быть больше текущего"));
        return;
    }

    QDialog::accept();
}