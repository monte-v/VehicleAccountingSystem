#pragma once
#include <Vehicle.h>
#include <QAbstractTableModel>

class VehicleModel : public QAbstractTableModel
{
public:
    explicit VehicleModel(QObject* parent = nullptr);

    // Методы модели
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QVariant headerData(int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool setData(const QModelIndex& index,
        const QVariant& value,
        int role = Qt::EditRole) override;

    // CRUD
    void addVehicle(const Vehicle& vehicle);
    void removeVehicle(int row);

    QVector<Vehicle> vehicles() const;
    void setVehicles(const QVector<Vehicle>& vehicles);

private:
    QVector<Vehicle> m_vehicles;
    int m_nextId = 1;
};

