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
    ui.cbType->setCurrentText(vehicle.getType());
    ui.leBrand->setText(vehicle.getBrand());
    ui.leModel->setText(vehicle.getModel());
    ui.sbYear->setValue(vehicle.getYear());
    ui.dsbWeight->setValue(vehicle.getWeight());
}

std::shared_ptr<Vehicle> VehicleDialog::vehicle() const
{
    QString type = ui.cbType->currentText();
    int typeIndex = ui.cbType->currentIndex();

    std::shared_ptr<Vehicle> result;


    switch (typeIndex)
    {
    case 0: // Автомобиль
        return std::make_shared<Car>(
            0,
            ui.leBrand->text(),
            ui.leModel->text(),
            ui.sbYear->value(),
            ui.dsbWeight->value());
    case 1: // Катер
        return std::make_shared<Boat>(
            0,
            ui.leBrand->text(),
            ui.leModel->text(),
            ui.sbYear->value(),
            ui.dsbWeight->value());
    }
    return result;
}

void VehicleDialog::accept()
{
    if (ui.cbType->currentText().isEmpty() || 
        ui.leBrand->text().trimmed().isEmpty() ||
        ui.leModel->text().trimmed().isEmpty() ||
        ui.dsbWeight->value() <= 0)
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Заполните все поля"));
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