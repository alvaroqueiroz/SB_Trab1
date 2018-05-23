#include "semantic_analyser.h"
using namespace std;


int semantic_analyser(list <Token> & tokenlist, list <Token> & labellist){
    list <Token> datalist, textlist;
    int err = 0;
    err+=duplicate_label(labellist);
    err+=section_placement(tokenlist);
//    get_sublists(tokenlist, textlist, datalist);
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
                cerr << "Semantic Error @ Line " << aux->line_number << " - multiple declarations of label '" << aux->str <<"'." << endl;
                cerr << "\t\tPrevious declaration @ line " << it->line_number << "." << endl;
                pre_error = 1;
                err++;
            }
            aux++;
        }
    }
    return err;
}

int section_placement (list <Token> & tokenlist){
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
                }
            }else if (count == 1 && err == 0){      //second section
                if (!(it->type == TT_DIRECTIVE && it->addit_info == DIR_DATA)){     //not data section
                    fprintf(stderr, "Semantic error @ line %d - Expected 'DATA' section!\n", it->line_number);
                    pre_error = 1;
                    err++;
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
    return err;
}


int get_sublists (list <Token> & tokenlist, list <Token> & textlist, list <Token> & datalist){
    list <Token>::iterator it = tokenlist.begin();
    while (it->type != TT_DIRECTIVE && it->addit_info != DIR_SECTION && it->flag != -1 && it != tokenlist.end()){
        it++;
    }
    advance (it, 2);
    while (it->type != TT_DIRECTIVE && it->addit_info != DIR_SECTION && it->flag != -1 && it != tokenlist.end()){
        textlist.push_back(*it);
    }
    advance (it, 2);
    while (it->type != TT_DIRECTIVE && it->addit_info != DIR_SECTION && it->flag != -1 && it != tokenlist.end()){
        datalist.push_back(*it);
    }
    return 0;
}
