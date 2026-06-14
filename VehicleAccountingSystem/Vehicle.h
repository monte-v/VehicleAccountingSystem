#pragma once
#include <QString>

struct Vehicle
{
    int id;
    QString type;
    QString brand;
    QString model;
    int year;
    double weight;

    static constexpr int FIELD_COUNT = 5;
};