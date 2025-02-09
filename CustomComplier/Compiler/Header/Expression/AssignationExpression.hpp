#pragma once
#include "Compiler.hpp"
#include "Expression/Expression.hpp"

struct Statement;
struct Compound_Statement;

struct Assignation_Expression : Expression
{
	Assignation_Expression(Expression* _expression_L)
		: expression_L(_expression_L), op(nullptr), expression_R(nullptr) {
	}

	Assignation_Expression(Expression* _expression_L, Token* _op, Expression* _expression_R)
		: expression_L(_expression_L), op(_op), expression_R(_expression_R) {
	}

	Expression* expression_L;
	Token* op;
	Expression* expression_R;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override { return nullptr; };
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;

	//VirtualType* EvaluateType(Compiler* compiler) override;
};