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
        if (m_drawGrid) {
            auto itransform = transform.inverted();
            auto toQPointF = [](const QPoint& p) {
                return QPointF(p.x(), p.y());
            };
            auto p1 = itransform.map(toQPointF(rect().bottomLeft()));
            auto p2 = itransform.map(toQPointF(rect().topRight()));
            QPen pen(QColor(QRgb(0xdddddd)), 1);
            pen.setCosmetic(true);
            p.setPen(pen);
            auto drawVline = [&](double x) {
                p.drawLine(QPointF(x, p1.y()), QPointF(x, p2.y()));
            };
            auto drawHline = [&](double y) {
                p.drawLine(QPointF(p1.x(), y), QPointF(p2.x(), y));
            };
            auto size = std::max(p2.x()-p1.x(), p2.y()-p1.y());
            auto h = pow(10, floor(log10(size))-1);
            auto x1 = ceil(p1.x()/h)*h;
            auto x2 = floor(p2.x()/h)*(h+0.1);
            for (auto x=x1; x<x2; x+=h)
                drawVline(x);
            auto y1 = ceil(p1.y()/h)*h;
            auto y2 = floor(p2.y()/h)*(h+0.1);
            for (auto y=y1; y<y2; y+=h)
                drawHline(y);
        }
        auto _2n = m_state.size();
        auto pointRadius = 3*pixelSize;
        p.setBrush(Qt::black);
        p.setPen(Qt::NoPen);
        p.setRenderHint(QPainter::Antialiasing);
        for(unsigned int _2i=0; _2i<_2n; _2i+=2)
        {
            if (m_colorPoints)
                p.setBrush(QColor::fromHsvF(static_cast<double>(_2i)/_2n, 1, 0.7));
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
