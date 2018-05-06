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
//#include "argument_checks.h"
using namespace std;



int main (int argc, char** argv){

//    validateArguments(argc, argv);

    string s = argv[1];
    string delimiter = ".";
    string file_name = s.substr(0, s.find(delimiter));
    cout << file_name << endl;
    /*
    FILE *fp = NULL;
    int operation_mode = checkOutputOption(argv[1]);
    switch (operation_mode){
        case 0:
            fp = fopen("pre_processed.txt", "w+");
            pre_processor();
            break;
        case 1:
            fp = fopen("macro_solved.txt", "w+");
            macro_sover();
            break;
        case 2:
            fp = fopen("output.o", "w+");
            assembler();
            break;
        default:
            return 0;
    }
    */

return 0;
}
