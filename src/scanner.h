#ifndef SCANNER_H_
#define SCANNER_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include "pre_processor.h"

int scanner(char * file_name, std::list <Token> & tokenlist);
int identify_tokens (char * s, std::list <Token> & tokenlist);
void rm_spaces (std::list <Token> & tokenlist);
void verify_tokens (std::list <Token> & tokenlist);
void print_tokenlist (std::list <Token> & tokenlist);

#endif /* SCANNER_H_ */
