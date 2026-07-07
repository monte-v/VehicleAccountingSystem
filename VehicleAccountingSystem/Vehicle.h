#pragma once
#include <QString>
#include <QVariant>

class Vehicle
{
public:
    enum Columns {
        Id = 0,
        Type,
        Brand,
        Model,
        Year,
        Weight,
        FIELD_COUNT
    };

    Vehicle(int id = 0, const QString& brand = "", const QString& model = "",
        int year = 2000, double weight = 0.0);
    virtual ~Vehicle() = default;

    virtual QString getType() const = 0;
 
    QString getColumnHeader(int column) const;
    QVariant getColumnData(int column, int role = Qt::DisplayRole) const;
    bool setColumnData(int column, const QVariant& value);

    int getId() const { return m_id; }
    QString getBrand() const { return m_brand; }
    QString getModel() const { return m_model; }
    int getYear() const { return m_year; }
    double getWeight() const { return m_weight; }

    void setId(int id) { m_id = id; }
    void setBrand(const QString& brand) { m_brand = brand; }
    void setModel(const QString& model) { m_model = model; }
    void setYear(int year) { m_year = year; }
    void setWeight(double weight) { m_weight = weight; }

protected:
    int m_id;
    QString m_type;
    QString m_brand;
    QString m_model;
    int m_year;
    double m_weight;
};