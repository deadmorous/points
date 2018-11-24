// ParamView.h

#ifndef _PARAMVIEW_H_
#define _PARAMVIEW_H_

#include <QWidget>
#include <memory>

class QTreeView;
class QAbstractItemDelegate;

namespace ctm {

class OptionalParameters;
class ParamModel;

class ParamView : public QWidget
{
Q_OBJECT
public:
    explicit ParamView(QWidget *parent = nullptr);
    OptionalParameters *source() const;
    void setSource(OptionalParameters *source);
    ParamModel *model();

private:
    ParamModel *m_model;
    QTreeView *m_view;
    QAbstractItemDelegate *m_delegate;
};

} // namespace ctm

#endif // _PARAMVIEW_H_
