#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Compiler.hpp"
#include "Parser.hpp"



std::string ExtractTextFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


Program Compiler::Compile(const std::string& filename)
{
    std::string programTxt = ExtractTextFile(filename);

    tokenList = Tokenize(programTxt);
    std::vector<Function_Def*> funcList = ParseToSyntaxTree(tokenList, this);
    funcList[0]->Print(0);

    Program program = Program();
    for(Function_Def * funcDef : funcList)
    {
        funcDef->GenerateInstructions(this, nullptr);
        VirtualFunction vFunc = VirtualFunction();
        vFunc.instructionList = currentInstructionList;
        currentInstructionList.clear();
        program.AddVirtualFunction(vFunc);
    }

    return program;
}

void Compiler::PrintDebugInfo()
{
    for (Token* token : tokenList)
    {
        std::cout << DebugTokenType[token->type] << " : " << token->value << "\n";
    }
}

int Compiler::AddVariableSymbol(std::string& variableName, Compound_Statement* scope)
{
    variableSymbolMap.emplace(variableName, Symbol(variableSymbolMap.size() * 4, scope));
    return GetVarCountInScope(scope) * 4 - 4;
}

void Compiler::RemoveSymbolInScope(Compound_Statement* scope)
{
    for (auto it = variableSymbolMap.begin(); it != variableSymbolMap.end(); ) 
    {
        if (it->second.scope == scope) 
            it = variableSymbolMap.erase(it);
        else
            ++it;
    }
}

size_t Compiler::GetVarCountInScope(Compound_Statement* currentScope) const
{
    return std::count_if(variableSymbolMap.begin(), variableSymbolMap.end(), [currentScope](const auto& pair) {
        return pair.second.scope == currentScope;
        });
}
