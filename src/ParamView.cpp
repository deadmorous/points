// ParamView.cpp

#include "ParamView.h"
#include "ParamModel.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>
#include <QHeaderView>

namespace ctm {

ParamView::ParamView(QWidget *parent) :
    QWidget(parent),
    m_model(new ParamModel(this)),
    m_view(new QTreeView)
{
    setMinimumHeight(100);
    setMinimumWidth(100);
    m_view->setModel(m_model);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    m_view->header()->setSectionResizeMode( QHeaderView::ResizeToContents );
    m_view->header()->setMinimumSectionSize( 50 );
}

OptionalParameters *ParamView::source() const
{
    return m_model->source();
}

void ParamView::setSource(OptionalParameters* source)
{
    m_model->setSource(source);
}

ParamModel *ParamView::model() {
    return m_model;
}

} // namespace ctm
