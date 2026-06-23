#include "VehicleDelegate.h"

VehicleDelegate::VehicleDelegate(QObject* parent) : QStyledItemDelegate(parent)  {}

QWidget* VehicleDelegate::createEditor(
	QWidget* parent, 
	const QStyleOptionViewItem& option, 
	const QModelIndex& index) const
{
	Q_UNUSED(option);

	switch (index.column())
	{
		case Vehicle::Year:
		{
			auto* editor = new QSpinBox(parent);

			editor->setRange(
				1900,
				QDate::currentDate().year());
			
			return editor;
		}

		case Vehicle::Weight:
		{
			auto* editor = new QDoubleSpinBox(parent);

			editor->setRange(0, 1000000);

			return editor;
		}

		default:
			return QStyledItemDelegate::createEditor(
				parent,
				option,
				index);
	}
}

void VehicleDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	switch (index.column())
	{
		case Vehicle::Year:
		{
			auto* sbYear = qobject_cast<QSpinBox*>(editor);
			
			if (!sbYear)
				return;

			sbYear->setValue(index.data().toInt());
			break;
		}
		case Vehicle::Weight:
		{
			auto* dsbWeight = qobject_cast<QDoubleSpinBox*>(editor);

			if (!dsbWeight)
				return;

			dsbWeight->setValue(index.data().toDouble());
			break;
		}
		default:
			QStyledItemDelegate::setEditorData(editor, index);
			return;
	}
}

void VehicleDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	auto* proxyModel = qobject_cast<QSortFilterProxyModel*>(model);

	if (!proxyModel)
	{
		QStyledItemDelegate::setModelData(editor, model, index);
		return;
	}

	auto* vehicleModel = qobject_cast<VehicleModel*>(proxyModel->sourceModel());

	if (!vehicleModel)
		return;

	QVariant value;

	switch (index.column())
	{
		case Vehicle::Year:
		{
			auto* sbYear = qobject_cast<QSpinBox*>(editor);
			value = sbYear->value();
			break;
		}
		case Vehicle::Weight:
		{
			auto* dsbWeight = qobject_cast<QDoubleSpinBox*>(editor);
			value = dsbWeight->value();	
			break;
		}
		default:
		{
			QStyledItemDelegate::setModelData(editor, model, index);
			return;
		}
	}
	QModelIndex sourceIndex = proxyModel->mapToSource(index);

	if (!vehicleModel->setData(sourceIndex, value, Qt::EditRole))
	{
		QMessageBox::warning(
			editor,
			QStringLiteral("Îøèáêà"),
			vehicleModel->lastError());
	}
}

void VehicleDelegate::updateEditorGeometry(
	QWidget* editor,
	const QStyleOptionViewItem& option,
	const QModelIndex&) const
{
	editor->setGeometry(option.rect);
}

