#include "Statement/VarDefStatement.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Statement/CompoundStatement.hpp"
#include <iostream>


std::vector<AST_Node*> Var_Def_Statement::GetElementList()
{
	return std::vector<AST_Node*>({ expression });
}


AST_Node* Var_Def_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	// First  two tokens have been verified

	typeSpecifier = GetNextToken(tokens, tokenIndex);
	varName = GetNextToken(tokens, tokenIndex);

	if (CheckTokenType(tokens, *tokenIndex, TokenType::EQUAL))
		equal = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	expression = GetNextExpression(tokens, tokenIndex, compiler);
	if (!expression) return nullptr;

	if (CheckTokenType(tokens, *tokenIndex, TokenType::SEMICOLON))
		semicolon = GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}


void Var_Def_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "[Variable Definition]\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t\"Type\" : " << "\"" << typeSpecifier->value << "\","
		<< '\n' << tabs << "\t\"Name\" : " << "\"" << varName->value << "\","
		<< '\n' << tabs << "\t\"Expression : ";
	expression->Print(depth + 1);
	std::cout << "\n" << tabs << "}";
}


void Var_Def_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	AST_Node::GenerateInstructions(compiler, scope);

	int memoryPointer = compiler->AddVariableSymbol(varName->value, scope/*, compiler->TryGetTypeSymbol(typeSpecifier->value)*/);

	compiler->AddInstruction(new Pop_Instruction(memoryPointer + 4));
}
