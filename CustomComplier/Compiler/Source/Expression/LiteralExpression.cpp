#include "Expression/LiteralExpression.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Statement/CompoundStatement.hpp"
#include <iostream>


std::vector<AST_Node*> Literal_Expression::GetElementList()
{
	return std::vector<AST_Node*>();
}

AST_Node* Literal_Expression::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	if (CheckTokenType(tokens, *tokenIndex, TokenType::IDENTIFIER))
	{
		identifier = GetNextToken(tokens, tokenIndex);
		lit = LiteralType::L_IDEN;
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::NUMERIC_LITERAL))
	{
		numeric = GetNextToken(tokens, tokenIndex);
		lit = LiteralType::L_NUM;
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::STRING_LITERAL))
	{
		str = GetNextToken(tokens, tokenIndex);
		lit = LiteralType::L_STR;
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::TRUE))
	{
		str = GetNextToken(tokens, tokenIndex);
		lit = LiteralType::L_TRUE;
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::FALSE))
	{
		str = GetNextToken(tokens, tokenIndex);
		lit = LiteralType::L_FALSE;
	}
	else
	{
		return nullptr;
	}
	return this;
}

void Literal_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	//std::cout << "[Literal]\":" << "\n" << tabs << "{";
	switch (lit)
	{
	case Literal_Expression::LiteralType::L_IDEN:
		std::cout << "\"Identifier\" : " << "\"" << identifier->value << "\"";
		break;
	case Literal_Expression::LiteralType::L_NUM:
		std::cout << "\"Numeric\" : " << "\"" << numeric->value << "\"";
		break;
	case Literal_Expression::LiteralType::L_STR:
		std::cout << "\"String\" : " << "\"" << str->value << "\"";
		break;
	case Literal_Expression::LiteralType::L_TRUE:
		std::cout << "\"True\" : " << "\"" << str->value << "\"";
		break;
	case Literal_Expression::LiteralType::L_FALSE:
		std::cout << "\"False\" : " << "\"" << str->value << "\"";
		break;
	default:
		break;
	}
	//std::cout << "\n" << tabs << "}";
}

void Literal_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*switch (lit)
	{
	case(Literal_Expression::LiteralType::L_NUM):
	{
		compiler->AddInstruction(new Push_Instruction(true, std::stoi(numeric->value)));
		break;
	}

	case(Literal_Expression::LiteralType::L_IDEN):
	{
		compiler->AddInstruction(new Push_Instruction(false, compiler->TryGetSymbol(identifier->value)->memoryAdress));
		break;
	}

	}*/
}
//
//VirtualType* Literal_Expression::EvaluateType(Compiler* compiler)
//{
//	switch (lit)
//	{
//	case(Literal_Expression::LiteralType::L_NUM):
//	{
//		return compiler->TryGetTypeSymbol("int");
//	}
//
//	case(Literal_Expression::LiteralType::L_IDEN):
//	{
//		return compiler->TryGetSymbol(identifier->value)->type;
//	}
//
//	}
//}
