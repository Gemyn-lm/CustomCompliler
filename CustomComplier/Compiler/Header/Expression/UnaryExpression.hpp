#pragma once
#include "Expression.hpp"

struct Statement;
struct Compound_Statement;

struct UnaryExpression : Expression
{
	UnaryExpression(Expression* _expression, Token* _op)
		: expression(_expression), op(_op) {
	}

	Expression* expression;
	Token* op;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override { return nullptr; };
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};