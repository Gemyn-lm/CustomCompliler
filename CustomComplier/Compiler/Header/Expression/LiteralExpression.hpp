#pragma once
#include "Expression.hpp"


struct Compound_Statement;

struct Literal_Expression : Expression
{
	enum class LiteralType
	{
		L_IDEN,
		L_NUM,
		L_STR,
		L_TRUE,
		L_FALSE
	};
	LiteralType lit;

	union
	{
		Token* identifier;
		Token* numeric;
		Token* str;
	};

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
	//VirtualType* EvaluateType(Compiler* compiler) override;
};