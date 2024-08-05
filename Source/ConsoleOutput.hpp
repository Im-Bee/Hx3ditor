#ifndef HX_CONSOLE_OUTPUT_H
#define HX_CONSOLE_OUTPUT_H

#include "Hxditr.hpp"
#include <cmath>
#include <memory>
#include <stdint.h>
#include <vector>

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

    class UiElement {
        // Elemnent size can be represented either as an amount of characters
        // or percent of availible console dimensions
        union m_Dim {
            Vec2<float> percent;
            Vec2<uint32_t> cells;
        };
        
        // Elements are painted from left to right, from lowest index to highest
        uint8_t m_uElementIndex = 0;

    public:
        UiElement() noexcept = default;
        UiElement(uint8_t ei) : m_uElementIndex(ei) {};
        ~UiElement() noexcept = default;

    public:
        void SetIndex(uint8_t i) {
            m_uElementIndex = i;
        }

        const uint8_t& GetIndex() {
            return m_uElementIndex;
        }
    };

    struct Ui : private std::vector<std::shared_ptr<HX::UiElement>> {
        public:
            void Add(std::shared_ptr<HX::UiElement> ue);
            size_t Size() { return this->size(); }
            uint8_t GetLastAvaliableIndex() { return (this->size()); }

            std::shared_ptr<HX::UiElement> operator[](size_t i) { return *(this->begin() + i); }
    };

    class ConsoleOut {
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
