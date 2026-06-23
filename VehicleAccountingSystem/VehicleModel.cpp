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
    case Vehicle::Id:
        return vehicle.id;

    case Vehicle::Type:
        return vehicle.type;

    case Vehicle::Brand:
        return vehicle.brand;

    case Vehicle::Model:
        return vehicle.model;

    case Vehicle::Year:
        return vehicle.year;

    case Vehicle::Weight:
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
        case Vehicle::Id:
            return "ID";

        case Vehicle::Type:
            return QStringLiteral("Тип");

        case Vehicle::Brand:
            return QStringLiteral("Марка");

        case Vehicle::Model:
            return QStringLiteral("Модель");

        case Vehicle::Year:
            return QStringLiteral("Год");

        case Vehicle::Weight:
            return QStringLiteral("Вес, кг");

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

    if (index.column() != Vehicle::Id)
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
    m_lastError.clear();

    switch (index.column())
    {
    case Vehicle::Type:
    {
        QString type = value.toString().trimmed();

        if (type.isEmpty())
        {
            m_lastError = QStringLiteral("Поле \"Тип\" не может быть пустым.");
            return false;
        }

        vehicle.type = type; 
        break;
    }
    case Vehicle::Brand:
    {
        QString brand = value.toString().trimmed();

        if (brand.isEmpty())
        {
            m_lastError = QStringLiteral("Поле \"Марка\" не может быть пустым.");
            return false;
        }

        vehicle.brand = brand;
        break;
    }
    case Vehicle::Model:
    {
        QString model = value.toString().trimmed();

        if (model.isEmpty())
        {
            m_lastError = QStringLiteral("Поле \"Модель\" не может быть пустым.");
            return false;
        }

        vehicle.model = model;
        break;
    }
    case Vehicle::Year:
    {
        int year = value.toInt();

        if (year < 1900 || year > QDate::currentDate().year())
        {
            m_lastError = QStringLiteral("Некорректный год выпуска.");
            return false;
        }
        vehicle.year = year;
        break;
    }
    case Vehicle::Weight:
    {
        double weight = value.toDouble();

        if (weight <= 0)
        {
            m_lastError = QStringLiteral("Некорректный вес транспортного средства.");
            return false;
        }

        vehicle.weight = weight;
        break;
    }
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

QString VehicleModel::lastError() const
{
    return m_lastError;
}


