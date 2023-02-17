#include "UserInput.h"

namespace Input 
{
    EInput UserInput::GetUserInput()
    {
        char CharInput = _getch();

        switch (CharInput)
        {
        case KEY_BINDING_UW:
        case KEY_BINDING_LW:
        {
            return EInput::Up;
        }
        case KEY_BINDING_US:
        case KEY_BINDING_LS:
        {
            return EInput::Down;
        }
        case KEY_BINDING_UA:
        case KEY_BINDING_LA:
        {
            return EInput::Left;
        }
        case KEY_BINDING_UD:
        case KEY_BINDING_LD:
        {
            return EInput::Right;
        }
        default:
            return EInput::None;
            break;
        }
    }
}
