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

    class Ui : public std::vector<std::shared_ptr<HX::UiElement>> {
        uint8_t m_AvalibleIndex = 0;

        public:
            void Add(std::shared_ptr<HX::UiElement> ue);

            uint8_t GetLastAvaliableIndex();
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

    public:
        void AddElement(std::shared_ptr<HX::UiElement> ue) {
            for (auto& i : m_Ui) {
                if (ue->GetIndex() == i->GetIndex()) {
                    HX_DBG_PRT("Warrning element with index ");
                    HX_DBG_PRT(ue->GetIndex());
                    HX_DBG_PRT_N(" already exists changing index to last availible");
                    
                    ue->SetIndex(m_Ui.GetLastAvaliableIndex());
                }
            }

            m_Ui.Add(std::move(ue));
        }
    };
}

#endif // HX_CONSOLE_OUTPUT_H
