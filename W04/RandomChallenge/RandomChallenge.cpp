#include <iostream>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;

int RandomUntilSelectedNumber_Recursively(int MinRange, int MaxRange, int SelectedNumber)
{
	int RandNum = MinRange + (rand() % (MaxRange - MinRange + 1));

	if (RandNum == SelectedNumber) 
	{
		return 1;
	}
	else 
	{
		return 1 + RandomUntilSelectedNumber_Recursively(MinRange, MaxRange, SelectedNumber);
	}
}

int RandomUntilSelectedNumber_NonRecursively(int MinRange, int MaxRange, int SelectedNumber)
{
	int Count = 1;

	while ((MinRange + (rand() % (MaxRange - MinRange + 1)) != SelectedNumber))
	{
		Count++;
	}

	return Count;
}

int main()
{
	int MinRange = 1;
	int MaxRange = 100;
	int SelectedNumber = 0;

	cout << "Enter number between 1 and 100: " << endl;
	cin >> SelectedNumber;

	if (SelectedNumber >= 1 && SelectedNumber <= 100)
	{
		srand((unsigned)time(0));

		int Count = RandomUntilSelectedNumber_Recursively(MinRange, MaxRange, SelectedNumber);

		cout << "It took " << Count << " iterations to recursive function to randomly pick selected number " << SelectedNumber << endl;

		Count = RandomUntilSelectedNumber_NonRecursively(MinRange, MaxRange, SelectedNumber);

		cout << "It took " << Count << " iterations to non recursive function to randomly pick selected number " << SelectedNumber << endl;

	}

	system("PAUSE");
}