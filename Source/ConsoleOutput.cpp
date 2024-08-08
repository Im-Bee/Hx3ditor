#include "Hxditr.hpp"
#include <cassert>
#include <exception>
#include <string>

HX::SwapBuffers::SwapBuffers(int32_t size) noexcept :
    Size(std::move(size)) {

    this->Front = reinterpret_cast<Cell*>(malloc(Size * sizeof(Cell)));
    this->Back = reinterpret_cast<Cell*>(malloc(Size * sizeof(Cell)));

    assert(this->Front != nullptr);
    assert(this->Back  != nullptr);

    for (int32_t i = 0; i < Size; ++i) {
        HX_GET_CHAR(this->Front[i]) = ' ';
        HX_GET_CHAR(this->Back[i]) = ' ';
    }
}

HX::SwapBuffers::~SwapBuffers() noexcept {
    free(this->Front);
    free(this->Back);
}

void HX::ConsoleOut::Update() {
    // Get current console dimensions
    static Vec2<uint32_t> oldDim = {};
    HX_GET_CONSOLE_DIM(m_CurDim);
    HX_DBG_PRT_B("Current terminal width and height: W = ");
    HX_DBG_PRT_I(m_CurDim.x);
    HX_DBG_PRT_I(" H = ");
    HX_DBG_PRT_E(m_CurDim.y);

    // If they aren't the same then
    // update every element
    if (oldDim != m_CurDim) {
        oldDim = m_CurDim;

        for (size_t i = 0; i < m_Ui.Size(); ++i) {
            if (!m_Ui[i]->IsPercent) {
                continue;
            }

            m_Ui[i]->Dim.percent.x = m_CurDim.x * m_Ui[i]->Dim.percent.x;
            m_Ui[i]->Dim.percent.y = m_CurDim.y * m_Ui[i]->Dim.percent.y;
        }
    }
}

void HX::Ui::Add(std::shared_ptr<HX::UiElement> ue){
    for (auto& i : *this ) {
        if (ue->ElementIndex == i->ElementIndex) {
            HX_DBG_PRT_B("Warrning element with index ");
            HX_DBG_PRT_I(HX_STR(ue->ElementIndex));
            HX_DBG_PRT_E(" already exists changing index to the last one");
            
            HX_DBG_PRT_B("Last avalible index is: ");
            HX_DBG_PRT_I(HX_STR(this->GetLastAvaliableIndex()));
            HX_DBG_PRT_E("");

            ue->ElementIndex = this->GetLastAvaliableIndex();
        }
    }

    this->push_back(ue);
}


void HX::ConsoleOut::Clear() {
#ifdef __GNUC__
    system("clear");
#endif
}

void HX::ConsoleOut::Paint() {

    for (size_t i = 0; i < m_Ui.Size(); ++i) {
        auto myWidth = m_Ui[i]->Dim.cells.x;
        auto myHeight = m_Ui[i]->Dim.cells.y;

        if (!m_Ui[i]->Target) {
            continue;
        }
        
        if (m_Ui[i]->IsPercent) {
            continue;
        }
        
        for (uint32_t k = 0; k < myHeight; ++k) {
            for (uint32_t j = 0; j < myWidth; ++j) {
                HX_GET_CHAR(m_Outputs.Back[k * m_CurDim.x + j + 1]) = 'A';
            }
        }

    }
    for (uint32_t k = 0; k < m_CurDim.y; ++k) {
         HX_GET_CHAR(m_Outputs.Back[k * m_CurDim.x + 1]) = std::to_string(k)[0];
    }
    for (uint32_t k = 0; k < m_CurDim.x; ++k) {
         HX_GET_CHAR(m_Outputs.Back[k]) = std::to_string(k)[0];
    }

    const uint32_t lastIndx = m_CurDim.x;
    for (uint32_t i = 0; i < m_CurDim.y; ++i) {
        HX_GET_CHAR(m_Outputs.Back[(i + 1) * lastIndx - 1]) = 'S';
        HX_GET_CHAR(m_Outputs.Back[(i + 0) * lastIndx]) = '\n';
    }
    m_Outputs.Back[m_CurDim.x * m_CurDim.y] = '\0';

    std::cout << m_Outputs.Back;
    m_Outputs.Swap();
}

