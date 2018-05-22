/*
Universidade de Brasilia - 01/2018
CIC 116432 - Software Basico - Turma B
Professor Bruno Macchiavello
Trabalho Pratico 1 - Montador

Alunos: Andre Abreu Rodrigues de Almeida    12/0007100
        Bruno Takashi Tengan                12/0167263
*/



#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "argument_checks.h"
#include "pre_processor.h"
#include "assembler.h"
using namespace std;

int pre_error = 0; // flag to indicate if pre-processor had any error.

/*
* MAIN: validates arguments and calls specifc functions, acording to arguments.
* INPUTS: - argc -> argument count from terminal
*         - argv -> argument vector from terminal
* OUTPUT: none
*/
int main (int argc, char** argv){

    validateArguments(argc, argv);
    int operation_mode = checkOutputOption(argv[1]);
    string file_name = string(argv[2]) + ".asm";
    string output_fn;
    switch (operation_mode){
        case 0:
            output_fn = string(argv[3]) + ".pre";
            pre_processor(strdup(file_name.c_str()), strdup(output_fn.c_str()));
            break;
        case 1:
            output_fn = string(argv[3]) + ".mcr";
    //        macro_solver(strdup(file_name.c_str()), strdup(output_fn.c_str()));
            break;
        case 2:
            output_fn = string(argv[3]) + ".o";
            assembler(strdup(file_name.c_str()), strdup(output_fn.c_str()));
            break;
        default:
            return 0;
    }

return 0;
}
