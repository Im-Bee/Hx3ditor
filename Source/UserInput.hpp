#ifndef HX_USER_INPUT_H
#define HX_USER_INPUT_H

#include <atomic>
#include <mutex>
#include <thread>

namespace HX {
    constexpr uint32_t InputTimeOutMul = 100;

    class InputThread {
        std::atomic_bool m_Work = false;
        std::thread* m_pInputThread = nullptr;
        std::shared_ptr<HX::ditr> m_pDitr = nullptr;

        std::atomic_bool m_Exit = false;

    public:
        InputThread() noexcept;
        InputThread(std::shared_ptr<HX::ditr> ditr) noexcept;
        ~InputThread() noexcept;

        void SetDitr(std::shared_ptr<HX::ditr> ditr);

        const bool& Exit() { 
            static bool r = false;
            if (m_Exit.load())
                r = true;

            return r; 
        }

    private:
        void Loop();
    };
}

#endif // HX_USER_INPUT_H