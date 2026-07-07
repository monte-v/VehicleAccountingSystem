#include "VehicleDialog.h"
#include "ui_VehicleDialog.h"

VehicleDialog::VehicleDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    connect(ui.cbType, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &VehicleDialog::onTypeChanged);

    ui.leCustomType->setVisible(false);
    ui.lCustomType->setVisible(false);
}

VehicleDialog::~VehicleDialog()
{
}

void VehicleDialog::setVehicle(const Vehicle& vehicle)
{
    int index = ui.cbType->findText(vehicle.getType());

    ui.cbType->setCurrentIndex(index);

    ui.leBrand->setText(vehicle.getBrand());
    ui.leModel->setText(vehicle.getModel());
    ui.sbYear->setValue(vehicle.getYear());
    ui.dsbWeight->setValue(vehicle.getWeight());
}

std::shared_ptr<Vehicle> VehicleDialog::vehicle() const
{
    QString type;

    if (ui.cbType->currentIndex() == 0) {
        type = ui.leCustomType->text().trimmed();
        if (type.isEmpty()) {
            type = QStringLiteral("Другое");
        }
    }
    else {
        type = ui.cbType->currentText();
    }

    return VehicleFactory::create(
        type,
        0,
        ui.leBrand->text(),
        ui.leModel->text(),
        ui.sbYear->value(),
        ui.dsbWeight->value()
    );
}

void VehicleDialog::onTypeChanged(int index)
{
    bool isCustom = (ui.cbType->currentIndex() == 0);
    ui.leCustomType->setVisible(isCustom);
    ui.lCustomType->setVisible(isCustom);

    if (isCustom) {
        ui.leCustomType->setFocus();
    }
}

void VehicleDialog::accept()
{
    if (ui.cbType->currentIndex() <= 0 &&
        ui.leCustomType->text().trimmed().isEmpty()) {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Введите название типа или выберите существующий"));
        return;
    }

    if (ui.leBrand->text().trimmed().isEmpty() ||
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

