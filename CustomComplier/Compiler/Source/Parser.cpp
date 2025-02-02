#include "Parser.hpp"


std::vector<Function_Def*> ParseToSyntaxTree(std::vector<Token*> tokens, Compiler* compiler)
{
	std::vector<Function_Def*> result;
	unsigned int tokenIndex = 0;

	while (CheckTokenType(tokens, tokenIndex, TokenType::IDENTIFIER))
	{
		Function_Def* func = new Function_Def();
		func->Parse(tokens, &tokenIndex, compiler);
		result.push_back(func);
	}

	return result;
}

bool CheckTokenType(const std::vector<Token*>& tokens, unsigned int tokenIndex, TokenType type)
{
	return tokens[tokenIndex]->type == type;
}

TokenType CheckTokenType(const std::vector<Token*>& tokens, unsigned int tokenIndex)
{
	return tokens[tokenIndex]->type;
}

//bool CheckOperator(const std::vector<Token*>& tokens, unsigned int tokenIndex, char op)
//{
//	return tokens[tokenIndex]->value == op;
//}

Token* GetNextToken(const std::vector<Token*>& tokens, unsigned int* tokenIndex)
{
	(*tokenIndex)++;
	return tokens[*tokenIndex - 1];
}

AST_Node* Function_Def::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	if (CheckTokenType(tokens, *tokenIndex, TokenType::IDENTIFIER))
		typeSpecifier = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::IDENTIFIER))
		funcName = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_L))
		GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_R))
		GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::CURLY_L))
	{
		body = new Compound_Statement();
		if (!body->Parse(tokens, tokenIndex, compiler))
			return nullptr;
	}
	else
	{
		return nullptr;
	}

	return this;
}
