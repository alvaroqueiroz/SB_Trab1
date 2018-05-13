#include "pre_processor.h"
#include "scanner.h"
using namespace std;

/*
* PRE_PROCESSOR: executes the analisys steps from the assembler
* INPUT: - char * s -> ASM file name from terminal
* OUTPUT: - FILE *ofp -> File containing analysed code
*/
int pre_processor(char * s){
    list <Token> tokenlist;
    scanner(s, tokenlist);
    //parser();
    //semantic_analyser();

    string delimiter = ".";
    string file_name = string(s).substr(0, string(s).find(delimiter));  //remove extension




    /*create output file*/
    FILE *ofp = NULL;
    char* outpname;
    file_name = file_name + ".txt";     //add ".txt" extension
    outpname = strdup(file_name.c_str());
    ofp = fopen(outpname, "w+");




    fclose (ofp);
    
    return 0;
}
