
#include "Daemon.hpp"
#include "Log.hpp"

bool Daemon::m_isRunning = false;
bool Daemon::m_reload = false;

Daemon::Daemon() {

    m_isRunning = true;
    m_reload = false;

    // Register the signal function to read external events
    signal(SIGINT, Daemon::signalHandler);
    signal(SIGTERM, Daemon::signalHandler);
    signal(SIGHUP, Daemon::signalHandler);
}

bool Daemon::IsRunning() {
    if (m_reload) {
        m_reload = false;
        m_reloadFunc();
    }
    return m_isRunning;
}

void Daemon::signalHandler(int signal) {
    LOG_INFO("Interrup signal number [", signal,"] recived.");
    switch(signal) {
        case SIGINT:
        case SIGTERM: {
            m_isRunning = false;
            break;
        }
        case SIGHUP: {
            m_reload = true;
            break;
        }
    }
}