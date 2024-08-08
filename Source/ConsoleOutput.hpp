#ifndef HX_CONSOLE_OUTPUT_H
#define HX_CONSOLE_OUTPUT_H

#include <cmath>
#include <cstdio>
#include <memory>
#include <stdint.h>
#include <vector>
#include <sys/ioctl.h>

namespace HX {

#ifdef _WIN32
    typedef CHAR_INFO Cell;

#   define GET_CHAR(ch) ch.Char.AsciiChar
#elif __GNUC__
    typedef  uint8_t Cell;

#   define HX_GET_CHAR(ch) ch

#   define HX_GET_CONSOLE_DIM(vec2)                 \
    {                                               \
        struct winsize w;                           \
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);       \
        vec2.x = w.ws_col;                          \
        vec2.y = w.ws_row;                          \
    }
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

    // Elemnent size can be represented either as an amount of characters
    // or percent of availible console dimensions
    union Dimensions {
        Dimensions() = default;
        Dimensions(HX::Vec2<float> f) : percent(f) {};
        Dimensions(HX::Vec2<uint32_t> i) : cells(i) {};

        public:
        HX::Vec2<float> percent;
        HX::Vec2<uint32_t> cells;
    };

    struct UiElement {
        UiElement() noexcept : Dim(Vec2<float>(10.f, 10.f)) {};
        ~UiElement() noexcept = default;
        
        Dimensions Dim;
        bool IsPercent = false;
        // Elements are painted from left to right, from lowest index to highest
        uint8_t ElementIndex = 0;
        Cell* Target = nullptr;
    };

    struct Ui : private std::vector<std::shared_ptr<HX::UiElement>> {
        public:
            void Add(std::shared_ptr<HX::UiElement> ue);
            size_t Size() { return this->size(); }
            uint8_t GetLastAvaliableIndex() { return (this->size()); }

            std::shared_ptr<HX::UiElement> operator[](size_t i) { return *(this->begin() + i); }
    };

    class ConsoleOut {
        HX::Vec2<uint32_t> m_CurDim = {};
        Ui m_Ui = {};
        SwapBuffers m_Outputs = SwapBuffers(HX::MaxOutHeight * HX::MaxOutWidth);

    public:
        ConsoleOut() noexcept = default;
        ~ConsoleOut() noexcept = default;
        
    public:
        void Update();
        static void Clear();
        void Paint();

        void AddElement(std::shared_ptr<HX::UiElement> ue) {
            m_Ui.Add(std::move(ue));
        }
    };
}

#endif // HX_CONSOLE_OUTPUT_H
