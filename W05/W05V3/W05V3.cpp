/*
	CGSpectrum IGPC Cert T1
	Week 05 Challenge 1 v3 - Find the greatest product of five consecutive digits in the 1000-digit number.
	By: Kinan Turman. 2023
*/
#include <iostream>

using std::string;
using std::cout;
using std::endl;

// uncomment, and comment the other one, to test extreme cases
//const char* kDigits = "\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000005555500000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000009979900000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000000000000000000000000\
//00000000000000000000000000000099999000000000000000\
//00000000000000000000000000000000000000000000000000";

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

		// get the first digit of the "previous" iteration
		int FirstDigit = CharToInt(kDigits[i]);

		// get the nexy digit of the next iteration
		int NextDigit = CharToInt(kDigits[i + SEQ_LEN]);

		// if we hit a first digit with 0, we skip to the next iteration
		if (FirstDigit == 0) 
		{
			GetNextValidIteration(i, Product, Length);
			
			// we (possibliy) incremented i in function, the index returned hast to be 
			// subtracted by 1, since the loop condition will add one again. 
			i--;

			if (Max < Product) 
			{
				Max = Product;
			}
			// continue on to next iteration skipping as many iterations as given by the new i value
			continue;
		}
		// iteration not skipped

		// divide the product by the first digit of the "previous" iteration
		Product /= FirstDigit;

		// multiply by the next digit of the next iteration to get the new product
		Product *= NextDigit;

		if (Max < Product) 
		{
			Max = Product;
		}
	}

	cout << "MAX PRODUCT OF " << SEQ_LEN <<" CONSECUTIVE DIGITS : " << Max << endl;
}

/*
* Function - GetNextValidIteration
* Loops through a number of digits, until a valid sequence is found.
* A valid sequence is defined as one in which all its N digits, given by SEQ_LEN,
* can be multiplied without resulting in a total product.
* 
* @param -	ValidIterationIndex: Reference to the index that will be used to start searching.
*			Eventually it get's overriten to the index of the first digit of a valid iteration sequence.
*
* @param -	Product: reference to the product. Rather than return a product in this function, I
*			decided to just pass a reference. Once the function is complete, the Product should be
*			set to the valid iteration Product, or to 0 if none found. 
* 
* @param - Length: just a reference to the length of the array of digits
*/

void GetNextValidIteration(int& ValidIterationIndex, int& Product, const int& Length)
{
	// flag for checking if a valid input found
	bool bValidIterationFound = false;
	
	// we will check that SEQ_LEN digits were multiplied in order to make the above true
	int DigitsMultiplied = 0;

	// loop until we get a valid iteration
	while (!bValidIterationFound)
	{
		// reset
		DigitsMultiplied = 0;
		Product = 1;

		// if we have reached the the max number of digits in the array, or above, we break out.
		if (SEQ_LEN + ValidIterationIndex >= Length)
		{
			Product = 0;
			break;
		}

		// iterate over the sequence of digits
		for (int i = ValidIterationIndex; i < SEQ_LEN + ValidIterationIndex; i++)
		{
			int Digit = CharToInt(kDigits[i]);

			// if any digit in the sequence is 0, then no valid iteration is found, we skip to the next
			if (Digit == 0)
			{
				ValidIterationIndex++;
				break;
			}
			 
			Product *= Digit;
			DigitsMultiplied++;
		}

		// if we multiplied SEQ_LEN number of digits, then we did not have a single 0 in the sequence, valid iteration sequence found!
		if (DigitsMultiplied == SEQ_LEN)
		{
			bValidIterationFound = true;
		}
	}
}