/*
	CGSpectrum IGPC Cert T1
	Week 05 Challenge 1 v3 - Find the greatest product of five consecutive digits in the 1000-digit number.
	By: Kinan Turman. 2023
*/
#include <iostream>

using std::string;
using std::cout;
using std::endl;

const char* kDigits = "\
73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450";

#define SEQ_LEN 5
#define CharToInt(chr) (chr - '0')

void GetNextValidIteration(int& ValidIterationIndex, int& Product, const int& Length);

int main()
{
	// to keep track of index of the first valid iteration (ie. one that has a product != 0)
	int ValidIterationIndex = 0;
	int Product = 1;
	int Length = strlen(kDigits);
	
	// get the first valid iteration, to be used (possibly) for future iterations
	GetNextValidIteration(ValidIterationIndex, Product, Length);
	int Max = Product;

	// We have found the first valid iteration, now we continue with the rest of the digits
	for (int i = ValidIterationIndex; i < Length; i++) 
	{
		if (i + SEQ_LEN >= Length) 
		{
			break;
		}

		int FirstDigit = CharToInt(kDigits[i]);
		int NextDigit = CharToInt(kDigits[i + SEQ_LEN]);

		// if we hit a first digit with 0, we skip to the next iteration...
		if (FirstDigit == 0) 
		{
			GetNextValidIteration(i, Product, Length);
			i--;

			if (Max < Product) 
			{
				Max = Product;
			}
			continue;
		}
		Product /= FirstDigit;
		Product *= NextDigit;

		if (Max < Product) 
		{
			Max = Product;
		}
	}

	cout << "MAX PRODUCT OF " << SEQ_LEN <<" CONSECUTIVE DIGITS : " << Max << endl;
}

void GetNextValidIteration(int& ValidIterationIndex, int& Product, const int& Length)
{
	bool bValidIterationFound = false;
	int DigitsMultiplied = 0;

	// Get the 1st valid iteration
	while (!bValidIterationFound)
	{
		DigitsMultiplied = 0;
		Product = 1;

		if (SEQ_LEN + ValidIterationIndex >= Length)
		{
			Product = 0;
		}
		for (int i = ValidIterationIndex; i < SEQ_LEN + ValidIterationIndex; i++)
		{
			int Digit = CharToInt(kDigits[i]);

			if (Digit == 0)
			{
				ValidIterationIndex++;
				break;
			}
			Product *= Digit;
			DigitsMultiplied++;
		}
		if (DigitsMultiplied == SEQ_LEN)
		{
			bValidIterationFound = true;
		}
	}
}