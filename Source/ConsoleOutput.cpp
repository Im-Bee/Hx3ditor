#include "Hxditr.hpp"
#include <cassert>

HX::SwapBuffers::SwapBuffers(int32_t size) noexcept :
    Size(std::move(size)) {

    this->Front = reinterpret_cast<Cell*>(malloc(Size * sizeof(Cell)));
    this->Back = reinterpret_cast<Cell*>(malloc(Size * sizeof(Cell)));

    assert(this->Front != nullptr);
    assert(this->Back  != nullptr);

    for (int32_t i = 0; i < Size; ++i) {
        GET_CHAR(this->Front[i]) = ' ';
        GET_CHAR(this->Back[i]) = ' ';
    }
}

HX::SwapBuffers::~SwapBuffers() noexcept {
    free(this->Front);
    free(this->Back);
}

void HX::ConsoleOut::Update() {
    // Get current console dimensions
    
    // If they aren't the same then
    // update every element

    // 
}

void HX::ConsoleOut::Clear() {
}

void HX::ConsoleOut::Paint() {
}

