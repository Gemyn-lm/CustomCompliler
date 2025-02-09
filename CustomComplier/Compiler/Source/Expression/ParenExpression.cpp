#include "Expression/ParenExpression.hpp"
#include "Parser.hpp"
#include <iostream>

std::vector<AST_Node*> Paren_Expression::GetElementList()
{
	return std::vector<AST_Node*>({ expression });
}

AST_Node* Paren_Expression::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	par_l = GetNextToken(tokens, tokenIndex);

	expression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!expression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_R))
		par_r = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}

void Paren_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Parenthesis Expression\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t";
	expression->Print(depth + 1);
	std::cout << "\n" << tabs << "}";
}

//VirtualType* Paren_Expression::EvaluateType(Compiler* compiler)
//{
//	return expression->EvaluateType(compiler);
//}
