// ParamModel.h

#ifndef _PARAMMODEL_H_
#define _PARAMMODEL_H_

#include <QAbstractItemModel>
#include <memory>
#include "IndexedComparable.h"

namespace ctm {

class OptionalParameters;

class ParamModel : public QAbstractItemModel
{
Q_OBJECT
public:
    explicit ParamModel(QObject *parent = nullptr);
    std::shared_ptr<OptionalParameters> source() const;
    void setSource(std::shared_ptr<OptionalParameters> source);

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;
    QMap<int, QVariant> itemData(const QModelIndex &index) const override;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    std::shared_ptr<OptionalParameters> m_source;
    IndexedComparable<quintptr, QString> m_paths;
};

} // namespace ctm

#endif // _PARAMMODEL_H_
