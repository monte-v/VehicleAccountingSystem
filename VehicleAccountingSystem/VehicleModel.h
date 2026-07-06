#pragma once
#include <Vehicle.h>
#include <QAbstractTableModel>
#include <QDate>
#include <memory> 

class VehicleModel : public QAbstractTableModel
{
    Q_OBJECT

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
    void addVehicle(std::shared_ptr<Vehicle> vehicle);
    void removeVehicle(int row);
    QVector<std::shared_ptr<Vehicle>> vehicles() const;
    void setVehicles(const QVector<std::shared_ptr<Vehicle>>& vehicles);

    QString lastError() const;

private:
    QVector<std::shared_ptr<Vehicle>> m_vehicles;
    int m_nextId = 1;
    QString m_lastError;
};
