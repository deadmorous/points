// SimulationRunner.cpp

#include "SimulationRunner.h"
#include <QTimerEvent>

namespace ctm {

SimulationRunner::SimulationRunner(QObject *parent) :
    QObject(parent)
{}

SimulationRunner::~SimulationRunner()
{
    stopSimulation();
}

void SimulationRunner::startSimulation()
{
    if (m_worker.isRunning()) {
        emit message(tr("Simulatoin is already running"));
        return;
    }
    m_worker.start();
    if (!m_timer) {
        m_timer = startTimer(40);
        Q_ASSERT(m_timer);
    }
}

void SimulationRunner::stopSimulation()
{
    if (m_worker.isRunning()) {
        m_worker.stop();
        m_worker.wait();
    }
    if (m_timer) {
        killTimer(m_timer);
        m_timer = 0;
    }
}

void SimulationRunner::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timer   &&   m_worker.ready()) {
        auto cs = m_worker.currentState();
        emit updateState(cs.first, cs.second);
        m_worker.simulateFurther();
    }
}

} // namespace ctm
