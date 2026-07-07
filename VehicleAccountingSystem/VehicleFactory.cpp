#include "VehicleFactory.h"

#include "Car.h"
#include "Boat.h"
#include "CustomVehicle.h"

std::shared_ptr<Vehicle> VehicleFactory::create(
    const QString& type,
    int id,
    const QString& brand,
    const QString& model,
    int year,
    double weight)
{
    if (type == QStringLiteral("Автомобиль"))
    {
        return std::make_shared<Car>(
            id, brand, model, year, weight);
        
    }

    if (type == QStringLiteral("Водный транспорт"))
    {
        return std::make_shared<Boat>(
            id, brand, model, year, weight);
    }

    auto vehicle = std::make_shared<CustomVehicle>(
        id, brand, model, year, weight);

    vehicle->setTypeName(type);

    return vehicle;
}