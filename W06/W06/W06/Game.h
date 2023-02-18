#pragma once
#include "APlayer.h"
#include "Level.h"
#include "UserInput.h"
#include "raylib.h"

using Input::UserInput;

constexpr static int MAP_TILE_SIZE = 32;         // Tiles size 32x32 pixels
constexpr static int PLAYER_SIZE = 32;         // Player size

class Game
{
	public:
		Game(ACursor* Player, Level::FLevel* Level);
		void UpdatePlayerPosition();
		void Render();
		bool IsGameDone() const;
	private:
		ACursor* MPlayer;
		Level::FLevel* MLevel;

		Color CWalls{ 128, 128, 128, 160 };
		Color CDoor{ 100, 100, 100, 255 };
		Color CKey{ 0, 255, 0, 255 };
		Color CGoal{ 0, 0, 255, 255 };

		void DrawLevel();
		void DrawPlayer();
};