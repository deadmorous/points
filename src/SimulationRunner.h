// SimulationRunner.h

#pragma once

#include <QObject>
#include "SimulationThread.h"
#include "ode_num_int/VectorTemplate.h"
#include "vec_type.h"

namespace ctm {

class SimulationRunner : public QObject
{
Q_OBJECT
public:
    explicit SimulationRunner(QObject *parent = nullptr);
    ~SimulationRunner();

signals:
    void updateState(double time, const V& state);
    void message(const QString& what);

public slots:
    void startSimulation();
    void stopSimulation();

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    SimulationThread m_worker;
    int m_timer = 0;
};

} // namespace ctm
