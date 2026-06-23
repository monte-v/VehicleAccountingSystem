#pragma once
#include <QString>

struct Vehicle
{
    enum Columns
    {
        Id = 0,
        Type,
        Brand,
        Model,
        Year,
        Weight,

        FIELD_COUNT
    };

    int id;
    QString type;
    QString brand;
    QString model;
    int year;
    double weight;

};