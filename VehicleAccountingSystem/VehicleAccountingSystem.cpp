#include "VehicleAccountingSystem.h"

VehicleAccountingSystem::VehicleAccountingSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.tableView->setModel(&m_model);

    ui.tableView->horizontalHeader()->setStretchLastSection(true);

    ui.tableView->setSelectionBehavior(
        QAbstractItemView::SelectRows);

    ui.tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
}

VehicleAccountingSystem::~VehicleAccountingSystem()
{}

void VehicleAccountingSystem::on_btnTest_clicked()
{
    Vehicle v1;
    v1.type = QStringLiteral("Автомобиль");
    v1.brand = "Toyota";
    v1.model = "Camry";
    v1.year = 2020;
    v1.weight = 1500;

    m_model.addVehicle(v1);

    Vehicle v2;
    v2.type = QStringLiteral("Самолет");
    v2.brand = "Boeing";
    v2.model = "747";
    v2.year = 2010;
    v2.weight = 183500;

    m_model.addVehicle(v2);
}

void VehicleAccountingSystem::on_btnDelete_clicked()
{
    QModelIndex index = ui.tableView->currentIndex();

    if (!index.isValid())
        return;

    m_model.removeVehicle(index.row());
}

void VehicleAccountingSystem::on_btnAdd_clicked()
{
    VehicleDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        m_model.addVehicle(dialog.vehicle());
    }
}
