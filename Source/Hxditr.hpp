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
#include <stdexcept>

#define HX_SELECTED_MIN 1
#define HX_SELECTED_MAX 4

#define HX_UNKOWN_SIZE ((uint64_t)(-1))

#pragma region DEBUGGING
#ifdef _DEBUG
#   define HX_DBG_PRT_B(x) std::cout << "[DBG]: " << x 
#   define HX_DBG_PRT_I(x) std::cout << x 
#   define HX_DBG_PRT_E(x) std::cout << x << std::endl; 
#   define HX_DBG_PRT_N(x) std::cout << "[DBG]: " << x << std::endl
#   define HX_DBG_PRT_FE(arr, range)                                              \
    for (int i = 0; i < range; ++i) std::cout << "[DBG]: " << arr[i] << std::endl;
#   define HX_STR(x) std::to_string(x)
#else
#   define HX_DBG_PRT_B(x) 
#   define HX_DBG_PRT_I(x) 
#   define HX_DBG_PRT_E(x) 
#   define HX_DBG_PRT_N(x) 
#   define HX_DBG_PRT_FE(arr, range)                                     
#   define HX_STR(x) 
#endif // _DEBUG
#pragma endregion

namespace HX {
    typedef unsigned char Byte;

    template<typename T> 
    struct Vec2 {
        T x;
        T y;
    };

    enum MoveDirection {
        Left,
        Right,
        Down,
        Up
    };

    class ditr {
        Byte* m_pFile = nullptr;
        uint64_t m_uFileSize = HX_UNKOWN_SIZE;
 
        uint64_t m_uCurrentFilePos = 0;
       
        // Amount of selected bytes for interpretation 
        // [HX_SELECTED_MIN, HX_SELECTED_MAX]
        int32_t m_Selected = HX_SELECTED_MIN;

    public:
        ditr() = default;
        ditr(const char* szFile);
        ~ditr();

    public:
        /**
         * Move in file in set direction a set amount
         **/
        void Move(const MoveDirection& md, const uint32_t& amount);

        bool SetFile(const char* file);

    private:
        /**
         * TO DO: Write this method
         **/
        uint32_t GetCurUiWidth();
    };
}

#include "ConsoleOutput.hpp"
#include "UserInput.hpp"

#endif // HX_HXDITR_H
