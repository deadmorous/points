// PointsView.cpp

#include "PointsView.h"
#include <QPainter>

namespace points {

PointsView::PointsView(QWidget *parent) :
    QWidget (parent),
    m_sceneCenter(0, 0),
    m_sceneSize(0, 0),
    m_hasTransformData(false),
    m_userOffset(0, 0),
    m_userScale(0.95)
{
    setMinimumSize(400, 400);
}

void PointsView::setState(double time, const V& state)
{
    Q_UNUSED(time); // TODO
    m_state = state;
    fit();
    update();
}

void PointsView::resetView()
{
    m_hasTransformData = false;
    m_userOffset = QPointF(0, 0);
    m_userScale = 0.95;
}

void PointsView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    if (m_state.empty())
        p.drawText(rect(), Qt::AlignCenter, "No point configuration has been set");
    else if (m_state.size() & 1)
        p.drawText(rect(), Qt::AlignCenter, "Incorrect data size");
    else {
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(Qt::black);
        p.setPen(Qt::NoPen);
        p.fillRect(rect(), Qt::white);
        QTransform transform;
        auto sc = m_sceneSize.width()*height() < m_sceneSize.height()*width()?
                    height() / m_sceneSize.height() : width() / m_sceneSize.width();
        sc *= m_userScale;
        double pixelSize = 1./sc;
        transform.translate(width()/2, height()/2);
        transform.scale(sc, -sc);
        transform.translate(-m_sceneCenter.x(), -m_sceneCenter.y());
        p.setTransform(transform);
        auto _2n = m_state.size();
        auto pointRadius = 3*pixelSize;
        for(unsigned int _2i=0; _2i<_2n; _2i+=2)
        {
            p.drawEllipse(QPointF(m_state[_2i], m_state[_2i+1]), pointRadius, pointRadius);
        }
    }
}

void PointsView::fit()
{
    auto _2n = m_state.size();
    if (_2n < 2   ||   (_2n & 1))
        return;
    auto xmin = m_state[0], xmax = xmin, ymin = m_state[1], ymax = ymin;
    auto addPoint = [&](double x, double y) {
        if (xmin > x)
            xmin = x;
        else if (xmax < x)
            xmax = x;
        if (ymin > y)
            ymin = y;
        else if (ymax < y)
            ymax = y;
    };
    for(unsigned int _2i=2; _2i<_2n; _2i+=2)
        addPoint(m_state[_2i], m_state[_2i+1]);
    if (m_hasTransformData) {
        addPoint(m_sceneCenter.x() - 0.5*m_sceneSize.width(), m_sceneCenter.y() - 0.5*m_sceneSize.height());
        addPoint(m_sceneCenter.x() + 0.5*m_sceneSize.width(), m_sceneCenter.y() + 0.5*m_sceneSize.height());
    }
    else
        m_hasTransformData = true;
    m_sceneCenter = QPointF(0.5*(xmin+xmax), 0.5*(ymin+ymax));
    m_sceneSize = QSizeF(xmax-xmin, ymax-ymin);
}

} // namespace points
