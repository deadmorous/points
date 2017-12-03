// ParamView.cpp

#include "ParamView.h"
#include "ParamModel.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>

namespace ctm {

ParamView::ParamView(QWidget *parent) :
    QWidget(parent),
    m_model(new ParamModel(this)),
    m_view(new QTreeView)
{
    m_view->setModel(m_model);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
}

std::shared_ptr<OptionalParameters> ParamView::source() const
{
    return m_model->source();
}

void ParamView::setSource(std::shared_ptr<OptionalParameters> source)
{
    m_model->setSource(source);
}

} // namespace ctm
