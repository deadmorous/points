// ParamModel.cpp

#include "ParamModel.h"
#include "ode_num_int/OptionalParameters.h"

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
    auto parentPath = parent.isValid()? m_paths.byIndex(parent.internalId()): QString();
    auto root = m_source->parameters();
    auto& param = OptionalParameters::parameters(root, parentPath.toUtf8().constData());
    Q_ASSERT(row >= 0   &&   row < param.size());
    auto it = param.begin();
    std::advance(it, row);
    auto path = QString::fromUtf8(it->first.c_str());
    if (!parentPath.isEmpty())
        path.prepend(parentPath + ".");
    auto id = m_paths.insert(path);
    return createIndex(row, column, id);
}

QModelIndex ParamModel::parent(const QModelIndex &child) const
{
    Q_ASSERT(child.isValid());
    auto path = m_paths.byIndex(child.internalId());
    auto i = path.lastIndexOf('.');
    if (i == -1)
        return  QModelIndex();
    auto parentPath = path.left(i);
    auto parentId = m_paths.insert(parentPath);
    auto name = path.mid(i+1);
    auto root = m_source->parameters();
    auto& param = OptionalParameters::parameters(root, parentPath.toUtf8().constData());
    auto it = param.find(name.toUtf8().constData());
    Q_ASSERT(it != param.end());
    auto parentRow = static_cast<int>(std::distance(param.begin(), it));
    return createIndex(parentRow, 0, parentId);
}

int ParamModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return false;
    auto parentPath = parent.isValid()? m_paths.byIndex(parent.internalId()): QString();
    auto root = m_source->parameters();
    if (parentPath.isEmpty())
        return root.size();
    auto& value = OptionalParameters::value(root, parentPath.toUtf8().constData());
    auto nestedParam = value.nestedParameters();
    return nestedParam? static_cast<int>(nestedParam->size()): 0;
}

int ParamModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

bool ParamModel::hasChildren(const QModelIndex &parent) const
{
    return ParamModel::rowCount(parent) > 0;
}

QVariant ParamModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    auto path = m_paths.byIndex(index.internalId());
    switch (index.column()) {
    case 0: {
        auto i = path.lastIndexOf('.');
        return i == -1? path: path.mid(i+1);
    }
    case 1: {
        auto root = m_source->parameters();
        auto& value = OptionalParameters::value(root, path.toUtf8().constData());
        return QString::fromUtf8(value.value<std::string>().c_str());
    }
    default:
        Q_ASSERT(false);
    }
}

bool ParamModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false; // TODO
}

QVariant ParamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case 0:
            return tr("name");
        case 1:
            return tr("value");
        default:
            Q_ASSERT(false);
        }
    }
    return QVariant();
}

//QMap<int, QVariant> ParamModel::itemData(const QModelIndex &index) const
//{
//    return QMap<int, QVariant>();
//}

//bool ParamModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
//{
//    return false; // TODO
//}

Qt::ItemFlags ParamModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::NoItemFlags;
    if (index.isValid()) {
        result |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        if (index.column() == 1)
            result |= Qt::ItemIsEditable;
    }
    return result;
}

} // namespace ctm
