#ifndef HX_CONSOLE_OUTPUT_H
#define HX_CONSOLE_OUTPUT_H

#include <stdint.h>

namespace HX {

#ifdef _WIN32
    typedef CHAR_INFO Cell;

#   define GET_CHAR(ch) ch.Char.AsciiChar
#elif __GNUC__
    typedef  uint8_t Cell;

#   define GET_CHAR(ch) ch
#endif // _WIN32

    constexpr int32_t MaxOutWidth = 512;
    constexpr int32_t MaxOutHeight = 512;

    /**
    * Two buffers of the same size that can be swapped with each other.
    **/
    struct SwapBuffers {
        SwapBuffers() = delete;
        SwapBuffers(int32_t size) noexcept;
        ~SwapBuffers() noexcept;

        int32_t Size = -1;

        Cell* Front = nullptr;
        Cell* Back = nullptr;

        /**
        * Swaps front with back. 
        **/
        void Swap() {
            Cell* tmp = Front;
            Front = Back;
            Back = tmp;
        }
    };

    class ConsoleOut {
        SwapBuffers m_Outputs = SwapBuffers(HX::MaxOutHeight * HX::MaxOutWidth);

    public:
        ConsoleOut() noexcept = default;
        ~ConsoleOut() noexcept = default;

    };
}

#endif // HX_CONSOLE_OUTPUT_H
