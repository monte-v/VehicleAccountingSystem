#include "Boat.h"

Boat::Boat(int id, const QString& brand, const QString& model,
    int year, double weight)
    : Vehicle(id, brand, model, year, weight)
{
}

QString Boat::getColumnHeader(int column) const {
    return Vehicle::getColumnHeader(column);
}

QVariant Boat::getColumnData(int column, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();
    
    return Vehicle::getColumnData(column, role);
}

bool Boat::setColumnData(int column, const QVariant& value) {
    return Vehicle::setColumnData(column, value);
}