#pragma once
#include "Vehicle.h"

class Boat : public Vehicle {
public:
    Boat(int id = 0, const QString& brand = "", const QString& model = "",
        int year = 2000, double weight = 0.0);

    QString getType() const override { return QStringLiteral("Водный транспорт"); }

    QVector<int> getVisibleColumns() const override {
        return { Id, Type, Brand, Model, Year, Weight };
    }

    QString getColumnHeader(int column) const override;
    QVariant getColumnData(int column, int role = Qt::DisplayRole) const override;
    bool setColumnData(int column, const QVariant& value) override;
};