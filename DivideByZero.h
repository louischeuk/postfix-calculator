#ifndef DIVIDEBYZERO_H
#define DIVIDEBYZERO_H
#include <stdexcept>

class DivideByZeroException : public std::runtime_error {
public:
	DivideByZeroException() :
			runtime_error("Math error: Attempted to divide by Zero\n") {}
};

#endif