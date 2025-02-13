#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.hpp"
#include "Compiler.hpp"
#include "Program.hpp"
#include "Interpretor.hpp"

using namespace std;

int main()
{
    Compiler compiler;
    Program program = compiler.Compile("Compiler/Resources/program.txt");
    compiler.PrintDebugInfo();
    program.Print();

    Interpretor interpretor(program, 512);
    interpretor.Run(0);

}

