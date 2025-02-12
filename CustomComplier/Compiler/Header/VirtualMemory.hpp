#pragma once
#include <vector>


class VirtualMemory
{
	uint8_t* memory;
	size_t memorySize;
	int stackHead = 0;
	int tempValuesOffset = 0; // Relative to the stack head

public:

	int currentInstructionIndex = 0;
	int currentFunctionIndex = 0;

	VirtualMemory(size_t size)
		: memorySize(size)
	{
		memory = new uint8_t[size];
	}

	~VirtualMemory()
	{
		delete[] memory;
	}

	// Relative to stack head
	int ReadMemory(const int pointerOffset);
	// Relative to stack head
	void WriteMemory(const int pointerOffset, const int value);

	int ReadTempValue(const int pointerOffset);
	void WriteTempValue(const int pointerOffset, const int value);

	void PushTempValue(const int value);
	int PopTempValue();

	void PushStack(const int value);
	int PopStack();

	void OffsetStackHead(int offset) { stackHead += offset; }
	int MoveStackHead(int destination) { stackHead = destination; }
	int GetStackHead() const { return stackHead; }

	size_t GetMemorySize() const { return memorySize; }

	unsigned char* GetMemory() const { return memory; }
};