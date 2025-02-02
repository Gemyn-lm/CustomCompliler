#pragma once
#include <vector>
#include "Statement/Statement.hpp"
#include "Statement/CompoundStatement.hpp"


struct Function_Def : AST_Node
{
	Token* typeSpecifier;
	Token* funcName;


	std::vector<Token*> commas;
	struct ParameterDef
	{
		Token* type;
		Token* name;
	};
	std::vector<ParameterDef> parameters;

	Compound_Statement* body;

	std::vector<AST_Node*> GetElementList() override;
	AST_Node* Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler) override;
	void Print(unsigned int depth) override;
	void GenerateInstructions(Compiler* compiler, Compound_Statement* scope) override;
};

std::vector<Function_Def*> ParseToSyntaxTree(std::vector<Token*> tokens, Compiler* compiler);
bool CheckTokenType(const std::vector<Token*>& tokens, unsigned int tokenIndex, TokenType type);
TokenType CheckTokenType(const std::vector<Token*>& tokens, unsigned int tokenIndex);
//bool CheckOperator(const std::vector<Token*>& tokens, unsigned int tokenIndex, char op);
Token* GetNextToken(const std::vector<Token*>& tokens, unsigned int* tokenIndex);

