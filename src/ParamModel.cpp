// ParamModel.cpp

#include "ParamModel.h"
#include "ode_num_int/OptionalParameters.h"
#include "ModelRoles.h"
#include "decl_metatype.h"

namespace ctm {

ParamModel::ParamModel(QObject *parent) : QAbstractItemModel(parent)
{
}

OptionalParameters *ParamModel::source() const
{
    return m_source;
}

void ParamModel::setSource(OptionalParameters *source)
{
    m_source = source;
}

QModelIndex ParamModel::index(int row, int column,
                          const QModelIndex &parent) const
{
    if (!m_source)
        return createIndex(row, column);
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
    if (!m_source)
        return QModelIndex();
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
    if (!m_source)
        return 0;
    if (parent.isValid() && parent.column() != 0)
        return 0;
    auto parentPath = parent.isValid()? m_paths.byIndex(parent.internalId()): QString();
    auto root = m_source->parameters();
    if (parentPath.isEmpty())
        return static_cast<int>(root.size());
    auto& value = OptionalParameters::value(root, parentPath.toUtf8().constData());
    auto nestedParam = value.nestedParameters();
    return nestedParam? static_cast<int>(nestedParam->size()): 0;
}

int ParamModel::columnCount(const QModelIndex &parent) const
{
    if (!m_source)
        return 0;
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
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
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
    else if (role == ModelRoles::IsFactoryObject) {
        auto root = m_source->parameters();
        auto& value = OptionalParameters::value(root, path.toUtf8().constData());
        return value.typeRegistryGetter()? true: false;
    }
    else if (role == ModelRoles::TypeRegistryGetter) {
        auto root = m_source->parameters();
        auto& value = OptionalParameters::value(root, path.toUtf8().constData());
        return QVariant::fromValue(value.typeRegistryGetter());
    }
    else
        return QVariant();
}

bool ParamModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    Q_ASSERT(idx.isValid());
    auto root = m_source->parameters();
    auto path = m_paths.byIndex(idx.internalId());
    auto& v = OptionalParameters::value(root, path.toUtf8().constData());
    auto hadNestedParameters = v.nestedParameters()? true: false;
    v = value.toString().toUtf8().constData();
    try {
        auto parent = idx.parent();
        auto row = idx.row();
        m_source->setParameters(root);
        if (hadNestedParameters) {
            beginRemoveRows(parent, row, row);
            endRemoveRows();
            beginInsertRows(parent, row, row);
            endInsertRows();
        }
        emit dataChanged(index(row, 0, parent), index(row, 1, parent));
        return true;
    }
    catch(const std::exception& e) {
        emit editingFailed(QString::fromUtf8(e.what()));
        return  false;
    }
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
