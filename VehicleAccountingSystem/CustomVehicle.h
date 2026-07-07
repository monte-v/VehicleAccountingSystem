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

private:
    QString m_typeName;
};