#pragma once
#include <string>
#include <vector>
#include <map>
#include "Program.hpp"
#include "Tokenizer.hpp"
#include "Symbol.hpp"




class Compiler
{
public:

	Program Compile(const std::string& filename);

	void PrintDebugInfo();

	VariableSymbol* TryGetVarSymbol(const std::string& symbolName)
	{
		auto it = variableSymbolMap.find(symbolName);
		return (it != variableSymbolMap.end()) ? &(it->second) : nullptr;
	}

	FunctionSymbol* TryGetFuncSymbol(const std::string& symbolName)
	{
		auto it = functionSymbolMap.find(symbolName);
		return (it != functionSymbolMap.end()) ? &(it->second) : nullptr;
	}

	void AddInstruction(Instruction* instruction)
	{
		currentInstructionList.push_back(instruction);
	}

	int AddVariableSymbol(std::string& variableName, Compound_Statement* scope);
	void RemoveSymbolInScope(Compound_Statement* scope);
	std::vector<Instruction*> GetInstructions() const
	{
		return currentInstructionList;
	}

	size_t GetVarCountInScope(Compound_Statement* currentScope) const;

private:

	std::vector<Token*> tokenList;

	std::map<std::string, VariableSymbol> variableSymbolMap;
	std::map<std::string, FunctionSymbol> functionSymbolMap;

	// instruction list for the current function
	std::vector<Instruction*> currentInstructionList;
};