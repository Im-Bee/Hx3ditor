#ifndef HX_HXDITR_H
#define HX_HXDITR_H

#ifdef _WIN32
#   include <Windows.h>
#elif __GNUC__
#   include <termios.h>
#endif // _WIN#2


#include <iostream>
#include <fstream>
#include <memory>
#include <cstring>

namespace HX {
    class ditr {
    public:
        void Test() {};

    };
}

#include "ConsoleOutput.hpp"
#include "UserInput.hpp"

#endif // HX_HXDITR_H
