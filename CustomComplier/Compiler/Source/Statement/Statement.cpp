#include "Statement/Statement.hpp"
#include "Statement/IfStatement.hpp"
#include "Statement/WhileStatement.hpp"
#include "Statement/ReturnStatement.hpp"
#include "Statement/VarDefStatement.hpp"
#include "Statement/ExpressionStatement.hpp"
#include "Statement/CompoundStatement.hpp"
#include "Parser.hpp"

Statement* GetNextStatement(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	Statement* result = nullptr;
	if (CheckTokenType(tokens, *tokenIndex, TokenType::IDENTIFIER) &&
		CheckTokenType(tokens, *tokenIndex + 1, TokenType::IDENTIFIER)) // Might also be an expression statement
	{
		result = new Var_Def_Statement();
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::IF))
	{
		result = new If_Statement();
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::WHILE))
	{
		result = new While_Statement();
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::RETURN))
	{
		result = new Return_Statement();
	}
	else if (CheckTokenType(tokens, *tokenIndex, TokenType::CURLY_L))
	{
		result = new Compound_Statement();
	}
	else
	{
		result = new Expression_Statement();
	}

	if (result)
		return (Statement*)result->Parse(tokens, tokenIndex, compiler);
	else
		return nullptr;
}
