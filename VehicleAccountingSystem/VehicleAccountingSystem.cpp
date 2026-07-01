#include "VehicleAccountingSystem.h"

VehicleAccountingSystem::VehicleAccountingSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_proxyModel.setSourceModel(&m_model);
    ui.tableView->setModel(&m_proxyModel);
    ui.tableView->setSortingEnabled(true);

    m_delegate = new VehicleDelegate(this);
    ui.tableView->setItemDelegate(m_delegate);

    m_proxyModel.setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel.setFilterKeyColumn(1);

    connect(ui.leSearch,
        &QLineEdit::textChanged,
        this,
        &VehicleAccountingSystem::onSearchTextChanged);

    connect(ui.cbColumn,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &VehicleAccountingSystem::onSearchColumnChanged);

    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui.tableView->setSelectionBehavior(
        QAbstractItemView::SelectRows);

    ui.tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
}

VehicleAccountingSystem::~VehicleAccountingSystem()
{}

void VehicleAccountingSystem::on_btnDelete_clicked()
{

    QMessageBox::StandardButton reply = QMessageBox::warning(
        this,
        QStringLiteral("Подтверждение"),
        QStringLiteral("Вы уверены, что удалить запись?"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply == QMessageBox::No)
        return;

    QModelIndex proxyIndex = ui.tableView->currentIndex();

    if (!proxyIndex.isValid())
        return;

    QModelIndex sourceIndex = m_proxyModel.mapToSource(proxyIndex);

    m_model.removeVehicle(sourceIndex.row());
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
    if (!m_model.vehicles().isEmpty())
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(
            this,
            QStringLiteral("Подтверждение"),
            QStringLiteral("При открытии нового файла все текущие данные будут удалены.\n"
                "Вы уверены, что хотите продолжить?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No 
        );

        if (reply == QMessageBox::No)
            return;
    }

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

    QMessageBox::information(
        this,
        QStringLiteral("Успех"),
        QStringLiteral("Загружено %1 записей.").arg(vehicles.size()));
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

void VehicleAccountingSystem::onSearchTextChanged(const QString& text)
{
    m_proxyModel.setFilterRegularExpression(text);
}

void VehicleAccountingSystem::onSearchColumnChanged(int index)
{
    m_proxyModel.setFilterKeyColumn(index);
}
