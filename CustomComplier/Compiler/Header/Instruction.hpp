#pragma once
#include "Parser.hpp"
//#include "Semantic.h"
#include "Statement/Statement.hpp"
#include "VirtualMemory.hpp"
#include "DebugHelper.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Instruction
{
	virtual void Print() {};
	virtual void Execute(VirtualMemory* vMemory) = 0;
};

enum BinaryOperationType
{
	ASSIGNATION,
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVISION,
	EQUALITY,
	INEQUALITY,
	GREATER_THAN,
	GREATER_OR_EQUAL_THAN,
	LESSER_THAN,
	LESSER_OR_EQUAL_THAN,
	LOGICAL_AND,
	LOGICAL_OR
};

struct Binary_Arithmetic_Instruction : Instruction
{
private:

	BinaryOperationType operationType;

public:

	Binary_Arithmetic_Instruction(BinaryOperationType _operationType)
		: operationType(_operationType)
	{
	}

	void Print() override
	{
		PrintDebug(operationType);
		std::cout << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Move_Instruction : Instruction
{
	int targetPointer;

	Move_Instruction(int target)
		: targetPointer(target)
	{
	}

	void Print() override
	{
		std::cout << "MOVE " << "[stack-" << targetPointer << "]\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Push_Instruction : Instruction
{
	bool isSourceConstant;
	union
	{
		int sourcePointer;
		int sourceConstant;
	};

	Push_Instruction(bool _isSourceConstant, int _source)
		: isSourceConstant(_isSourceConstant), sourcePointer(_source)
	{
	}

	void Print() override
	{
		std::cout << "PUSH ";
		if (isSourceConstant)
			std::cout << sourceConstant << "\n";
		else
			std::cout << "[stack-" << sourcePointer << "]\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Pop_Instruction : Instruction
{
	int targetPointer;

	Pop_Instruction(int target)
		: targetPointer(target)
	{
	}

	void Print() override
	{
		std::cout << "POP [stack-" << targetPointer << "]\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};


struct Allocate_Instruction : Instruction
{
	int offset;

	Allocate_Instruction(int _offset)
		: offset(_offset) {
	}

	void Print() override
	{
		std::cout << "ALLOC " << offset << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Jump_Instruction : Instruction
{
	bool checkForCondition;
	int destination;

	Jump_Instruction(bool _checkForCondition, int dest)
		:checkForCondition(_checkForCondition), destination(dest)
	{
	}

	void Print() override
	{
		if (checkForCondition)
			std::cout << "JUMP_IF " << destination << "\n";
		else
			std::cout << "JUMP " << destination << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Store_Exec_Instruction : Instruction
{
	void Print() override
	{
		std::cout << "STORE_EXEC\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Return_Instruction : Instruction
{
	int freeSize;

	Return_Instruction(int _freeSize)
		: freeSize(_freeSize) {
	}

	void Print() override
	{
		std::cout << "RETURN " << freeSize << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct Call_Instruction : Instruction
{
	int functionIndex;

	Call_Instruction(int _functionIndex)
		: functionIndex(_functionIndex)
	{
	}

	void Print() override
	{
		std::cout << "CALL " << functionIndex << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

struct External_Call_Instruction : Instruction
{
	int functionIndex;

	External_Call_Instruction(int _functionIndex)
		: functionIndex(_functionIndex)
	{
	}

	void Print() override
	{
		std::cout << "EXCALL " << functionIndex << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

enum UnaryOperationType
{
	NEGATION,
	NOT_BOOL
};

struct Unary_Instruction : Instruction
{
	UnaryOperationType operationType;

	Unary_Instruction(UnaryOperationType _operationType)
		: operationType(_operationType) {
	}

	void Print() override
	{
		PrintDebug(operationType);
		std::cout << "\n";
	}

	void Execute(VirtualMemory* vMemory) override;
};

