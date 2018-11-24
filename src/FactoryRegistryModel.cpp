// FactoryRegistryModel.cpp

#include "FactoryRegistryModel.h"
#include "ode_num_int/OptionalParameters.h"

namespace ctm {

FactoryRegistryModel::FactoryRegistryModel(
        std::function<std::vector<std::string>()> source, QObject *parent) : QAbstractListModel(parent)
{
    m_items << QString();
    for (auto name : source()) {
        m_items << QString::fromUtf8(name.c_str());
    }
}

int FactoryRegistryModel::rowCount(const QModelIndex &parent) const
{
    return m_items.size();
}

QVariant FactoryRegistryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if ((role == Qt::DisplayRole || role == Qt::EditRole) && index.column() == 0) {
        Q_ASSERT(index.row() >= 0   &&   index.row() < m_items.size());
        return m_items[index.row()];
    }
    else
        return QVariant();
}

} // namespace ctm
