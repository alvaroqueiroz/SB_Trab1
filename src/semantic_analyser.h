#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include "pre_processor.h"

int semantic_analyser(std::list <Token> & tokenlist, std::list <Token> & labellist);
int duplicate_label (std::list <Token> & labellist);
int section_placement (std::list <Token> & tokenlist, std::list<Token>::iterator & text, std::list<Token>::iterator & data, int & hasdatasec);
int get_sublists (std::list <Token> & tokenlist, std::list <Token> & textlist, std::list <Token> & datalist);
int check_symbols_from_data(std::list <Token> & tokenlist, std::list<Token>::iterator data_it);
int check_for_data_need(std::list <Token> & tokenlist);
int defaslabel(std::list<Token> & tokenlist, std::list<Token>::iterator data_it);

extern int pre_error;

#endif /* SEMANTIC_H_ */
