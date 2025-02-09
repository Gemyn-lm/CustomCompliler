#include "Statement/ReturnStatement.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
//#include "Instruction.hpp"
#include <iostream>



std::vector<AST_Node*> Return_Statement::GetElementList()
{
	return std::vector<AST_Node*>({ expression });
}

AST_Node* Return_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	// First token have been verified

	returnKeyword = GetNextToken(tokens, tokenIndex);

	expression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!expression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::SEMICOLON))
		semicolon = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}

void Return_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "[Return Statement]"
		<< '\n' << tabs << "->\tExpression : ";
	expression->Print(depth + 1);

}

void Return_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*AST_Node::GenerateInstructions(compiler, scope);
	compiler->AddInstruction(new Return_Instruction(0));*/
}
