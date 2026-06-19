#pragma once
#include <QString>
#include <QVector>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "Vehicle.h"

class JsonStorage
{ 
public:
    static bool save(const QString& fileName,
        const QVector<Vehicle>& vehicles);

    static bool load(const QString& fileName,
        QVector<Vehicle>& vehicles);
};

