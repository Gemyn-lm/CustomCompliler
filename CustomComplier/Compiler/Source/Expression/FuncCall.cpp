#include <iostream>
#include "Expression/FuncCall.hpp"
#include "Expression/Expression.hpp"

std::vector<AST_Node*> FuncCall_Expression::GetElementList()
{
	return std::vector<AST_Node*>({funcPtr});
}

void FuncCall_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Function Call\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t";
	funcPtr->Print(depth + 1);

	std::cout << "\n" << tabs << "}";
}

void FuncCall_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
}

