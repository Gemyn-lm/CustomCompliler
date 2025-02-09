#include "Expression/Expression.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/LiteralExpression.hpp"
#include "Expression/ParenExpression.hpp"
#include "Expression/FuncCall.hpp"
#include "Expression/IndexingExpression.hpp"
#include "Expression/UnaryExpression.hpp"
#include "Expression/AssignationExpression.hpp"
#include "Parser.hpp"
#include <iostream>

Expression* GetNextExpression(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	return GetNextBinaryOperation(tokens, tokenIndex, -1, compiler);
}

int GetOperatorPrecedence(TokenType type, bool& isLeftHanded)
{
	isLeftHanded = true;
	switch (type)
	{
	case EQUAL: isLeftHanded = false;  return 1;
	case PLUS_EQUAL: isLeftHanded = false; return 1;
	case MINUS_EQUAL: isLeftHanded = false; return 1;
	case MULT_EQUAL: isLeftHanded = false; return 1;
	case DIV_EQUAL: isLeftHanded = false; return 1;
	case OR: return 2;
	case AND: return 3;
	case IS_EQUAL: return 7;
	case IS_NOT_EQUAL: return 7;
	case GREATER: return 8;
	case GREATER_EQUAL: return 8;
	case LESSER: return 8;
	case LESSER_EQUAL: return 8;
	case PLUS: return 11;
	case MINUS: return 11;
	case MULT: return 12;
	case DIVIDE: return 12;
	default: return 0;
	}
}

Expression* GetExpressionFromOperator(Expression* left, Expression* right, Token* op)
{
	switch (op->type)
	{
	case EQUAL: return new Assignation_Expression(left, op, right);
	case PLUS_EQUAL: return new Assignation_Expression(left, op, right);
	case MINUS_EQUAL: return new Assignation_Expression(left, op, right);
	case MULT_EQUAL: return new Assignation_Expression(left, op, right);
	case DIV_EQUAL: return new Assignation_Expression(left, op, right);
	case OR: return new Binary_Expression(left, op, right);
	case AND: return new Binary_Expression(left, op, right);
	case IS_EQUAL: return new Binary_Expression(left, op, right);
	case IS_NOT_EQUAL: return new Binary_Expression(left, op, right);
	case GREATER: return new Binary_Expression(left, op, right);
	case GREATER_EQUAL: return new Binary_Expression(left, op, right);
	case LESSER: return new Binary_Expression(left, op, right);
	case LESSER_EQUAL: return new Binary_Expression(left, op, right);
	case PLUS: return new Binary_Expression(left, op, right);
	case MINUS: return new Binary_Expression(left, op, right);
	case MULT: return new Binary_Expression(left, op, right);
	case DIVIDE: return new Binary_Expression(left, op, right);
	default: return nullptr;
	}
}

Expression* GetNextBinaryOperation(const std::vector<Token*>& tokens, unsigned int* tokenIndex, int precedence, Compiler* compiler)
{
	Expression* result = GetNextPrefixOperation(tokens, tokenIndex, compiler);
	if (!result) return nullptr;

	bool isLeftHanded;
	while (int newPrecedence = GetOperatorPrecedence(CheckTokenType(tokens, *tokenIndex), isLeftHanded))
	{
		Expression* right = nullptr;
		Token* op = nullptr;

		if (newPrecedence > precedence || (newPrecedence == precedence && !isLeftHanded))
		{
			op = GetNextToken(tokens, tokenIndex);
			right = GetNextBinaryOperation(tokens, tokenIndex, newPrecedence, compiler);
		}
		else
		{
			return result;
		}


		if (!right) return nullptr;

		Expression* tmp = GetExpressionFromOperator(result, right, op);

		result = tmp;
	}
	return result;
}

Expression* GetNextPrefixOperation(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{

	if (CheckTokenType(tokens, *tokenIndex, TokenType::MINUS))
	{
		Token* op = GetNextToken(tokens, tokenIndex);
		return new UnaryExpression(GetNextPrefixOperation(tokens, tokenIndex, compiler), op);
	}
	if (CheckTokenType(tokens, *tokenIndex, TokenType::NOT))
	{
		Token* op = GetNextToken(tokens, tokenIndex);
		return new UnaryExpression(GetNextPrefixOperation(tokens, tokenIndex, compiler), op);
	}

	return GetNextFactor(tokens, tokenIndex, compiler);
}



Expression* GetNextFactor(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	Expression* result = nullptr;

	// Terminal factors (parenthesis, single token)
	if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_L))
	{
		result = new Paren_Expression();
		if (!result->Parse(tokens, tokenIndex, compiler)) return nullptr;
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::IDENTIFIER) ||
		CheckTokenType(tokens, *tokenIndex, TokenType::NUMERIC_LITERAL) ||
		CheckTokenType(tokens, *tokenIndex, TokenType::STRING_LITERAL) ||
		CheckTokenType(tokens, *tokenIndex, TokenType::TRUE) ||
		CheckTokenType(tokens, *tokenIndex, TokenType::FALSE))
	{
		result = new Literal_Expression();
		if (!result->Parse(tokens, tokenIndex, compiler)) return nullptr;
	}


	// Suffix epxression (unction call, indexing, suffix increment / decrement, ...)
	while (true)
	{
		if (CheckTokenType(tokens, *tokenIndex, TokenType::PAREN_L))
		{
			FuncCall_Expression* tmp = new FuncCall_Expression(result);
			if (!tmp->Parse(tokens, tokenIndex, compiler)) return nullptr;
			result = tmp;
		}
		else if (CheckTokenType(tokens, *tokenIndex, TokenType::BRACKET_L))
		{
			Indexing_Expression* tmp = new Indexing_Expression(result);
			if (!tmp->Parse(tokens, tokenIndex, compiler)) return nullptr;
			result = tmp;
		}
		else
		{
			break;
		}
	}

	return result;
}

