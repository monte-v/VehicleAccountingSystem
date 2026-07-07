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

    connect(ui.leSearch,
        &QLineEdit::textChanged,
        this,
        &VehicleAccountingSystem::onSearchTextChanged);

    connect(ui.listWidget,
        &QListWidget::currentItemChanged,
        this,
        &VehicleAccountingSystem::onTypeFilterChanged);

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

    updateTypeFilterList();
}

void VehicleAccountingSystem::on_btnAdd_clicked()
{
    VehicleDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        auto vehicle = dialog.vehicle();

        if (!vehicle)   
            return;

        m_model.addVehicle(vehicle);

        updateTypeFilterList();
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

    QVector<std::shared_ptr<Vehicle>> vehicles;

    if (!JsonStorage::load(fileName, vehicles))
    {
        QMessageBox::warning(
            this,
            QStringLiteral("Ошибка"),
            QStringLiteral("Не удалось открыть файл."));
        return;
    }

    m_model.setVehicles(vehicles);

    updateTypeFilterList();

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
    m_proxyModel.setSearchText(text);
}

void VehicleAccountingSystem::onTypeFilterChanged(QListWidgetItem* current,
    QListWidgetItem* previous)
{
    Q_UNUSED(previous);

    if (!current) {
        return;
    }

    QString type = current->text();

    if (type == QStringLiteral("Все типы"))
        m_proxyModel.setTypeFilter(QStringLiteral(""));
    else
        m_proxyModel.setTypeFilter(type);
}

void VehicleAccountingSystem::updateTypeFilterList()
{
    ui.listWidget->blockSignals(true);

    QStringList types;
    for (const auto& vehicle : m_model.vehicles()) {
        QString type = vehicle->getType();
        if (!type.isEmpty() && !types.contains(type)) {
            types.append(type);
        }
    }

    types.sort();

    ui.listWidget->clear();
    ui.listWidget->addItem(QStringLiteral("Все типы"));
    ui.listWidget->addItems(types);

    ui.listWidget->blockSignals(false);

    ui.listWidget->setCurrentRow(0);
}