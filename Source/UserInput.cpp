#include "Hxditr.hpp"
#include "UserInput.hpp"

HX::InputThread::InputThread() noexcept {
    m_Work.store(true);
    m_pInputThread = new std::thread(&HX::InputThread::Loop, this);
}

HX::InputThread::InputThread(std::shared_ptr<HX::ditr> ditr) noexcept {
    m_pDitr = ditr;

    m_Work.store(true);
    m_pInputThread = new std::thread(&HX::InputThread::Loop, this);
}

HX::InputThread::~InputThread() noexcept {
    m_Work.store(false);
    if (m_pInputThread) {
        m_pInputThread->join();
        m_pInputThread = nullptr;
    }
}

void HX::InputThread::SetDitr(std::shared_ptr<HX::ditr> ditr) {
    m_pDitr = ditr;
}

void HX::InputThread::Loop() {
    using namespace std::chrono_literals;
    auto timeout = 1ms;
    timeout = timeout * HX::InputTimeOutMul;

    while (m_Work.load()) {
        std::this_thread::sleep_for(timeout);

        if (!m_pDitr.get()) {
            continue;
        }
    }
}
