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
    scanner(input_fn, tokenlist);
    //parser();
    //semantic_analyser();


    /*create output file*/
    //ofstream fp (output_fn);  //opens output file


    //fp.close();   //closes output file

    return 0;
}
