#pragma once
#include "Expression.hpp"

struct Statement;
struct Compound_Statement;

struct Binary_Expression : Expression
{
	Binary_Expression(Expression* _leftExpression, Token* _op, Expression* _rightExpression)
		: leftExpression(_leftExpression), op(_op), rightExpression(_rightExpression){
	}

	Expression* leftExpression;
	Token* op;
	Expression* rightExpression;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override { return nullptr; };
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};