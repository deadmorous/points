// SimulationThread.cpp

#include "SimulationThread.h"

namespace ctm {

SimulationThread::SimulationThread(QObject *parent) :
    QThread(parent)
{}

void SimulationThread::simulateFurther()
{
    m_semaphore.release();
}

void SimulationThread::stop()
{
    QMutexLocker lock(&m_mutex);
    m_stopRequested = true;
    simulateFurther();
}

bool SimulationThread::ready() const
{
    QMutexLocker lock(&m_mutex);
    return m_ready;
}

auto SimulationThread::currentState() const -> std::pair<double, V>
{
    QMutexLocker lock(&m_mutex);
    return std::make_pair(m_currentTime, m_currentState);
}

void SimulationThread::run()
{
    try {
        {
            QMutexLocker lock(&m_mutex);
            m_errorMessage.clear();
            m_stopRequested = false;
        }
        rawRun();
        exit(0);
    }
    catch(const std::exception& e) {
        {
            QMutexLocker lock(&m_mutex);
            m_errorMessage = QString::fromUtf8(e.what());
        }
        exit(1);
    }
}

void SimulationThread::rawRun()
{
    auto& cfg = TaskConfig::cfg();
    auto initState = cfg.parameterProvider()->initState();
    if (!initState)
        throw cxx::exception("No initial state");
    double t0 = initState->initialTime();
    V x0 = initState->initialState();
    {
        QMutexLocker lock(&m_mutex);
        m_currentState = x0;
    }
    auto sc = cfg.apply( std::set<unsigned int>(), t0, x0 );
    auto solver = sc.solver();

    forever {
        m_semaphore.acquire();
        QMutexLocker lock(&m_mutex);
        if (m_stopRequested)
            break;
        m_ready = false;
        lock.unlock();

        // TODO: piece of simulation
        auto startTime = solver->initialTime();
        solver->doStep();
        auto endTime = solver->initialTime();

        lock.relock();
        m_currentTime = endTime;
        m_currentState = solver->initialState();
        m_ready = true;
    }
}

} // namespace ctm
