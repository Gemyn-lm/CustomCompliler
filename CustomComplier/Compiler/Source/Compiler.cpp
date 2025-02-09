#include <fstream>
#include <iostream>
#include <sstream>
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

	return Program();
}

void Compiler::PrintDebugInfo()
{
    for (Token* token : tokenList)
    {
        std::cout << DebugTokenType[token->type] << " : " << token->value << "\n";
    }
}
