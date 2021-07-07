#include "PostfixCalculator.h"
#include <iostream>
#include <cmath>
#include <cassert>


int main() {

	// push operators from char[] to vector for easier list maniplualtion
	AddOpsToVector();

	// allow user input
	std::string expression;
	std::cout << "Type your postfix expression: ";
	getline(std::cin, expression);
	std::cout << "Ans: " << PostfixCalculator(expression) << "\n";

	/* -------------- tests for pre-made postfix expressions -------------- */

	char exp[] = "100 200 + 2 / 5 * 7 +";
	assert(PostfixCalculator(exp) == 757);

	char exp2[] = "-100 200 + 2 / 5 * 7 +";
	assert(PostfixCalculator(exp2) == 257);

	char exp3[] = "3.146 2 * 1.000 +";
	assert(PostfixCalculator(exp3) == 7.292);

	char exp4[] = ".45 .2 +";
	assert(PostfixCalculator(exp4) == 0.65);

	char exp5[] = "-100 200q";
	assert(std::isnan(PostfixCalculator(exp5)));

	char exp6[] = "exit";
	assert(std::isnan(PostfixCalculator(exp6)));

	char exp7[] = "1 2 + 3 * 6 + 2 3 + /";
	assert(PostfixCalculator(exp7) == 3);

	char exp8[] = "exi1";
	assert(std::isnan(PostfixCalculator(exp8)));

	char exp9[] = "100 0 /";
	assert(PostfixCalculator(exp9) == std::numeric_limits<double>::infinity());

	char exp10[] = "100 log";
	assert(PostfixCalculator(exp10) == log(100));

	char exp11[] = "-10 abs";
	assert(PostfixCalculator(exp11) == 10);

	char exp12[] = "3 9 sqrt + ";
	assert(PostfixCalculator(exp12) == 6);

	char exp13[] = "2 3 4 * +";
	assert(PostfixCalculator(exp13) == 14);

	char exp14[] = "-2 abs 3 4 * +";
	assert(PostfixCalculator(exp14) == 14);

	return 0;
}


