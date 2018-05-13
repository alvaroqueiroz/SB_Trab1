/*
Universidade de Brasilia - 01/2018
CIC 116432 - Software Basico - Turma B
Professor Bruno Macchiavello
Trabalho Pratico 1 - Montador

Alunos: Andre Abreu Rodrigues de Almeida    12/0007100
        Bruno Takashi Tengan                12/0167263
*/

/**
 * @file main.c
 * @brief Execução do programa pela função 'main'.
 */


#include <cstdio>
#include <iostream>
#include <fstream>
#include "argument_checks.h"
using namespace std;



int main (int argc, char** argv){

    validateArguments(argc, argv);

    char* outpname;
    string s = argv[2];
    string delimiter = ".";
    string file_name = s.substr(0, s.find(delimiter));

    FILE *fp = NULL;
    int operation_mode = checkOutputOption(argv[1]);
    switch (operation_mode){
        case 0:
            file_name = file_name + ".txt";
            outpname = strdup(file_name.c_str());
            fp = fopen(outpname, "w+");
    //        pre_processor(fp);
            fclose (fp);
            break;
        case 1:
            file_name = file_name + ".txt";
            outpname = strdup(file_name.c_str());
            fp = fopen(outpname, "w+");
    //        macro_solver(fp);
            fclose (fp);
            break;
        case 2:
            file_name = file_name + ".out";
            outpname = strdup(file_name.c_str());
            fp = fopen(outpname, "w+");
    //        assembler(fp);
            fclose (fp);
            break;
        default:
            return 0;
    }

return 0;
}
