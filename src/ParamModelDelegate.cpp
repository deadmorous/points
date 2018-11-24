// ParamModelDelegate.cpp

#include "ParamModelDelegate.h"
#include "ModelRoles.h"
#include "FactoryRegistryModel.h"
#include "decl_metatype.h"
#include <QComboBox>

namespace ctm {

ParamModelDelegate::ParamModelDelegate(QWidget *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *ParamModelDelegate::createEditor(
        QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data(ModelRoles::IsFactoryObject).toBool()) {
        auto result = new QComboBox(parent);
        auto trg = index.data(ModelRoles::TypeRegistryGetter).value<OptionalParameters::TypeRegistryGetter>();
        result->setModel(new FactoryRegistryModel(trg, result));
        // TODO: Use option
        return result;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ParamModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.data(ModelRoles::IsFactoryObject).toBool()) {
        auto type = index.data(Qt::EditRole);
        auto cb = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(cb);
        auto cbm = cb->model();
        Q_ASSERT(cbm);
        int index = -1;
        for (int i=0, n=cbm->rowCount(); i<n; ++i)
            if (type == cbm->index(i, 0).data().toString()) {
                index = i;
                break;
            }
        cb->setCurrentIndex(index);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void ParamModelDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    if (index.data(ModelRoles::IsFactoryObject).toBool()) {
        auto cb = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(cb);
        model->setData(index, cb->currentText());
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

} // namespace ctm
