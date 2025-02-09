#pragma once
#include "Statement.hpp"

struct Compound_Statement;

struct Var_Def_Statement : Statement
{
	Token* typeSpecifier;
	Token* varName;
	Token* equal;
	Expression* expression;
	Token* semicolon;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};