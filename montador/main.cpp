/*
Universidade de Brasilia - 01/2019
CIC 116432 - Software Basico - Turma B
Professor Bruno Macchiavello
Trabalho Pratico 1 - Montador

Alunos: Ian Moura Alexandre                 15/0129661
        Alvaro Queiroz dos Reis Silva       15/0155280
*/



#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "argument_checks.h"
#include "pre_processor.h"
#include "scanner.h"
#include "parser.h"
#include "macro.h"
#include "synthesizer.h"
#include "semantic_analyser.h"
using namespace std;

int pre_error = 0; // flag to indicate if pre-processor had any error.
int solo = 0;

/*
* MAIN: validates arguments and calls specifc functions, acording to arguments.
* INPUTS: - argc -> argument count from terminal
*         - argv -> argument vector from terminal
* OUTPUT: none
*/
int main (int argc, char** argv){

    list<Token> tokenlist, tokenlist2;
    list<Token>::iterator it, aux;
    list<Symbol> dt, ut, dt2, ut2;
    list<Symbol>::iterator its;
    list<int> object, realoc, object2, realoc2;
    list<int>::iterator it_ob;

    checkArgumentAmount(argc);
    //int operation_mode = checkOutputOption(argv[1]);
    string file_name;
    string output_fn;
    string pathPRE;
    string pathO;
    if (argc == 2) {
        solo = 1;
        file_name = "../arquivosASM/" + string(argv[1]) + ".asm";
        pre_processor(strdup(file_name.c_str()), tokenlist);

        if (pre_error){
            cout << endl << "Error = true. The process will terminate before creating output files." << endl << endl;
            return 0;
        }

        solve_macro(tokenlist);
        synthesizer(tokenlist, object, realoc, dt, ut);

            // Creating a directory 
        if (mkdir("../arquivosPRE", 0777) == -1){
            if(errno != 17){ 
                cerr << "Error :  " << strerror(errno) << endl;
            }
        }

        ofstream pre;
        pathPRE = "../arquivosPRE/" + string(argv[1]) + ".pre";
		pre.open(pathPRE);
		    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
		        pre << it->str << " ";
		    }
 		pre.close();
        cout << "Created the " << string(argv[1]) << ".pre\n";
		ofstream xpre;  //opens output file for pre

        pathO = "../arquivosOBJ/" + string(argv[1]) + ".obj";
        if (mkdir("../arquivosOBJ", 0777) == -1){
            if(errno != 17){ 
                cerr << "Error :  " << strerror(errno) << endl;
            }
        }
		xpre.open(pathO);
		for (it_ob = object.begin(); it_ob != object.end(); it_ob++){
		    xpre << *it_ob << " ";
		}

		xpre.close();   //closes output file
        cout << "Created the " << string(argv[1]) << ".obj\n";

        return 0;
    } else {
        solo = 0;
        file_name = file_name = string(argv[1]) + ".asm";
        pre_processor(strdup(file_name.c_str()), tokenlist);
        file_name = file_name = string(argv[2]) + ".asm";
        pre_processor(strdup(file_name.c_str()), tokenlist2);

        if (pre_error){
            cout << endl << "Error = true. The process will terminate before creating output files." << endl << endl;
            return 0;
        }

        solve_macro(tokenlist);
        synthesizer(tokenlist, object, realoc, dt, ut);
        solve_macro(tokenlist2);
        synthesizer(tokenlist2, object2, realoc2, dt2, ut2);


        /*create output file*/
        output_fn = string(argv[1]) + ".o";
        ofstream fpo (output_fn);  //opens output file
        fpo << "HEAD:" << endl;
        fpo << "N. " << string(argv[1]) << endl;
        fpo << "S. " << realoc.size() << endl;
        fpo << "R. ";
        for (it_ob = realoc.begin(); it_ob != realoc.end(); it_ob++){
            fpo << *it_ob << " ";
        }
        if (dt.size() != 0){
            fpo << endl;
            fpo << "D. ";
            for (its = dt.begin(); its != dt.end(); its++){
                fpo << its->str << " " << its->atrb << " ";
            }
        }
        if (ut.size() != 0) {
            fpo << endl;
            fpo << "U. ";
            for (its = ut.begin(); its != ut.end(); its++){
                fpo << its->str << " " << its->atrb << " ";
            }
        }

        fpo << endl << "TEXT: ";
        for (it_ob = object.begin(); it_ob != object.end(); it_ob++){
            fpo << *it_ob << " ";
        }
        fpo.close();   //closes output file

        /*create output file*/
        output_fn = string(argv[2]) + ".o";
        ofstream fpo2 (output_fn);  //opens output file
        fpo2 << "HEAD:" << endl;
        fpo2 << "N. " << string(argv[2]) << endl;
        fpo2 << "S. " << realoc2.size() << endl;
        fpo2 << "R. ";
        for (it_ob = realoc2.begin(); it_ob != realoc2.end(); it_ob++){
            fpo2 << *it_ob << " ";
        }
        if (dt2.size() != 0) {
            fpo2 << endl;
            fpo2 << "D. ";
            for (its = dt2.begin(); its != dt2.end(); its++){
                fpo2 << its->str << " " << its->atrb << " ";
            }
        }
        if (ut2.size() != 0) {
            fpo2 << endl;
            fpo2 << "U. ";
            for (its = ut2.begin(); its != ut2.end(); its++){
                fpo2 << its->str << " " << its->atrb << " ";
            }
        }

        fpo2 << endl << "TEXT: ";
        for (it_ob = object2.begin(); it_ob != object2.end(); it_ob++){
            fpo2 << *it_ob << " ";
        }
        fpo2.close();   //closes output file

				/*create output file*/


        return 0;
    }
}
