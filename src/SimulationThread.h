// SimulationThread.h

#pragma once

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include "ode_num_int/VectorTemplate.h"
#include "TaskConfig.h"
#include "vec_type.h"

namespace ctm {

class SimulationThread : public QThread
{
Q_OBJECT
public:
    explicit SimulationThread(QObject *parent = nullptr);
    void simulateFurther();
    void stop();
    bool ready() const;
    std::pair<double, V> currentState() const;
    QString currentError() const;

protected:
    void run() override;

private:
    QSemaphore m_semaphore;
    mutable QMutex m_mutex;
    double m_currentTime;
    V m_currentState;
    bool m_ready = true;
    bool m_stopRequested = false;
    QString m_errorMessage;

    void rawRun();
};

} // namespace ctm
