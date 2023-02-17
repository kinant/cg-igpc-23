#include "Level.h"

namespace Level 
{
	int FLevel::GetIndexFromCoordinates(const FCoordinates& C, int Width)
	{
		return C.X + C.Y * Width;
	}

}