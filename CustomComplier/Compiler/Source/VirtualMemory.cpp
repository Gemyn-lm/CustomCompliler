#include "VirtualMemory.hpp"


int VirtualMemory::ReadMemory(const int pointerOffset)
{
	int result;
	memcpy(&result, &memory[stackHead + pointerOffset], 4);
	return result;
}

void VirtualMemory::WriteMemory(const int pointerOffset, const int value)
{
	memcpy(&memory[stackHead + pointerOffset], &value, 4);
}

int VirtualMemory::ReadTempValue(const int pointerOffset)
{
	int result;
	memcpy(&result, &memory[stackHead + pointerOffset + tempValuesOffset], 4);
	return result;
}

void VirtualMemory::WriteTempValue(const int pointerOffset, const int value)
{
	memcpy(&memory[stackHead + pointerOffset + tempValuesOffset], &value, 4);
}

void VirtualMemory::PushTempValue(const int value)
{
	WriteTempValue(0, value);
	tempValuesOffset += 4;
}

int VirtualMemory::PopTempValue()
{
	tempValuesOffset -= 4;
	return ReadTempValue(0);
}

void VirtualMemory::PushStack(const int value)
{
	WriteMemory(0, value);
	stackHead += 4;
}

int VirtualMemory::PopStack()
{
	stackHead -= 4;
	return ReadMemory(0);
}
