#include "PostfixCalculator.h"
#include "DivideByZero.h"
#include "Messages.h"

double PostfixCalculator(const std::string &exp) {

	std::stack<double> stack;

	// ans will return NaN if there is error
	double ans = std::numeric_limits<double>::quiet_NaN();

	for (int i = 0; i < exp.length(); i++) {		
		if (exp[i] == ' ') continue;

		if (IsOperandInvalid(exp[i])) {
			std::cout << errorMessage3 << exp[i] << std::endl;
			return ans;
		}

		// check if the operator is "log" or "abs" or "sqrt"
		if (isCharMatchStartOfOperator(exp[i])) {
			char startCh = exp[i];
			if (IsLog(exp, i) || IsAbs(exp, i) || IsSqrt(exp, i)) {
				if (stack.empty()) {
					std::cout << errorMessage1 << std::endl;
					return ans;
				}

				double o = stack.top();
				stack.pop();

				if (startCh == opLOG[0]) stack.push(Calculate(opLOG, o));
				else if (startCh == opABS[0]) stack.push(Calculate(opABS, o));
				else if (startCh == opSQRT[0]) stack.push(Calculate(opSQRT, o));
				continue;

			} else {
				std::cout << errorMessage3 << exp[i] << std::endl;
				return ans;
			}
		}

		// check if the word is the key word to exit the program
		if (IsStartOfExitKeyWorld(exp[i])) {
			if (IsExitKeyWorld(exp, i)) {
				std::cout << keyWordReceivedMessage << '\n';
			} else {
				std::cout << errorMessage3 << exp[i] << std::endl;
			}
			return ans;
		}

		// get operand (when sign is explicitly stated)
		if (IsSign(exp[i]) && IsSignValid(exp, i)) {
			double num = GetOperand(exp, ++i);
			num = exp[i] == '+' ? num : -num;
			stack.push(num);

			// get operand (if it is between abs(0 and 1))
		} else if (exp[i] == '.' && IsDecimalValid(exp, i)) {
			double num = GetOperand(exp, ++i, true);
			stack.push(num);

			// get operand
		} else if (isdigit(exp[i])) {
			double num = GetOperand(exp, i);
			stack.push(num);

			/* perform operation */
		} else if (IsOperator(exp[i])) {
			if (stack.size() >= 2) {
				double o2 = stack.top();
				stack.pop();
				double o1 = stack.top();
				stack.pop();
				double res = Calculate(std::string(1, exp[i]), o1, o2);
				stack.push(res);

			} else {
				std::cout << errorMessage1 << std::endl;
				return ans;
			}
		}
	}

	// at the end, there should only be 1 item in stack
	if (stack.size() > 1) {
		std::cout << errorMessage2 << std::endl;
		return ans;
	}

	std::cout << stack.top() << '\n';
	ans = stack.top();
	return ans;
}

bool isCharMatchStartOfOperator(const char &c) {
	return c == opLOG[0] || c == opABS[0] || c == opSQRT[0];
}

bool IsSqrt(const std::string &expr, int &pos) { return IsOperatorCorrect(expr, pos, opSQRT); }

bool IsLog(const std::string &expr, int &pos) { return IsOperatorCorrect(expr, pos, opLOG); }

bool IsAbs(const std::string &expr, int &pos) { return IsOperatorCorrect(expr, pos, opABS); }


bool IsOperatorCorrect(const std::string &expr, int &pos, std::string op) {
	int i;
	for (i = 0; i < op.length(); i++) {
		if (expr[i + pos] == op[i]) {
		} else {
			pos += i; // return the position of invalid operand
			return false;
		}
	}
	pos += i;
	return true;
}


bool IsDecimalValid(const std::string &expr, int i) {
	return IsSignValid(expr, i);
}


double GetOperand(const std::string &expr, int &i, bool decimal) {
	double num = 0;
	int exponent = decimal ? 1 : 0;

	while (isdigit(expr[i]) || (expr[i] == '.' && !decimal)) {

		if (expr[i] == '.') {
			decimal = true;
			exponent = 1;
			i++;
			continue;
		}

		if (!decimal) {
			num = num * 10 + (expr[i] - '0');
			i++;
		} else {
			num = num + (expr[i] - '0') / pow(10, exponent++);
			i++;
		}

	}
	i--;
	return num;
}

bool IsSignValid(const std::string &expr, int i) {
	return i + 1 < expr.length() && isdigit(expr[i + 1]);
}

bool IsSign(char c) {
	return c == '+' || c == '-';
}

bool IsOperandInvalid(char c) {
		return !isdigit(c)
	&& !IsSign(c)
	&& !IsStartOfExitKeyWorld(c)
	&& !isCharMatchStartOfOperator(c)
	&& !IsOperator(c)
	&& c != '.';
}

bool IsExitKeyWorld(const std::string &expr, int &pos) {
	std::string word;
	for (int i = 0; i < exitKeyWord.length(); i++) {
		if (expr[i + pos] == exitKeyWord[i]) {
			word += expr[i + pos];
		} else {
			pos += i; // return the position of invalid operand
			return false;
		}
	}
	return true;
}

bool IsStartOfExitKeyWorld(char c) { return c == exitKeyWord[0]; }

bool IsOperator(char c) {
	std::string s(1, c);
	return std::any_of(v_ops.begin(), 
											v_ops.end(), 
											[s](const auto &op) { return s == op; });
}

double Calculate(const std::string &op, const double& o1, const double& o2) {
	if (op == "+") return o1 + o2;
	if (op == "-") return o1 - o2;
	if (op == "*") return o1 * o2;
	if (op == "^") return pow(o1, o2);
	if (op == "/") { handleDivideByZero(o2); return o1 / o2; }
	return 0;
}

double Calculate(const std::string &op, const double& o) {
	if (op == "log") return log(o);
	if (op == "sqrt") return sqrt(o);
	if (op == "abs") return abs(o);
	return 0;
}

void handleDivideByZero(double operand) {
	try {
		if (operand == 0) throw DivideByZeroException();
	} catch (DivideByZeroException &e) {
		std::cout << e.what();
	}
}

void AddOpsToVector() {
	for (std::string op : ops) v_ops.push_back(op);
}
