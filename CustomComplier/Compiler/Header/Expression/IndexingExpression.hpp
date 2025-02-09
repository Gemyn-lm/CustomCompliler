#pragma once
#include "IndexingExpression.hpp"
#include "Expression.hpp"

struct Indexing_Expression : Expression
{
	Indexing_Expression(Expression* _varPtr)
		: varPtr(_varPtr), bracket_l(nullptr), indexExpression(nullptr), bracket_r(nullptr) {
	}

	Expression* varPtr;
	Token* bracket_l;
	Expression* indexExpression;
	Token* bracket_r;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
};