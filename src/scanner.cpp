#include "scanner.h"
using namespace std;

int scanner (char * s, list <Token> & tokenlist){
    identify_tokens(s, tokenlist);      //generates token list
    print_tokenlist (tokenlist);
    rm_spaces(tokenlist);     //removes blank spaces
    print_tokenlist (tokenlist);
//    verify_tokens(tokenlist);     //verifies token lexic validity
    return 0;
}


int identify_tokens (char * s, list <Token> & tokenlist){
    /*Open .asm file (input)*/
    ifstream asmfile( s );  //opens ASM file
    string line;
    string delimiter = " ";
    string semicolon = ";";
    int lcount = 0;
    int tcount = 0;
    Token vtoken;
    if (asmfile){
        while(getline(asmfile, line)){  //scans whole file
        line = line.substr(0, line.find(semicolon));    //removes comments
            while (line.length() > 0){  //scans whole line
                vtoken.str = line.substr(0, line.find(delimiter));   //gets new token
                line.erase(0, vtoken.str.length() + delimiter.length()); //erases token from line
                vtoken.token_pos_il = tcount;   //stores token order in line
                vtoken.line_number = lcount;    //stores line number
                tokenlist.insert(tokenlist.end(), vtoken);   //inserts token to token list
                tcount++;
            }
        tcount = 0;
        lcount++;
        }
    }else{
        fprintf(stderr, "[ERRO]: Falha ao abrir o arquivo '%s'.\n", s);
        exit(EXIT_FAILURE);
    }
    asmfile.close();    //closes ASM file
    return 0;
}


void rm_spaces (list <Token> & tokenlist){
    list<Token>::iterator it;
    list<Token>::iterator newit;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (it->str == "" || it->str == " " || it->str == "\n"){
            newit = it = tokenlist.erase(it); //erases node and advances iterator
            it--;   //places iterator back to place (bug fix for Linux)
            //newit++;  //works on Mac, but not on Linux - DON'T UNCOMMENT UNLESS YOU KNOW WHAT YOU'RE DOING!!!
            while (newit->line_number == it->line_number){
                newit->token_pos_il--;
                newit++;
            }
        }
    }
}

void verify_tokens (list <Token> & tokenlist){

}

void print_tokenlist (list <Token> & tokenlist){
        cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
        list<Token>::iterator it;
        for (it = tokenlist.begin();it != tokenlist.end(); it++)
            cout << "Token: " << it->str << "   Line: " << it->line_number << " Number: " << it->token_pos_il << endl;  //print list element
        cout << "-----------------\n";
}
