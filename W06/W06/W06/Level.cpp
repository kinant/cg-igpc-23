#include "Level.h"

namespace Level 
{
	int FLevel::GetIndexFromCoordinates(const FCoordinates& C, int Width)
	{
		return C.X + C.Y * Width;
	}

	void FLevel::DrawLevel(const FLevel& Level)
	{
        system("CLS");

        for (int y = 0; y < Level.Dimensions.Height; y++)
        {
            for (int x = 0; x < Level.Dimensions.Width; x++)
            {
                cout << Level.Map[Level.GetIndexFromCoordinates({ x, y }, Level.Dimensions.Width)];
            }
            cout << endl;
        }
	}
}