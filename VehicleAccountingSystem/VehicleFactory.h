#pragma once
#include <memory>
#include <QString>

#include "Vehicle.h"

class VehicleFactory
{
public:
    static std::shared_ptr<Vehicle> create(
        const QString& type,
        int id = 0,
        const QString& brand = "",
        const QString& model = "",
        int year = 2000,
        double weight = 0.0);
};