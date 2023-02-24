#pragma once
#include <conio.h>
#include <Windows.h>
#include <fstream>

#include "Player.h"
#include "Level.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

class Game 
{
	public:
		Game();
		~Game();

		bool Load();
		void Run();

		bool IsGameOver();

	private:
		Player m_Player;
		Level m_Level;
		bool m_bIsGameOver;

		bool Update();
		void Draw();

		static constexpr int kOpenDoorColor = 10;
		static constexpr int kClosedDoorColor = 12;
		static constexpr int kRegularColor = 7;
};