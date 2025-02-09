#include "Statement/WhileStatement.hpp"
#include "Compiler.hpp"
//#include "Instruction.hpp"
#include "Parser.hpp"
#include <iostream>


std::vector<AST_Node*> While_Statement::GetElementList()
{
	return std::vector<AST_Node*>({ expression });
}

AST_Node* While_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	// First token have been verified

	whileKeyword = GetNextToken(tokens, tokenIndex);

	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_L))
		par_l = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	expression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!expression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_R))
		par_r = GetNextToken(tokens, tokenIndex);
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

void While_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "[While Statement]"
		<< '\n' << tabs << "->\tExpression : ";
	expression->Print(depth + 1);

	std::cout << '\n' << tabs << "->\tBody : ";
	body->Print(depth + 1);
}

void While_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*int whileStart = compiler->GetInstructions().size();
	Jump_Instruction* jumpToEnd = new Jump_Instruction(true, 0);

	expression->GenerateInstructions(compiler, scope);
	compiler->AddInstruction(jumpToEnd);
	body->GenerateInstructions(compiler, scope);

	jumpToEnd->destination = compiler->GetInstructions().size() + 1;
	compiler->AddInstruction(new Jump_Instruction(false, whileStart));*/
}
