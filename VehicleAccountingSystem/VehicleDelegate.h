#pragma once
#include <QStyledItemDelegate>
#include <QSpinBox>
#include <QDate>
#include <QMessageBox>
#include <QSortFilterProxyModel>

#include "Vehicle.h"
#include "VehicleModel.h"

class VehicleDelegate: public QStyledItemDelegate
{
public:
	explicit VehicleDelegate(QObject* parent = nullptr);

	QWidget* createEditor(
		QWidget* parent,
		const QStyleOptionViewItem& option,
		const QModelIndex& index
	) const override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
	void updateEditorGeometry(
		QWidget* editor,
		const QStyleOptionViewItem& option,
		const QModelIndex&) const override;
};

