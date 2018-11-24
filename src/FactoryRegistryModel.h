// FactoryRegistryModel.h

#ifndef _FACTORYREGISTRYMODEL_H_
#define _FACTORYREGISTRYMODEL_H_

#include <QAbstractItemModel>

namespace ctm {

class OptionalParameters;

class FactoryRegistryModel : public QAbstractListModel
{
Q_OBJECT
public:
    explicit FactoryRegistryModel(std::function<std::vector<std::string>()> source, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Qt::ItemFlags flags(const QModelIndex &index) const override;

// signals:
//     void editingFailed(const QString& what);

private:
    QStringList m_items;
};

} // namespace ctm

#endif // _FACTORYREGISTRYMODEL_H_
