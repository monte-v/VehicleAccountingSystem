#include "Vehicle.h"

Vehicle::Vehicle(int id, const QString& brand, const QString& model,
    int year, double weight)
    : m_id(id)
    , m_brand(brand)
    , m_model(model)
    , m_year(year)
    , m_weight(weight)
{
}

QString Vehicle::getColumnHeader(int column) const {
    switch (column) {
    case Id:       return QStringLiteral("ID");
    case Type:     return QStringLiteral("Тип");
    case Brand:    return QStringLiteral("Марка");
    case Model:    return QStringLiteral("Модель");
    case Year:     return QStringLiteral("Год");
    case Weight:   return QStringLiteral("Вес, кг");
    default:           return QStringLiteral("");
    }
}

QVariant Vehicle::getColumnData(int column, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();

    switch (column) {
    case Id:       return m_id;
    case Type:     return getType();
    case Brand:    return m_brand;
    case Model:    return m_model;
    case Year:     return m_year;
    case Weight:   return m_weight;
    default:           return QVariant();
    }
}

bool Vehicle::setColumnData(int column, const QVariant& value) {
    switch (column) {
    case Brand:
        m_brand = value.toString();
        return true;
    case Model:
        m_model = value.toString();
        return true;
    case Year:
        m_year = value.toInt();
        return true;
    case Weight:
        m_weight = value.toDouble();
        return true;
    default:
        return false;
    }
}