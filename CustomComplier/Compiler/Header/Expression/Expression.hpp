#pragma once

#include "Tokenizer.hpp"

class Compiler;
struct Compound_Statement;

struct AST_Node
{
	virtual std::vector<AST_Node*> GetElementList() = 0;
	virtual AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) = 0;
	virtual void Print(unsigned int depth) {}
	virtual void GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
	{
		for (AST_Node* node : GetElementList())
		{
			node->GenerateInstructions(compiler, scope); 
		}
	};
};

struct Expression : AST_Node
{
	//virtual VirtualType* EvaluateType(Compiler* compiler) = 0;
};

Expression* GetNextExpression(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler);
Expression* GetNextBinaryOperation(const std::vector<Token*>& tokens, unsigned int* tokenIndex, int precedence, Compiler* compiler);
Expression* GetNextPrefixOperation(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler);
Expression* GetNextFactor(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler);