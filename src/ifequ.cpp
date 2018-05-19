#include "ifequ.h"
using namespace std;

/*
*   IFEQU.CPP
*   Solves the directives "IF" and "EQU" from the assembly code.
*   First it solves for "EQU", uzing the equilizer() function, then solves for "IF" with the conditional_dir() function.
*   Input: tokenlist from scanner.
*   output: tokenlist solved for IF and EQU directives.
*/


void ifequ(list<Token> & tokenlist, list<Token> & labellist){
    print_list(tokenlist);
    print_list(labellist);
    equilizer(tokenlist, labellist);
    print_list(tokenlist);
    print_list(labellist);
//    conditional_dir(tokenlist);
}


int equilizer(list<Token> & tokenlist, list<Token> & labellist){
    if (identify_equ(tokenlist, labellist) == 0)
        solve_equ(tokenlist, labellist);
    return 0;
}

int identify_equ(list<Token> & tokenlist, list<Token> & labellist){
    list<Token>::iterator t_it, t_newit, aux, l_it;
    string label, value, delimiter = ":";
    int line, ad_info, type, equ_error = 0;
    for (t_it = tokenlist.begin();t_it != tokenlist.end(); t_it++){     //scans all the tokenlist
        if (t_it->type == TT_DIRECTIVE && t_it->addit_info == DIR_EQU){     //if it's "EQU"
            t_newit = t_it;
            t_newit --;
            if (t_it != tokenlist.begin()){      //checks if it is the first token
                if (t_newit->type == TT_LABEL){     //checks if previous is label
                    label = t_newit->str.substr(0, t_newit->str.find(delimiter));
                    line = t_newit->line_number;
                }else{                              //if it's not a label marks as sintax error
                    fprintf(stderr, "Sintax error @ line %d - Missing label for 'EQU' directive.\n", t_it->line_number);
                    pre_error = 1;
                    equ_error = 1;
                    break;
                }
            }else{
                fprintf(stderr, "Sintax error @ line %d - Missing label for 'EQU' directive.\n", t_it->line_number);
                pre_error = 1;
                equ_error = 1;
                break;
            }
            advance(t_newit,2);
            aux = t_newit;
            aux++;
            if (aux != tokenlist.end()){        //checks if it is the last token
                if (t_newit->line_number == t_it->line_number){     //checks if there's an argument for "EQU"
                    value = t_newit->str;
                    type = t_newit->type;
                    ad_info = t_newit->addit_info;
                }else{                      ////if there's no argument marks as sintax error
                    fprintf(stderr, "Sintax error @ line %d - Missing argument for 'EQU' directive.\n", t_it->line_number);
                    pre_error = 1;
                    equ_error = 1;
                    break;
                }
            }else{                      ////if there's no argument marks as sintax error
                fprintf(stderr, "Sintax error @ line %d - Missing argument for 'EQU' directive.\n", t_it->line_number);
                pre_error = 1;
                equ_error = 1;
                break;
            }
            l_it = labellist.begin();
            while (l_it != labellist.end() && l_it->str != label){      //search in labelist for the label
                l_it++;
            }
            if (l_it == labellist.end()){       //terminates program if there isn't such a label
                fprintf(stderr, "[ERROR]: Malformed label list. Program terminated.\n");
                exit(EXIT_FAILURE);
            }else{
                l_it->info_str = value;     //if there is, stores the argument value in the labellist token
                l_it->line_number = line;
                l_it->type = type;
                l_it->addit_info = ad_info;
                l_it->flag = DIR_EQU;
            }
        }
    }
    return equ_error;
}

int solve_equ (list<Token> & tokenlist, list<Token> & labellist){
    list<Token>::iterator l_it, l_newit, t_it, t_newit;
    for (l_it = labellist.begin(); l_it != labellist.end(); l_it++){    //scans whole list of labels
        if (l_it->flag == DIR_EQU){       //flag indicates "EQU"
            for (t_it = tokenlist.begin(); t_it != tokenlist.end(); t_it++){    //scans whole tokenlist
                if (t_it->str == l_it->str){
                    t_it->str = l_it->info_str;     //substitutes content
                }
            }
        }
    }
    return 0;
}


int conditional_dir(list<Token> & tokenlist){
    
    return 0;
}
