#include "Statement/IfStatement.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
//#include "Instruction.hpp"
#include <iostream>


std::vector<AST_Node*> If_Statement::GetElementList()
{
	return std::vector<AST_Node*>({ expression, body });
}

AST_Node* If_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	// First token have been verified

	ifKeyword = GetNextToken(tokens, tokenIndex);

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

void If_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "[If Statement]\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t\"Expression : ";
	expression->Print(depth + 1);
	std::cout << ",";

	std::cout << '\n' << tabs << "\t\"Body\ : ";
	body->Print(depth + 1);
	std::cout << "\n" << tabs << "}";
}

void If_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*Jump_Instruction* jump = new Jump_Instruction(true, 0);

	expression->GenerateInstructions(compiler, scope);
	compiler->AddInstruction(jump);
	body->GenerateInstructions(compiler, scope);

	jump->destination = compiler->GetInstructions().size();*/
}
