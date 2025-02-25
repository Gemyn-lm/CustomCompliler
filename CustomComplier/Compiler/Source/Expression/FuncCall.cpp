#include <iostream>
#include "Expression/FuncCall.hpp"
#include "Expression/Expression.hpp"
#include "Expression/LiteralExpression.hpp"
#include "Instruction.hpp"

std::vector<AST_Node*> FuncCall_Expression::GetElementList()
{
	return std::vector<AST_Node*>({funcPtr});
}

AST_Node* FuncCall_Expression::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	// TODO argument parsing
	GetNextToken(tokens, tokenIndex);
	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_R))
		GetNextToken(tokens, tokenIndex);
	else
		return nullptr;

	return this;
}

void FuncCall_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Function Call\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t";
	funcPtr->Print(depth + 1);

	std::cout << "\n" << tabs << "}";
}

void FuncCall_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	if (typeid(*funcPtr) != typeid(Literal_Expression) || ((Literal_Expression*)funcPtr)->lit != Literal_Expression::LiteralType::L_IDEN)
	{
		std::cerr << "The expression should be an lvalue (referencing an object).";
		return;
	}

	int funcIndex = compiler->TryGetFuncSymbol(((Literal_Expression*)funcPtr)->identifier->value)->functionIndex;
	compiler->AddInstruction(new Call_Instruction(funcIndex));
}

