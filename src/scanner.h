#ifndef SCANNER_H_
#define SCANNER_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include "pre_processor.h"

int scanner(char * file_name, std::list<Token> & tokenlist, std::list<Token> & labellist);
int identify_tokens (char * s, std::list<Token> & tokenlist);

void verify_tokens (std::list<Token> & tokenlist, std::list<Token> & labellist);
int categorize_token(Token & token, std::list<Token> & labellist);
void lexic_analisys(Token & token);

int is_mnemonic(Token & token);
int is_label(Token & token, std::list<Token> & labellist);
int is_directive(Token & token);
int is_operand(Token & token);
int is_decimal(Token & token);
int is_hexadecimal(Token & token);

int comma_operand (std::list<Token> & tokenlist);

void print_tokenlist (std::list<Token> & tokenlist, std::list<Token> & labellist);

#endif /* SCANNER_H_ */
