#include "VehicleFilterProxyModel.h"
#include "Vehicle.h"

VehicleFilterProxyModel::VehicleFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void VehicleFilterProxyModel::setSearchText(const QString& text)
{
    m_searchText = text;
    invalidateFilter();
}

void VehicleFilterProxyModel::setTypeFilter(const QString& type)
{
    m_typeFilter = type;
    invalidateFilter();
}

bool VehicleFilterProxyModel::filterAcceptsRow(int sourceRow,
    const QModelIndex& sourceParent) const
{
    // Сначала проверяем тип ТС
    if (!m_typeFilter.isEmpty())
    {
        QModelIndex typeIndex =
            sourceModel()->index(sourceRow, Vehicle::Type, sourceParent);

        QString type =
            sourceModel()->data(typeIndex).toString();

        if (type != m_typeFilter)
            return false;
    }

    if (m_searchText.isEmpty())
        return true;

    // Поиск по всем колонкам
    for (int col = 0; col < sourceModel()->columnCount(); ++col)
    {
        QModelIndex index =
            sourceModel()->index(sourceRow, col, sourceParent);

        QString text =
            sourceModel()->data(index).toString();

        if (text.contains(m_searchText, Qt::CaseInsensitive))
            return true;
    }

    return false;
}