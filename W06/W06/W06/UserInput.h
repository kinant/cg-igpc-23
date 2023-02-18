#pragma once

#include <conio.h>
#include <raylib.h>

namespace Input 
{
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

