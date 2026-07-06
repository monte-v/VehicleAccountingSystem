#pragma once
#include <QString>
#include <QVector>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

#include "Vehicle.h"
#include "CustomVehicle.h"
#include "Car.h"

class JsonStorage
{ 
public:
    static bool save(const QString& fileName,
        const QVector<std::shared_ptr<Vehicle>>& vehicles);

    static bool load(const QString& fileName,
        QVector<std::shared_ptr<Vehicle>>& vehicles);
};

