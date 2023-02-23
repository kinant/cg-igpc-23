#pragma once
#include "APlayer.h"
#include "Level.h"

class Game
{
	public:
		Game(APlayer* Player, Level::FLevel* Level);
		void UpdatePlayerPosition();
		void DrawGame();
		bool IsGameDone() const;
	private:
		APlayer* MPlayer;
		Level::FLevel* MLevel;
		void DrawPlayerPosition();
};