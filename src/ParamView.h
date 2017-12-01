// ParamView.h

#ifndef _PARAMVIEW_H_
#define _PARAMVIEW_H_

#include <QWidget>
#include <memory>

namespace ctm {

class OptionalParameters;

class ParamView : public QWidget
{
Q_OBJECT
public:
    explicit ParamView(QWidget *parent = nullptr);
    std::shared_ptr<OptionalParameters> source() const;
    void setSource(std::shared_ptr<OptionalParameters> source);

private:
    std::shared_ptr<OptionalParameters> m_source;
};

} // namespace ctm

#endif // _PARAMVIEW_H_
