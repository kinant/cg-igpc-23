#include <iostream>

using std::cout;
using std::cin;
using std::endl;

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;


void GetLevelDimensions(int& Width, int& Height);
void DisplayLevel(char* pLevel, const int Width, const int Height);
int GetIndexFromXY(const int X, const int Y, const int Width);

void DisplayTopBorder(const int Width);
void DisplayBottomBorder(const int Width);
void DisplayLeftBorder();
void DisplayRightBorder();

int main()
{
	int LevelWidth;
	int LevelHeight;

	GetLevelDimensions(LevelWidth, LevelHeight);

	char* pLevel = new char[LevelWidth * LevelHeight];
	
	for (int i = 0; i < LevelWidth * LevelHeight; i++) 
	{
		pLevel[i] = ' ';
	}

	DisplayLevel(pLevel, LevelWidth, LevelHeight);

	delete[] pLevel;
	pLevel = nullptr;
}

void GetLevelDimensions(int& Width, int& Height)
{
	cout << "Enter the width of your level: ";
	cin >> Width;

	cout << "Enter the height of your level: ";
	cin >> Height;
}

void DisplayLevel(char* pLevel, const int Width, const int Height)
{
	DisplayTopBorder(Width);

	for (int Y = 0; Y < Height; Y++) 
	{
		DisplayLeftBorder();

		for(int X = 0; X < Width; X++) 
		{
			const int Index = GetIndexFromXY(X, Y, Width);
			cout << pLevel[Index];
		}

		DisplayRightBorder();

	}


	DisplayBottomBorder(Width);
}

void DisplayTopBorder(const int Width) 
{
	cout << kTopLeftBorder;
	
	for (int i = 0; i < Width; i++) 
	{
		cout << kHorizontalBorder;
	}

	cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(const int Width) 
{
	cout << kBottomLeftBorder;

	for (int i = 0; i < Width; i++)
	{
		cout << kHorizontalBorder;
	}

	cout << kBottomRightBorder << endl;
}

void DisplayLeftBorder() 
{
	cout << kVerticalBorder;
}

void DisplayRightBorder() 
{
	cout << kVerticalBorder << endl;
}

int GetIndexFromXY(const int X, const int Y, const int Width) 
{
	return X + Y * Width;
}