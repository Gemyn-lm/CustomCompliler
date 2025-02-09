#pragma once
#include "CompoundStatement.hpp"
#include "Expression/Expression.hpp"


struct While_Statement : Statement
{
	Token* whileKeyword;
	Token* par_l;
	Expression* expression;
	Token* par_r;
	Compound_Statement* body;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};