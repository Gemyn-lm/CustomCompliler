#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.hpp"
#include "Compiler.hpp"
#include "Program.hpp"

using namespace std;

int main()
{
    Compiler compiler;
    Program program = compiler.Compile("Compiler/Resources/program.txt");

    compiler.PrintDebugInfo();

}

