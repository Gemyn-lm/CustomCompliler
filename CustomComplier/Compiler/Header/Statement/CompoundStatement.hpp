#pragma once
#include "Statement.hpp"
//#include "Semantic.h"
#include <map>
#include <string>

struct Compound_Statement : Statement
{
	Token* cur_l;
	std::vector<Statement*> statements;
	Token* cur_r;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	virtual void Print(unsigned int depth);
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};