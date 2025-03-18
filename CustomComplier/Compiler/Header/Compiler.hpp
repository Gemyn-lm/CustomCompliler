#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
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

	ExternalFunctionSymbol* TryGetExternalFuncSymbol(const std::string& symbolName)
	{
		auto it = externalFunctionSymbolMap.find(symbolName);
		return (it != externalFunctionSymbolMap.end()) ? &(it->second) : nullptr;
	}

	void AddInstruction(Instruction* instruction)
	{
		currentInstructionList.push_back(instruction);
	}

	int AddVariableSymbol(std::string& variableName, Compound_Statement* scope);
	int AddExternalFunctionSymbol(const char* functionName, std::function<void(uint8_t* memory)> funcPtr);
	void RemoveSymbolInScope(Compound_Statement* scope);
	std::vector<Instruction*> GetInstructions() const
	{
		return currentInstructionList;
	}

	size_t GetVarCountInScope(Compound_Statement* currentScope) const;

private:

	Program resultProgram;

	std::vector<Token*> tokenList;

	std::map<std::string, VariableSymbol> variableSymbolMap;
	std::map<std::string, FunctionSymbol> functionSymbolMap;
	std::map<std::string, ExternalFunctionSymbol> externalFunctionSymbolMap;

	// instruction list for the current function
	std::vector<Instruction*> currentInstructionList;
};