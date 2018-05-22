#include "pre_processor.h"
#include "scanner.h"
using namespace std;

/*
* PRE_PROCESSOR: executes the analisys steps from the assembler
* INPUT: - char * input_fn -> ASM file name from terminal
* OUTPUT: - FILE *output_fn -> File containing analysed code
*/
int pre_processor(char * input_fn, char * output_fn){
    list <Token> tokenlist;
    list <Token> labellist;

    scanner(input_fn, tokenlist, labellist);
    //parser();
    //semantic_analyser();


    /*create output file*/
    //ofstream fp (output_fn);  //opens output file


    //fp.close();   //closes output file

    return 0;
}

void print_list (list<Token> & tokenlist){
    cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
    list<Token>::iterator it;
    for (it = tokenlist.begin();it != tokenlist.end(); it++)
        cout << "Token: " << it->str << "..   Line: " << it->line_number << "   Position in line: " << it->token_pos_il << "    Type: " << it->type << "        addt_info: " << it->addit_info << "    flag: " << it->flag << "     info str: " << it->info_str << endl;  //print list element
    cout << "-----------------\n";
}
