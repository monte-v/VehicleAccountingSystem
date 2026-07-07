#include "CustomVehicle.h"

CustomVehicle::CustomVehicle(int id, const QString& brand, const QString& model,
    int year, double weight)
    : Vehicle(id, brand, model, year, weight)
{
}
