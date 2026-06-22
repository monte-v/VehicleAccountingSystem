#include "VehicleAccountingSystem.h"

VehicleAccountingSystem::VehicleAccountingSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.tableView->setModel(&m_model);

    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void VehicleAccountingSystem::on_mbfOpen_triggered() 
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("Открыть файл"),
        "",
        QStringLiteral("JSON (*.json)")
    );

    if (fileName.isEmpty()) 
        return;

    QVector<Vehicle> vehicles;

    if (!JsonStorage::load(fileName, vehicles))
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Не удалось открыть файл."));
        return;
    }

    m_model.setVehicles(vehicles);
}

void VehicleAccountingSystem::on_mbfSave_triggered()
{
    if (m_model.vehicles().isEmpty())
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Нет данных для сохранения."));
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("Сохранить файл"),
        "",
        QStringLiteral("JSON (*.json)")
    );

    if (fileName.isEmpty())
        return;

    if (!JsonStorage::save(fileName, m_model.vehicles()))
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Не удалось сохранить файл."));
    }
}