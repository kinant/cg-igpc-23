#pragma once
#include <conio.h>

namespace Input 
{
    constexpr char KEY_BINDING_UW = 'W';
    constexpr char KEY_BINDING_LW = 'w';
    constexpr char KEY_BINDING_UA = 'A';
    constexpr char KEY_BINDING_LA = 'a';
    constexpr char KEY_BINDING_US = 'S';
    constexpr char KEY_BINDING_LS = 's';
    constexpr char KEY_BINDING_UD = 'D';
    constexpr char KEY_BINDING_LD = 'd';

    enum class EInput : char
    {
        Up,
        Down,
        Left,
        Right,
        None
    };

    class UserInput
    {
    public:
        static EInput GetUserInput();
    };
}

