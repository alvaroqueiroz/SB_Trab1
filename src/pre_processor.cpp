#include "pre_processor.h"
#include "scanner.h"
using namespace std;

/*
* PRE_PROCESSOR: executes the analisys steps from the assembler
* INPUT: - char * input_fn -> ASM file name from terminal
* OUTPUT: - FILE *output_fn -> File containing analysed code
*/
int pre_processor(char * input_fn, char * output_fn, bool output_enable){
    list <Token> tokenlist;
    list <Token> labellist;

    scanner(input_fn, tokenlist, labellist);
    //parser();
    //semantic_analyser();


    /*create output file*/
    if (output_enable){     //stores output '.pre' file
        ofstream fp (output_fn);  //opens output file
        if (fp.is_open()){
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
        }else{
            fprintf(stderr, "[ERROR]: Error opening file for writing - '%s'.\n", output_fn);
            exit(EXIT_FAILURE);
        }
    }else{
        ofstream fp ("intermediary.csv");  //saves intermediary code as '.csv' file
        if (fp.is_open()){
            fp << "Token Name,Line,Position In Line,Type,Additional Information,Flag,Info String" << endl;
            for (it = tokenlist.begin(); it != tokenlist.end(); it++){
                fp << it->str << "," << it->line_number << "," << it->token_pos_il << "," << it->type << "," << it->addit_info << "," << it->flag << "," << it->info_str << endl;
            }
            fp.close();     //closes '.csv' file
        }else{
            fprintf(stderr, "[ERROR]: Error opening file for writing - 'intermediary.csv'.\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

void print_list (list<Token> & tokenlist){
    cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
    list<Token>::iterator it;
    for (it = tokenlist.begin();it != tokenlist.end(); it++)
        cout << "Token: " << it->str << "..   Line: " << it->line_number << "   Position in line: " << it->token_pos_il << "    Type: " << it->type << "        addt_info: " << it->addit_info << "    flag: " << it->flag << "     info str: " << it->info_str << endl;  //print list element
    cout << "-----------------\n";
}
