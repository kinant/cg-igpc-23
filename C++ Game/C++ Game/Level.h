#pragma once
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

using std::ifstream;

class Level 
{
	public:
		Level();
		~Level();
		
		bool Load(string LevelName, int* PlayerX, int* PlayerY);
		void Draw(int X, int Y) const;

		bool IsSpace(int X, int Y) const;
		bool IsDoor(int X, int Y) const;
		bool IsKey(int X, int Y) const;
		bool IsGoal(int X, int Y) const;

		void PickupKey(int X, int Y);
		void OpenDoor(int X, int Y);

		int GetHeight() const { return m_Height; }
		int GetWidth() const { return m_Width; }

		static constexpr char WAL = (char)219;
		static constexpr char KEY = (char)232;
		static constexpr char DOR = (char)179;
		static constexpr char GOL = (char)36;

	private:
		char* m_pLevelData;
		int m_Height;
		int m_Width;

		bool Convert(int* PlayerX, int* PlayerY);
		int GetIndexFromCoordinates(int X, int Y) const;
};