#include "VehicleModel.h"

VehicleModel::VehicleModel(QObject* parent)
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
        return QVariant();

    if (role != Qt::DisplayRole &&
        role != Qt::EditRole)
    {
        return QVariant();
    }

    const Vehicle& vehicle = m_vehicles[index.row()];

    switch (index.column())
    {
    case 0:
        return vehicle.id;

    case 1:
        return vehicle.type;

    case 2:
        return vehicle.brand;

    case 3:
        return vehicle.model;

    case 4:
        return vehicle.year;

    case 5:
        return vehicle.weight;

    default:
        return QVariant();
    }
}

QVariant VehicleModel::headerData(int section,
    Qt::Orientation orientation,
    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "ID";

        case 1:
            return "Тип";

        case 2:
            return "Марка";

        case 3:
            return "Модель";

        case 4:
            return "Год";

        case 5:
            return "Вес";

        default:
            return QVariant();
        }
    }

    return QAbstractTableModel::headerData(
        section,
        orientation,
        role);
}

Qt::ItemFlags VehicleModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags =
        Qt::ItemIsEnabled |
        Qt::ItemIsSelectable;

    if (index.column() != 0)
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

    Vehicle& vehicle = m_vehicles[index.row()];

    switch (index.column())
    {
    case 1:
        vehicle.type = value.toString();
        break;

    case 2:
        vehicle.brand = value.toString();
        break;

    case 3:
        vehicle.model = value.toString();
        break;

    case 4:
        vehicle.year = value.toInt();
        break;

    case 5:
        vehicle.weight = value.toDouble();
        break;

    default:
        return false;
    }

    emit dataChanged(index, index);

    return true;
}

void VehicleModel::addVehicle(const Vehicle& vehicle)
{
    beginInsertRows(
        QModelIndex(),
        m_vehicles.size(),
        m_vehicles.size());

    Vehicle newVehicle = vehicle;

    newVehicle.id = m_nextId++;

    m_vehicles.append(newVehicle);

    endInsertRows();
}

void VehicleModel::removeVehicle(int row)
{
    if (row < 0 || row >= m_vehicles.size())
        return;

    beginRemoveRows(
        QModelIndex(),
        row,
        row);

    m_vehicles.removeAt(row);

    endRemoveRows();
}

QVector<Vehicle> VehicleModel::vehicles() const
{
    return m_vehicles;
}

void VehicleModel::setVehicles(
    const QVector<Vehicle>& vehicles)
{
    beginResetModel();

    m_vehicles = vehicles;

    m_nextId = 1;

    for (const Vehicle& vehicle : m_vehicles)
    {
        if (vehicle.id >= m_nextId)
        {
            m_nextId = vehicle.id + 1;
        }
    }

    endResetModel();
}


