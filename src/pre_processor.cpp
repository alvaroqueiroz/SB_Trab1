#include "pre_processor.h"
#include "scanner.h"
#include "parser.h"
#include "macro.h"
#include "synthesizer.h"
#include "semantic_analyser.h"
using namespace std;

/*
* PRE_PROCESSOR: executes the analisys steps from the assembler
* INPUT: - char * input_fn -> ASM file name from terminal
* OUTPUT: - FILE *output_fn -> File containing analysed code
*/
int pre_processor(char * input_fn, char * output_fn){
    list <Token> tokenlist;
    list <Token> labellist;
    list<Token>::iterator it, aux;

    scanner(input_fn, tokenlist, labellist);
    //equ;
    parser(tokenlist, labellist);
    //if;
    //semantic_analyser();
    //macro;
    solve_macro(tokenlist);
    print_list(tokenlist);
    synthesizer(tokenlist);
    semantic_analyser(tokenlist, labellist);


    /*create output file*/
    ofstream fp (output_fn);  //opens output file
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        aux = it;
        aux++;
        while (aux->line_number == it->line_number){
            fp << it->str << " ";
            it++;
            aux++;
        }
        fp << it->str << endl;
    }


    fp.close();   //closes output file

    return 0;
}


void print_list (list<Token> & tokenlist){
    cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
    list<Token>::iterator it;
    for (it = tokenlist.begin();it != tokenlist.end(); it++)
        cout << "Token: " << it->str << "..   \tLine: " << it->line_number << "   \tPosition in line: " << it->token_pos_il << "    \tType: " << it->type << "        \taddt_info: " << it->addit_info << "    \tflag: " << it->flag << "     \tinfo str: " << it->info_str << endl;  //print list element
    cout << "-----------------\n";
}

void mark_sintax_error (list<Token> & tokenlist, list<Token>::iterator it){
    int i = it->line_number;
    list<Token>::iterator newit;
    newit = it;
    while (newit->line_number == i){
        newit--;
    }
    newit++;
    while (newit->line_number == i){
        newit->flag = -1;
        newit++;
    }
}
