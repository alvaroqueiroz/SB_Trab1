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
#include "scanner.h"
#include "parser.h"
#include "macro.h"
#include "synthesizer.h"
#include "semantic_analyser.h"
using namespace std;

int pre_error = 0; // flag to indicate if pre-processor had any error.

/*
* MAIN: validates arguments and calls specifc functions, acording to arguments.
* INPUTS: - argc -> argument count from terminal
*         - argv -> argument vector from terminal
* OUTPUT: none
*/
int main (int argc, char** argv){

    list<Token> tokenlist;
    list<Token>::iterator it, aux;
    list<int> object;
    list<int>::iterator it_ob;

    validateArguments(argc, argv);
    int operation_mode = checkOutputOption(argv[1]);
    string file_name = string(argv[2]) + ".asm";
    string output_fn;

    if (operation_mode < 0 || operation_mode > 2){
        return 0;
    } else {
        pre_processor(strdup(file_name.c_str()), tokenlist);
        /*create output file*/
        output_fn = string(argv[3]) + ".pre";
        ofstream fpp (output_fn);  //opens output file
        for (it = tokenlist.begin(); it != tokenlist.end(); it++){
            aux = it;
            aux++;
            while (aux->line_number == it->line_number){
                fpp << it->str << " ";
                it++;
                aux++;
            }
            fpp << it->str << endl;
        }
        fpp.close();   //closes output file
        if (operation_mode == 0){
            return 0;
        }

        solve_macro(tokenlist);
        /*create output file*/
        output_fn = string(argv[3]) + ".mcr";
        ofstream fpm (output_fn);  //opens output file
        for (it = tokenlist.begin(); it != tokenlist.end(); it++){
            aux = it;
            aux++;
            while (aux->line_number == it->line_number){
                fpm << it->str << " ";
                it++;
                aux++;
            }
            fpm << it->str << endl;
        }
        fpm.close();   //closes output file
        if (operation_mode == 1){
            return 0;
        }

        synthesizer(tokenlist);
        /*create output file*/
        output_fn = string(argv[3]) + ".o";
        ofstream fpo (output_fn);  //opens output file
        for (it = tokenlist.begin(); it != tokenlist.end(); it++){
            aux = it;
            aux++;
            while (aux->line_number == it->line_number){
                fpo << it->str << " ";
                it++;
                aux++;
            }
            fpo << it->str << endl;
        }
        fpo.close();   //closes output file
        
        return 0;
    }
}
