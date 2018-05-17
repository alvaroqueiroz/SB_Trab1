#ifndef SCANNER_H_
#define SCANNER_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include "pre_processor.h"

int scanner(char * file_name, std::list<Token> & tokenlist);
int identify_tokens (char * s, std::list<Token> & tokenlist);
void rm_spaces (std::list<Token> & tokenlist);
void verify_tokens (std::list<Token> & tokenlist);
void print_tokenlist (std::list<Token> & tokenlist);
int categorize_token(Token & token);
void lexic_analisys(Token & token);
int is_mnemonic(Token & token);
int is_label(Token & token);
int is_directive(Token & token);
int is_operand(Token & token);
int is_decimal(Token & token);
int is_hexadecimal(Token & token);


#endif /* SCANNER_H_ */
