#include "pre_processor.h"
using namespace std;

/*
* PRE_PROCESSOR: executes the analisys steps from the assembler
* INPUT: - char * s -> ASM file name from terminal
* OUTPUT: - FILE *ofp -> File containing analysed code
*/
int pre_processor(char * s){
    //scanner(char * s);
    //parser();
    //semantic_analyser();

    string delimiter = ".";
    string file_name = string(s).substr(0, string(s).find(delimiter));  //remove extension





    /*Open .asm file (input)*/
    FILE *ifp = fopen(s, "r");

    /*create output file*/
    FILE *ofp = NULL;
    char* outpname;
    file_name = file_name + ".txt";     //add ".txt" extension
    outpname = strdup(file_name.c_str());
    ofp = fopen(outpname, "w+");




    fclose (ifp);
    fclose (ofp);


    return 0;
}
