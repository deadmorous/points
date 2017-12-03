// ParamView.h

#ifndef _PARAMVIEW_H_
#define _PARAMVIEW_H_

#include <QWidget>
#include <memory>

class QTreeView;

namespace ctm {

class OptionalParameters;
class ParamModel;

class ParamView : public QWidget
{
Q_OBJECT
public:
    explicit ParamView(QWidget *parent = nullptr);
    std::shared_ptr<OptionalParameters> source() const;
    void setSource(std::shared_ptr<OptionalParameters> source);

private:
    ParamModel *m_model;
    QTreeView *m_view;
};

} // namespace ctm

#endif // _PARAMVIEW_H_
