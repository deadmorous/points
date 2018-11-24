// ParamModelDelegate.h

#ifndef _PARAMMODELDELEGATE_H_
#define _PARAMMODELDELEGATE_H_

#include <QStyledItemDelegate>

namespace ctm {

class ParamModelDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
    explicit ParamModelDelegate(QWidget *parent = nullptr);
    QWidget *createEditor(
            QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

} // namespace ctm

#endif // _PARAMMODELDELEGATE_H_
