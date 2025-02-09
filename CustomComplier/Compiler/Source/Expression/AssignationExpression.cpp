#include "Expression/AssignationExpression.hpp"
#include "Statement/CompoundStatement.hpp"
#include "Expression/LiteralExpression.hpp"
#include <iostream>

std::vector<AST_Node*> Assignation_Expression::GetElementList()
{
	return std::vector<AST_Node*>({ expression_L, expression_R });
}

void Assignation_Expression::Print(unsigned int depth)
{
	std::string tabs = std::string(depth, '\t');
	std::cout << "\"Assignation\":" << "\n" << tabs << "{"
		<< '\n' << tabs << "\t";
	expression_L->Print(depth + 1);
	std::cout << ",";

	std::cout << '\n' << tabs << "\t";
	expression_R->Print(depth + 1);
	std::cout << "\n" << tabs << "}";
}

void Assignation_Expression::GenerateInstructions(Compiler* compiler, Compound_Statement* scope)
{
	/*if (typeid(*expression_L) != typeid(Literal_Expression) || ((Literal_Expression*)expression_L)->lit != Literal_Expression::LiteralType::L_IDEN)
	{
		std::cerr << "The expression should be an lvalue (referencing an object).";
		return;
	}


	int targetMemory = compiler->TryGetSymbol(((Literal_Expression*)expression_L)->identifier->value)->memoryAdress;

	if (op->type != TokenType::EQUAL)
		compiler->AddInstruction(new Push_Instruction(false, targetMemory));

	expression_R->GenerateInstructions(compiler, scope);

	switch (op->type)
	{
	case PLUS_EQUAL:
		compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::ADDITION));
		break;
	case MINUS_EQUAL:
		compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::SUBSTRACTION));
		break;
	case MULT_EQUAL:
		compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::MULTIPLICATION));
		break;
	case DIV_EQUAL:
		compiler->AddInstruction(new Binary_Arithmetic_Instruction(BinaryOperationType::DIVISION));
		break;
	}

	compiler->AddInstruction(new Pop_Instruction(targetMemory));*/
}

//VirtualType* Assignation_Expression::EvaluateType(Compiler* compiler)
//{
//	return nullptr;
//}


