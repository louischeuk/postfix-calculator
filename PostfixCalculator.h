#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <iostream>
#include <cctype>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <string>
#include <stack>

const static char *ops[] = {"+", "-", "*", "/", "^", "sqrt", "log", "abs"};
static std::vector<const std::string> v_ops;

const static std::string exitKeyWord = "exit";
const static std::string opLOG = "log"; /* natural log */
const static std::string opSQRT = "sqrt"; 
const static std::string opABS = "abs";

/* -------------- functions definition -------------- */

/* primary function */
double PostfixCalculator(const std::string &exp);

/* for operators "log", "abs", "sqrt" */
double Calculate(const std::string &op2, const double& o1, const double& o2);
 
/* for operators "+", "-", "*", "/", "^" */
double Calculate(const std::string &op, const double& o);

bool IsOperator(char c);

/* check if the ch is the start of the exit key word */
bool IsStartOfExitKeyWorld(char c);

bool IsExitKeyWorld(const std::string &expr, int &pos);

bool IsOperandInvalid(char c);

/* check if the ch is either "+" or "-" */
bool IsSign(char c);

bool IsSignValid(const std::string &expr, int i);

double GetOperand(const std::string &expr, int &i, bool decimal = false);

bool IsDecimalValid(const std::string &expr, int i);

void handleDivideByZero(double operand);

/* check if the word is "log" */
bool IsLog(const std::string &expr, int &pos);

/* check if the word is "sqrt" */
bool IsSqrt(const std::string &expr, int &pos);

/* check if the word is "abs" */
bool IsAbs(const std::string &expr, int &pos);

/* helper function delegated from IsSqrt(), Islog(), IsAbs() */
bool IsOperatorCorrect(const std::string &expr, int &pos, std::string op);

bool isCharMatchStartOfOperator(const char &c);

/* push operators from char[] to vector for easier list maniplualtion */
void AddOpsToVector();

#endif