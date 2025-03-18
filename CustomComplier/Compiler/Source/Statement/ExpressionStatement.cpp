#include "Statement/ExpressionStatement.hpp"
#include "Parser.hpp"
#include "Expression/FuncCall.hpp"
#include <iostream>


std::vector<AST_Node*> Expression_Statement::GetElementList()
{
	return std::vector<AST_Node*>({ expression });
}

AST_Node* Expression_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	expression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!expression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::SEMICOLON))
		semicolon = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}

void Expression_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	AST_Node::GenerateInstructions(compiler, scope);
	if (typeid(*expression) == typeid(FuncCall_Expression))
	{
		compiler->AddInstruction(new Pop_Instruction(0));
	}
}

void Expression_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');

	std::cout << "\"Expression Statement\":" << "\n" << tabs << "{"
		<< '\n' << tabs << '\t';
	expression->Print(depth + 1);
	std::cout << "\n" << tabs << "}";
}