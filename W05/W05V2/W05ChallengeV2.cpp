/*
	CGSpectrum IGPC Cert T1
	Week 05 Challenge 1 v2 - Find the greatest product of five consecutive digits in the 1000-digit number.
	By: Kinan Turman. 2023

	Used the following resources:
	- https://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
	- https://cplusplus.com/reference/string/string/substr/
	- https://artificial-mind.net/blog/2020/09/12/recursive-lambdas
*/
#include<iostream>
#include <stdlib.h>
#include <assert.h>

using std::cout;
using std::endl;
using std::string;

// macro used to aid in conversion from char to int
// we have subtract '0' or 48
#define CharToInt(chr) (chr-'0')

// number of consecutive integers to get product of
#define INTS_TO_CALC 5

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

int main()
{
	int Counter = 0;
	int Max = 0;

	string MaxSequence;

	// recursive lambda function get the product of the digits in the counter
	// https://artificial-mind.net/blog/2020/09/12/recursive-lambdas
	auto Product = [](string Sequence, auto&& Product) -> int
	{
		if (Sequence.length() == 0) return 1;
		// multiply 1st element of the string * recursively call the lambda funtion with the string reduced by that element
		return CharToInt(Sequence[0]) * Product(Sequence.substr(1, Sequence.length() - 1), Product);
	};

	// iterate while getting the next substring with length of INTS_TO_CALC (for this program it is 5, but can be changed)
	// https://cplusplus.com/reference/string/string/substr/
	//
	while (((string)kDigits).substr(Counter, INTS_TO_CALC).length() == INTS_TO_CALC)
	{
		string Sequence = ((string)kDigits).substr(Counter, INTS_TO_CALC);

		int Result = Product(Sequence, Product);

		// check if new max
		if (Max < Result)
		{
			Max = Result;

			// get the string of the sequence of 5 digits that is the new max
			// just using it as informative display in results output
			MaxSequence = Sequence;
		}
		Counter++;
	}

	cout << "MAX PRODUCT OF SEQUENCE OF " << INTS_TO_CALC << " DIGITS(" << MaxSequence << ") IS: " << Max << endl;
}