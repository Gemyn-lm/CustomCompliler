#include "Expression/BinaryExpression.hpp"
#include "Expression/LiteralExpression.hpp"
#include "Compiler.hpp"
#include <iostream>
#include <string>

std::vector<AST_Node*> Binary_Expression::GetElementList()
{
	return std::vector<AST_Node*>({ leftExpression, rightExpression });
}

void Binary_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Binary Operation\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t";
	leftExpression->Print(depth + 1);
	std::cout << ",";
	std::cout << '\n' << tabs << '\t';
	rightExpression->Print(depth + 1);
	std::cout << ",";

	std::cout << '\n' << tabs << "\t\"Operator\" : " << "\"" << op->value << "\",";

	std::cout << "\n" << tabs << "}";
}



void Binary_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*AST_Node::GenerateInstructions(compiler, scope);

	switch (op->type)
	{
	case(TokenType::MINUS): compiler->AddInstruction(new Unary_Instruction(UnaryOperationType::NEGATION)); break;
	case(TokenType::NOT): compiler->AddInstruction(new Unary_Instruction(UnaryOperationType::NOT_BOOL)); break;
	}*/
}
