#pragma once
#include "Tokenizer.hpp"
#include "Expression/Expression.hpp"



struct Statement : AST_Node
{

};


Statement* GetNextStatement(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler);
