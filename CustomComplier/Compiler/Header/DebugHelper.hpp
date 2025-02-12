#pragma once
#include <string>

enum BinaryOperationType;
enum UnaryOperationType;

const std::string BinaryOperationTypeDebug[]
{
	"MOV",
	"ADD",
	"SUB",
	"MULT",
	"DIV",
	"EQU",
	"INEQ",
	"GRT",
	"GREQ",
	"LESS",
	"LEEQ",
	"AND",
	"OR"
};

const std::string UnaryOperationTypeDebug[]
{
	"NEG",
	"NOT"
};

void PrintDebug(UnaryOperationType type);
void PrintDebug(BinaryOperationType type);