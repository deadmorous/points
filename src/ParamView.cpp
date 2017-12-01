// ParamView.cpp

#include "ParamView.h"
#include <QLabel>
#include <QVBoxLayout>

namespace ctm {

ParamView::ParamView(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(tr("TODO")));
}

std::shared_ptr<OptionalParameters> ParamView::source() const
{
    return m_source;
}

void ParamView::setSource(std::shared_ptr<OptionalParameters> source)
{
    m_source = source;
}

} // namespace ctm
