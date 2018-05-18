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
void label_spc_fix (std::list<Token> & tokenlist);
int comma_operand (std::list<Token> & tokenlist);

#endif /* SCANNER_H_ */
