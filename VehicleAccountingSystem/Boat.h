#pragma once
#include "Vehicle.h"

class Boat : public Vehicle {
public:
    Boat(int id = 0, const QString& brand = "", const QString& model = "",
        int year = 2000, double weight = 0.0);

    QString getType() const override { return QStringLiteral("Водный транспорт"); }
};