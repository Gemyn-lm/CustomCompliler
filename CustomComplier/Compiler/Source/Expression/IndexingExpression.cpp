#include "Expression/IndexingExpression.hpp"
#include "Parser.hpp"
#include <iostream>


std::vector<AST_Node*> Indexing_Expression::GetElementList()
{
	return std::vector<AST_Node*>({ varPtr, indexExpression });
}

AST_Node* Indexing_Expression::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	bracket_l = GetNextToken(tokens, tokenIndex);

	indexExpression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!indexExpression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::BRACKET_R))
		bracket_r = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}

void Indexing_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "[Indexing Expression]"
		<< '\n' << tabs << "->\tVariable Pointer : ";
	varPtr->Print(depth + 1);

	std::cout << '\n' << tabs << "->\tIndex Expression : ";
	indexExpression->Print(depth + 1);
}