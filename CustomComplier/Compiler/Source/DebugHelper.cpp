#include "DebugHelper.hpp"
#include <iostream>

void PrintDebug(BinaryOperationType type)
{
	std::cout << BinaryOperationTypeDebug[type];
}

void PrintDebug(UnaryOperationType type)
{
	std::cout << UnaryOperationTypeDebug[type];
}
