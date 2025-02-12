#include "Statement/CompoundStatement.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include <iostream>



std::vector<AST_Node*> Compound_Statement::GetElementList()
{
	std::vector<AST_Node*> result;
	for (Statement* statement : statements)
	{
		result.push_back(statement);
	}
	return result;
}

AST_Node* Compound_Statement::Parse(const std::vector<Token*>& tokens, unsigned int* tokenIndex, Compiler* compiler)
{
	cur_l = GetNextToken(tokens, tokenIndex);

	while (true)
	{
		Statement* newStatement = GetNextStatement(tokens, tokenIndex, compiler);
		if (!newStatement)
		{
			if (CheckTokenType(tokens, *tokenIndex, TokenType::CURLY_R))
			{
				cur_r = GetNextToken(tokens, tokenIndex);
				break;
			}
			else
			{
				return nullptr;
			}
		}
		statements.push_back(newStatement);
	}

	return this;
}

void Compound_Statement::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Compound Statement\":" << "\n" << tabs << "{";
	for (size_t i = 0; i < statements.size(); i++)
	{
		std::cout << '\n' << tabs << "\t";
		statements[i]->Print(depth + 1);

		if (i < statements.size() - 1)
			std::cout << ",";
	}
	std::cout << "\n" << tabs << "}";
}

void Compound_Statement::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{

	AST_Node::GenerateInstructions(compiler, this);

	compiler->RemoveSymbolInScope(this);

}


