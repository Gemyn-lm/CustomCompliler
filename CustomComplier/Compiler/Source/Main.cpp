#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.hpp"
#include "Compiler.hpp"
#include "Program.hpp"
#include "Interpretor.hpp"

using namespace std;

void Print(uint8_t* memory)
{
    int arg;
    memcpy(&arg, memory, 4);
    //memcpy(&arg, &memory, 4);
    std::cout << arg << std::endl;
}

int main()
{
    Compiler compiler;
    compiler.AddExternalFunctionSymbol("Print", Print);
    Program program = compiler.Compile("Compiler/Resources/program.txt");
    compiler.PrintDebugInfo();
    program.Print();

    Interpretor interpretor(program, 512);
    interpretor.Run(0);

}

