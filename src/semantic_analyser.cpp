#include "semantic_analyser.h"
using namespace std;

/*
* SEMANTIC ANALYSER
* Inputs: tokenlist and labellist
* Output: number of semantic errors
* -----------------------------------------
* Cases analysed:
* - multiple declarations of label;
* - section errors (missing section/wrong order/too many sections)
* - missing labels from data section
* - unused label from data section (warning)
* - Data definition declared as Text label
*/

/*
especificações de roteiro

(/)    – declarações e rótulos ausentes;
(X)    – declarações e rótulos repetidos;
( )    – pulo para rótulos inválidos; – pulo para seção errada;
(X)    – diretivas inválidas;
(X)    – instruções inválidas;
( )    – diretivas ou instruções na seção errada;
( )    – divisão por zero (para constante);
(X)    – instruções com a quantidade de operando inválida; – tokens inválidos;
(X)    – dois rótulos na mesma linha;
(X)    – seção TEXT faltante;
( )    – seção inválida;
( )    – tipo de argumento inválido;
( )    – modificação de um valor constante;

*/


int semantic_analyser(list <Token> & tokenlist, list <Token> & labellist){
    list <Token> datalist, textlist;
    list<Token>::iterator text_it, data_it;
    int err = 0;
    int hasdatasec = 0;
    err+=duplicate_label(labellist);
    err+=section_placement(tokenlist, text_it, data_it, hasdatasec);
    if (err == 0 && hasdatasec){
        err+=check_symbols_from_data(tokenlist, data_it);
    } else if (err == 0){
        err+=check_for_data_need(tokenlist);
    }
    err+=defaslabel(tokenlist, data_it);

    return err;
}


int duplicate_label (list <Token> & labellist){
    list<Token>::iterator it, aux, end;
    int err = 0;
    end=labellist.end();
    end--;              //stops loop one before
    for (it=labellist.begin(); it != end; it++){
        aux=it;
        aux++;
        while(aux != labellist.end()){
            if (it->str == aux->str){
                cerr << "Semantic Error @ Line " << aux->line_number << " - multiple declarations of '" << aux->str <<"'." << endl;
                cerr << "\t\tPrevious declaration @ line " << it->line_number << "." << endl;
                pre_error = 1;
                err++;
            }
            aux++;
        }
    }
    return err;
}


int section_placement (list <Token> & tokenlist, list<Token>::iterator & text, list<Token>::iterator & data, int & hasdatasec){
    list<Token>::iterator it = tokenlist.begin();
    int err = 0;
    int count = 0;
    while (it != tokenlist.end()){
        if (it->type == TT_DIRECTIVE && it->addit_info == DIR_SECTION && it->flag != -1){     //if section
            it++;
            if (count == 0){    //if first section
                if (!(it->type == TT_DIRECTIVE && it->addit_info == DIR_TEXT)){     //if not section text
                    fprintf(stderr, "Semantic error @ line %d - Expected 'TEXT' section!\n", it->line_number);
                    pre_error = 1;
                    err++;
                }else{
                    text = it;
                }
            }else if (count == 1 && err == 0){      //second section
                if (!(it->type == TT_DIRECTIVE && it->addit_info == DIR_DATA)){     //not data section
                    fprintf(stderr, "Semantic error @ line %d - Expected 'DATA' section!\n", it->line_number);
                    pre_error = 1;
                    err++;
                }else{
                    data = it;
                }
            }else if (err == 0){    //third+ section
                fprintf(stderr, "Semantic error @ line %d - Too many sections!\n", it->line_number);
                pre_error = 1;
                err++;
            }
            count++;
        }
        it++;
    }
    if (it == tokenlist.end() && count == 0){   //no section
        fprintf(stderr, "Semantic error - No section found!\n");
        pre_error = 1;
        err++;
    }
    if (count == 2){
        hasdatasec = 1;
    }
    return err;
}


int check_symbols_from_data(list <Token> & tokenlist, list<Token>::iterator data_begin){
    int err = 0;
    list<Token>::iterator it, data_it, aux;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (it->type == TT_OPERAND && it->addit_info != -1 && it->flag != -1){
            for (data_it = data_begin; data_it != tokenlist.end(); data_it++){
                if (data_it->type == TT_LABEL){
                    if (data_it->str.substr(0, data_it->str.find(":")) == it->str){
                        data_it->flag = 100;        //marks data flags that are related to an operand
                        break;
                    }
                }
            }
            if (data_it == tokenlist.end()){
                aux = it;
                aux--;
                if (!(aux->type == TT_MNEMONIC && (aux->addit_info == OP_JMP ||\
                                                aux->addit_info == OP_JMPN ||\
                                                aux->addit_info == OP_JMPP ||\
                                                aux->addit_info == OP_JMPZ))){
                    aux++;
                    fprintf(stderr, "Semantic error @ line %d - Argument '%s' not declared in DATA section.\n", it->line_number, it->str.c_str());
                    pre_error = 1;
                    err++;
                }
            }
        }
    }
    for (data_it = data_begin; data_it != tokenlist.end(); data_it++){
        if (data_it->type == TT_LABEL && data_it->flag != 100 && data_it->addit_info != -1){
            fprintf(stderr, "Warning @ line %d - Unused '%s' argument.\n", data_it->line_number, data_it->str.c_str());
            //pre_error = 1;
            //err++;
        }
    }
    return err;
}


int check_for_data_need(list <Token> & tokenlist){
    int err = 0;
    int i = 0;
    list<Token>::iterator it, aux;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (it->type == TT_OPERAND && it->addit_info != -1 && it->flag != -1){
            aux = it;
            aux--;
            if (!(aux->type == TT_MNEMONIC && (aux->addit_info == OP_JMP ||\
                                            aux->addit_info == OP_JMPN ||\
                                            aux->addit_info == OP_JMPP ||\
                                            aux->addit_info == OP_JMPZ))){
                fprintf(stderr, "Semantic error @ line %d - No DATA section - Argument '%s' not declared.\n", it->line_number, it->str.c_str());
                pre_error = 1;
                err++;
                i = 1;
            }
        }
    }
    if (i==1){
        fprintf(stderr, "Semantic error - Expected 'DATA' section!\n");
    }
    return err;
}


int defaslabel(list<Token> & tokenlist, list<Token>::iterator data_it){
    int err = 0;
    list<Token>::iterator it, newit, aux;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (it->type == TT_OPERAND && it->addit_info != -1 && it->flag != -1){
            aux = it;
            aux--;
            if (!(aux->type == TT_MNEMONIC && (aux->addit_info == OP_JMP ||\
                                            aux->addit_info == OP_JMPN ||\
                                            aux->addit_info == OP_JMPP ||\
                                            aux->addit_info == OP_JMPZ))){
                for (newit=tokenlist.begin();newit != data_it && newit != tokenlist.end(); newit++){
                    if ( (newit->str.substr(0, newit->str.find(":")) == it->str) && \
                                        (newit->type == TT_LABEL) && \
                                        (newit->line_number != it->line_number) && \
                                        (newit->token_pos_il != it->token_pos_il) ){
                        fprintf(stderr, "Semantic error @ line %d - Definition from line %d (%s) declared as TEXT label in line %d.\n", it->line_number, it->line_number, it->str.c_str(), newit->line_number);
                    }
                }
            }
        }
    }
    return err;
}
