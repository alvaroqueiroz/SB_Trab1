#include "scanner.h"
using namespace std;

int scanner (char * s){
    /*Open .asm file (input)*/
    ifstream asmfile( s );  //opens ASM file
    string line;
    string token;
    string delimiter = " ";
    if (asmfile){
        while(getline(asmfile, line)){  //scans whole file
            while (line.length() > 0){  //scans whole line
                token = line.substr(0, line.find(delimiter));   //gets new token
                line.erase(0, token.length() + delimiter.length()); //erases token from line
            }
        }
    }else{
        fprintf(stderr, "[ERRO]: Quantidade invalida de argumentos.\n");
        exit(EXIT_FAILURE);
    }
    asmfile.close();    //closes ASM file
    return 0;
}
