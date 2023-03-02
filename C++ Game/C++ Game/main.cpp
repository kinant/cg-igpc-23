#include <iostream>
#include "Game.h"

using std::cout;

int main() 
{
	Game MyGame;

	if (MyGame.Load()) 
	{
		while (!MyGame.IsGameOver()) 
		{
			MyGame.Run();
		}

		if (MyGame.DidUserQuit()) 
		{
			cout << "Thanks for playing!" << endl;
		}
		else if (MyGame.GetPlayerLives() < 0) 
		{
			cout << "YOU LOSE!!!" << endl;
		}
		else 
		{
			cout << "YOU WON!!!" << endl;
			// PlayWinSound();
		}
	}
	else 
	{
		cout << "Game did not load. Terminating now!" << endl;
		return -1;
	}
}

//void PlayDoorClosedSound() 
//{
//    Beep(500, 75);
//    Beep(500, 75);
//
//}
//
//void PlayDoorOpenSound() 
//{
//    Beep(1397, 200);
//}
//
//void PlayKeyPickupSound() 
//{
//    Beep(1568, 200);
//}
//
//void PlayWinSound() 
//{
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1245, 1000);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1175, 1000);
//}
