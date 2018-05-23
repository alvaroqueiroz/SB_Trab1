#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include "pre_processor.h"

int semantic_analyser(std::list <Token> & tokenlist, std::list <Token> & labellist);
int duplicate_label (std::list <Token> & labellist);
int section_placement (std::list <Token> & tokenlist);
int get_sublists (std::list <Token> & tokenlist, std::list <Token> & textlist, std::list <Token> & datalist);

#endif /* SEMANTIC_H_ */
