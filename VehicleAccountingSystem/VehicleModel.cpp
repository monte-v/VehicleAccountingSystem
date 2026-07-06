#include "VehicleModel.h"

VehicleModel::VehicleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int VehicleModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return m_vehicles.size();
}

int VehicleModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return Vehicle::FIELD_COUNT;
}

QVariant VehicleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() < 0 || index.row() >= m_vehicles.size())
        return {};

    const auto& vehicle = m_vehicles[index.row()];

    return vehicle->getColumnData(index.column(), role);
}

QVariant VehicleModel::headerData(int section,
    Qt::Orientation orientation,
    int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case Vehicle::Id:      return QStringLiteral("ID");
        case Vehicle::Type:    return QStringLiteral("Тип");
        case Vehicle::Brand:   return QStringLiteral("Марка");
        case Vehicle::Model:   return QStringLiteral("Модель");
        case Vehicle::Year:    return QStringLiteral("Год");
        case Vehicle::Weight:  return QStringLiteral("Вес, кг");
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags VehicleModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    if (index.column() != Vehicle::Id &&
        index.column() != Vehicle::Type)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool VehicleModel::setData(const QModelIndex& index,
    const QVariant& value,
    int role)
{
    if (!index.isValid())
        return false;

    if (role != Qt::EditRole)
        return false;

    if (index.row() < 0 || index.row() >= m_vehicles.size())
        return false;

    const auto& vehicle = m_vehicles[index.row()];

    bool ok = vehicle->setColumnData(index.column(), value);

    if (ok)
        emit dataChanged(index, index);

    return ok;
}

void VehicleModel::addVehicle(std::shared_ptr<Vehicle> vehicle)
{
    beginInsertRows({}, rowCount(), rowCount());

    vehicle->setId(m_nextId++);

    m_vehicles.append(vehicle);

    endInsertRows();
}

void VehicleModel::removeVehicle(int row)
{
    if (row < 0 || row >= m_vehicles.size())
        return;

    beginRemoveRows({}, row, row);

    m_vehicles.removeAt(row);

    endRemoveRows();
}

QVector<std::shared_ptr<Vehicle>> VehicleModel::vehicles() const
{
    return m_vehicles;
}

void VehicleModel::setVehicles(const QVector<std::shared_ptr<Vehicle>>& vehicles)
{
    beginResetModel();

    m_vehicles = vehicles;

    m_nextId = 1;

    for (const auto& vehicle : m_vehicles)
    {
        if (vehicle->getId() >= m_nextId)
            m_nextId = vehicle->getId() + 1;
    }

    endResetModel();
}

QString VehicleModel::lastError() const
{
    return m_lastError;
}
