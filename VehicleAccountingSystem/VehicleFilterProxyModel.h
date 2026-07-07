#pragma once

#include <QSortFilterProxyModel>

class VehicleFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit VehicleFilterProxyModel(QObject* parent = nullptr);

    void setSearchText(const QString& text);
    void setTypeFilter(const QString& type);

protected:
    bool filterAcceptsRow(int sourceRow,
        const QModelIndex& sourceParent) const override;

private:
    QString m_searchText;
    int m_searchColumn = -1;          // -1 = искать по всем колонкам
    QString m_typeFilter = QStringLiteral("");
};