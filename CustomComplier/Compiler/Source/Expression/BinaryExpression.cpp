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
	AST_Node::GenerateInstructions(compiler, scope);

	switch (op->type)
	{
	case(TokenType::PLUS): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::ADDITION)); break;
	case(TokenType::MINUS): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::SUBSTRACTION)); break;
	case(TokenType::MULT): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::MULTIPLICATION)); break;
	case(TokenType::DIVIDE): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::DIVISION)); break;
	case(TokenType::IS_EQUAL): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::EQUALITY)); break;
	case(TokenType::IS_NOT_EQUAL): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::INEQUALITY)); break;
	case(TokenType::GREATER): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::GREATER_THAN)); break;
	case(TokenType::GREATER_EQUAL): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::GREATER_OR_EQUAL_THAN)); break;
	case(TokenType::LESSER): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::LESSER_THAN)); break;
	case(TokenType::LESSER_EQUAL): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::LESSER_OR_EQUAL_THAN)); break;
	case(TokenType::AND): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::LOGICAL_AND)); break;
	case(TokenType::OR): compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::LOGICAL_OR)); break;
	}
}
