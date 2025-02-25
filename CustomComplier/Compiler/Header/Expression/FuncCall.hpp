#pragma once
#include "Compiler.hpp"
#include "Expression/Expression.hpp"

struct Statement;
struct Compound_Statement;

struct FuncCall_Expression : Expression
{
	FuncCall_Expression(Expression* _funcPtr)
		: funcPtr(_funcPtr), parenL(nullptr), parenR(nullptr) {
	}

	Expression* funcPtr;
	Token* parenL, * parenR;
	// TODO : argument list

	std::vector<AST_Node*> GetElementList() override;
	// TODO
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;

	//VirtualType* EvaluateType(Compiler* compiler) override;
};