#pragma once
#include <conio.h>
#include <Windows.h>
#include <fstream>

#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"

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
		bool DidUserQuit() { return m_bUserQuit; }

		int GetPlayerLives() { return m_Player.GetLives(); }

	private:
		static constexpr int kOpenDoorColor = 10;
		static constexpr int kClosedDoorColor = 12;
		static constexpr int kRegularColor = 7;

		static constexpr int kArrowInput = 224;
		static constexpr int kLeftArrow = 75;
		static constexpr int kRightArrow = 77;
		static constexpr int kUpArrow = 72;
		static constexpr int kDownArrow = 80;
		static constexpr int kEscapeKey = 27;


		Player m_Player;
		Level m_Level;
		bool m_bIsGameOver;
		bool m_bUserQuit;

		bool Update();
		void Draw();

		bool HandleCollision(int PlayerX, int PlayerY);
};