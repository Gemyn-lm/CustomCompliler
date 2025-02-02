#pragma once
#include <string>
#include <vector>
#include "Program.hpp"
#include "Tokenizer.hpp"


class Compiler
{
public:

	Program Compile(const std::string& filename);

	void PrintDebugInfo();

private:

	std::vector<Token*> tokenList;

};