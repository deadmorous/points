// PointsView.h

#ifndef _POINTSVIEW_H_
#define _POINTSVIEW_H_

#include <QWidget>
#include "ode_num_int/VectorTemplate.h"

namespace points {

using VD = ctm::math::VectorData<double>;
using V = ctm::math::Vector< double >;

class PointsView : public QWidget
{
Q_OBJECT
public:
    explicit PointsView(QWidget *parent = nullptr);

public slots:
    void setData(const V& data);
    void resetView();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    V m_data;
    QPointF m_sceneCenter;
    QSizeF m_sceneSize;
    bool m_hasTransformData;

    QPointF m_userOffset;
    double m_userScale;
    void fit();
};

} // namespace points

#endif // _POINTSVIEW_H_
