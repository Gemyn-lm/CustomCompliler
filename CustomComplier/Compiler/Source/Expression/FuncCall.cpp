#include <iostream>
#include "Expression/FuncCall.hpp"
#include "Expression/Expression.hpp"
#include "Expression/LiteralExpression.hpp"
#include "Instruction.hpp"

std::vector<AST_Node*> FuncCall_Expression::GetElementList()
{
	std::vector<AST_Node*> result({ funcPtr });
	for (Expression* expression : argumentList)
	{
		result.push_back(expression);
	}
	return result;
}

AST_Node* FuncCall_Expression::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	GetNextToken(tokens, tokenIndex);
	while (!CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_R))
	{
		

		argumentList.push_back(GetNextExpression(tokens, tokenIndex, compiler));
		if (CheckTokenType(tokens, *tokenIndex, TokenType::COMMA))
			GetNextToken(tokens, tokenIndex);
		else
			break;
	}

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

	int i = 0;
	for (Expression* param : argumentList)
	{
		std::cout << "\n" << tabs << "\t\"Param " << i << ":"
			<< "\n" << tabs << "\t{\n" << tabs;
			
		param->Print(depth + 3);
			std::cout << "\n" << tabs << "\t}";
		i++;
	}

	std::cout << "\n" << tabs << "}";
}

void FuncCall_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	if (typeid(*funcPtr) != typeid(Literal_Expression) || ((Literal_Expression*)funcPtr)->lit != Literal_Expression::LiteralType::L_IDEN)
	{
		std::cerr << "The expression should be an lvalue (referencing an object).";
		return;
	}

	int i = 4 + argumentList.size() * 4;
	for (Expression* param : argumentList)
	{
		param->GenerateInstructions(compiler, scope);
		compiler->AddInstruction(new Pop_Instruction(-i));
		i -= 4;
	}

	int funcIndex = compiler->TryGetFuncSymbol(((Literal_Expression*)funcPtr)->identifier->value)->functionIndex;
	compiler->AddInstruction(new Call_Instruction(funcIndex));
}

