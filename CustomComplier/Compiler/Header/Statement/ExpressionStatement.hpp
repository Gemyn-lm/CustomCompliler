#pragma once
#include "Statement.hpp"


struct Expression_Statement : Statement
{
	Expression* expression;
	Token* semicolon;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
	virtual void Print(unsigned int depth);
};