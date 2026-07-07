#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include "ui_VehicleAccountingSystem.h"
#include "VehicleModel.h"
#include "VehicleDialog.h"
#include "JsonStorage.h"
#include "VehicleDelegate.h"
#include "VehicleFilterProxyModel.h"

class VehicleAccountingSystem : public QMainWindow
{
    Q_OBJECT

public:
    VehicleAccountingSystem(QWidget *parent = nullptr);
    ~VehicleAccountingSystem();

private:
    void updateTypeFilterList();

    Ui::VehicleAccountingSystemClass ui;
    VehicleModel m_model;
    VehicleFilterProxyModel m_proxyModel;
    VehicleDelegate* m_delegate;

private slots:
    void on_btnDelete_clicked();
    void on_btnAdd_clicked();
    
    void on_mbfOpen_triggered();
    void on_mbfSave_triggered();

    void onSearchTextChanged(const QString& text);

    void onTypeFilterChanged(QListWidgetItem* current,
        QListWidgetItem* previous); 
};

