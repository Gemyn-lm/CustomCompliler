#pragma once
#include "Expression.hpp"


struct Paren_Expression : Expression
{
	Token* par_l;
	Expression* expression;
	Token* par_r;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	//VirtualType* EvaluateType(Compiler* compiler) override;
};