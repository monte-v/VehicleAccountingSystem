#pragma once
#include "Vehicle.h"
#include <QMap>

class CustomVehicle : public Vehicle
{
public:
    CustomVehicle(int id = 0, const QString& brand = "", const QString& model = "",
        int year = 2000, double weight = 0.0);

    QString getType() const override {
        return m_typeName.isEmpty() ? QStringLiteral("Без типа") : m_typeName;
    }

    void setTypeName(const QString& type) { m_typeName = type; }

    QVector<int> getVisibleColumns() const override {
        return { Id, Type, Brand, Model, Year, Weight };
    }

    QString getColumnHeader(int column) const override;
    QVariant getColumnData(int column, int role = Qt::DisplayRole) const override;
    bool setColumnData(int column, const QVariant& value) override;

private:
    QString m_typeName;
};