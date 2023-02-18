#include "UserInput.h"

namespace Input 
{
    EInput UserInput::GetUserInput()
    {
        if (IsKeyDown(KEY_W)) 
        {
            return EInput::Up;
        }
        else if (IsKeyDown(KEY_S)) 
        {
            return EInput::Down;
        }
        else if (IsKeyDown(KEY_A))
        {
            return EInput::Left;
        }
        else if (IsKeyDown(KEY_D))
        {
            return EInput::Right;
        }

        return EInput::None;
    }
}
