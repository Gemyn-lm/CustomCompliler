#include "Instruction.hpp"


void Binary_Arithmetic_Instruction::Execute(VirtualMemory* vMemory)
{
	int left = vMemory->ReadTempValue(-8);
	int right = vMemory->PopTempValue();

	switch (operationType)
	{
	case(BinaryOperationType::ADDITION):              vMemory->WriteTempValue(-4, left + right); break;
	case(BinaryOperationType::SUBSTRACTION):          vMemory->WriteTempValue(-4, left - right); break;
	case(BinaryOperationType::MULTIPLICATION):        vMemory->WriteTempValue(-4, left * right); break;
	case(BinaryOperationType::DIVISION):              vMemory->WriteTempValue(-4, left / right); break;
	case(BinaryOperationType::EQUALITY):              vMemory->WriteTempValue(-4, left == right); break;
	case(BinaryOperationType::INEQUALITY):            vMemory->WriteTempValue(-4, left != right); break;
	case(BinaryOperationType::GREATER_THAN):          vMemory->WriteTempValue(-4, left > right); break;
	case(BinaryOperationType::GREATER_OR_EQUAL_THAN): vMemory->WriteTempValue(-4, left >= right); break;
	case(BinaryOperationType::LESSER_THAN):           vMemory->WriteTempValue(-4, left < right); break;
	case(BinaryOperationType::LESSER_OR_EQUAL_THAN):  vMemory->WriteTempValue(-4, left <= right); break;
	case(BinaryOperationType::LOGICAL_AND):           vMemory->WriteTempValue(-4, left && right); break;
	case(BinaryOperationType::LOGICAL_OR):            vMemory->WriteTempValue(-4, left || right); break;
	}

}

void Move_Instruction::Execute(VirtualMemory* vMemory)
{
	vMemory->WriteMemory(-targetPointer, vMemory->PopTempValue());
}

void Push_Instruction::Execute(VirtualMemory* vMemory)
{
	if (isSourceConstant)
		vMemory->PushTempValue(sourceConstant);
	else
		vMemory->PushTempValue(vMemory->ReadMemory(-sourcePointer));
}

void Pop_Instruction::Execute(VirtualMemory* vMemory)
{
	vMemory->WriteMemory(-targetPointer, vMemory->PopTempValue());
}

void Allocate_Instruction::Execute(VirtualMemory* vMemory)
{
	vMemory->OffsetStackHead(offset);
}

void Jump_Instruction::Execute(VirtualMemory* vMemory)
{
	if (!checkForCondition || !vMemory->PopTempValue())
		vMemory->currentInstructionIndex = destination - 1;
}

void Store_Exec_Instruction::Execute(VirtualMemory* vMemory)
{
	vMemory->PushStack(vMemory->currentInstructionIndex);
	vMemory->PushStack(vMemory->currentFunctionIndex);
}

void Call_Instruction::Execute(VirtualMemory* vMemory)
{
	vMemory->PushStack(vMemory->currentInstructionIndex);
	vMemory->PushStack(vMemory->currentFunctionIndex);
	vMemory->currentInstructionIndex = -1;
	vMemory->currentFunctionIndex = functionIndex;
}

void Unary_Instruction::Execute(VirtualMemory* vMemory)
{
	switch (operationType)
	{
	case(UnaryOperationType::NEGATION): vMemory->WriteTempValue(0, -vMemory->ReadTempValue(0)); break;
	case(UnaryOperationType::NOT_BOOL): vMemory->WriteTempValue(0, !vMemory->ReadTempValue(0)); break;
	}
}

void Return_Instruction::Execute(VirtualMemory* vMemory)
{
	int returnValue = vMemory->PopTempValue();
	vMemory->OffsetStackHead(-freeSize);
	if (vMemory->GetStackHead() <= 0)
		return;
	vMemory->currentFunctionIndex = vMemory->PopStack();
	vMemory->currentInstructionIndex = vMemory->PopStack();
	vMemory->PushTempValue(returnValue);
}
