// ParamModel.cpp

#include "ParamModel.h"

namespace ctm {

ParamModel::ParamModel(QObject *parent) : QAbstractItemModel(parent)
{
}

std::shared_ptr<OptionalParameters> ParamModel::source() const
{
    return m_source;
}

void ParamModel::setSource(std::shared_ptr<OptionalParameters> source)
{
    m_source = source;
}

QModelIndex ParamModel::index(int row, int column,
                          const QModelIndex &parent) const
{
    return QModelIndex(); // TODO
}

QModelIndex ParamModel::parent(const QModelIndex &child) const
{
    return QModelIndex(); // TODO
}

int ParamModel::rowCount(const QModelIndex &parent) const
{
    return 0; // TODO
}

int ParamModel::columnCount(const QModelIndex &parent) const
{
    return 0; // TODO
}

bool ParamModel::hasChildren(const QModelIndex &parent) const
{
    return false; // TODO
}

QVariant ParamModel::data(const QModelIndex &index, int role) const
{
    return QVariant(); // TODO
}

bool ParamModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false; // TODO
}

QVariant ParamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant(); // TODO
}

QMap<int, QVariant> ParamModel::itemData(const QModelIndex &index) const
{
    return QMap<int, QVariant>();
}

bool ParamModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    return false; // TODO
}

Qt::ItemFlags ParamModel::flags(const QModelIndex &index) const
{
    return Qt::ItemFlags(); // TODO
}

} // namespace ctm
