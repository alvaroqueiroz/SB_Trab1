#include "parser.h"

int parser (list <Token> & tokenlist){
	list<Token>::iterator it;

	it = tokenlist.begin();
	while (it != tokenlist.end()){		// Check key tokens.
		switch (it->type){
			case TT_MNEMONIC:
				it = parser_mnemonic(tokenlist, it);
			break;

			case TT_LABEL:
				it++;
			break;

			case TT_DIRECTIVE:
				it = parser_directive(tokenlist, it);
			break;
			
			case TT_OPERAND:
				cout << "Sintax Error @ Line " << it->line_number << " - unexpected operand." << endl;
				it++;
			break;
			
			case TT_DEC_CONST:
			case TT_HEX_CONST:
				cout << "Sintax Error @ Line " << it->line_number << " - unexpected value." << endl;
				it++;
			break;

			default:
				cout << "Parser: unknowm type token." << endl;
				it++;
			break;
		}
	}

	return 0;
}

list<Token>::iterator parser_mnemonic(list <Token> & tokenlist, list<Token>::iterator it){
	static int target_line;

	switch (it->addit_info){
		case OP_ADD:
		case OP_SUB:
		case OP_MULT:
		case OP_DIV:
		case OP_JMP:
		case OP_JMPN:
		case OP_JMPP:
		case OP_JMPZ:
		case OP_LOAD:
		case OP_STORE:
		case OP_INPUT:
		case OP_OUTPUT:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->type == TT_OPERAND){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if(target_line == it->line_number){		// Check excess of operands.
								cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
								do {								// Get out of this line.
									it++;
									if (it == tokenlist.end()){		// Check end of token list to avoid errors.
										break;
									}
								} while (target_line == it->line_number);
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument, expected one operand." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
			}
		break;

		case OP_COPY:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->type == TT_OPERAND){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if (target_line == it->line_number){
								if (it->type == TT_OPERAND){
									it++;
									if(target_line == it->line_number){		// Check excess of operands.
										cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
										do {								// Get out of this line.
											it++;
											if (it == tokenlist.end()){		// Check end of token list to avoid errors.
												break;
											}
										} while (target_line == it->line_number);
									}
								} else{
									cout << "Sintax Error @ Line " << target_line << " - invalid argument, expected two operands." << endl;
									do {								// Get out of this line.
										it++;
										if (it == tokenlist.end()){		// Check end of token list to avoid errors.
											break;
										}
									} while (target_line == it->line_number);
								}
							} else{
								cout << "Sintax Error @ Line " << target_line << " - expected two arguments here." << endl;
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument, expected two operands." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected two arguments here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected two arguments here." << endl;
			}
		break;

		case OP_STOP:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check excess of arguments.
					cout << "Sintax Error @ Line " << target_line << " - unexpected arguments." << endl;
					do {								// Get out of this line.
						it++;
						if (it == tokenlist.end()){		// Check end of token list to avoid errors.
							break;
						}
					} while (target_line == it->line_number);
				}
			}
		break;

		default:
			cout << "Parser: unknowm mnemonic token." << endl;
			it++;
		break;
	}

	return it;
}

list<Token>::iterator parser_directive(list <Token> & tokenlist, list<Token>::iterator it){
	static int target_line;

	switch (it->addit_info){
		case DIR_SECTION:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->str.compare("TEXT") == 0 || it->str.compare("DATA") == 0){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if(target_line == it->line_number){		// Check excess of operands.
								cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
								do {								// Get out of this line.
									it++;
									if (it == tokenlist.end()){		// Check end of token list to avoid errors.
										break;
									}
								} while (target_line == it->line_number);
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument, expected TEXT or DATA." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected argument TEXT or DATA here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected argument TEXT or DATA here." << endl;
			}
		break;

		case DIR_SPACE:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->type == TT_DEC_CONST){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if(target_line == it->line_number){		// Check excess of operands.
								cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
								do {								// Get out of this line.
									it++;
									if (it == tokenlist.end()){		// Check end of token list to avoid errors.
										break;
									}
								} while (target_line == it->line_number);
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				}
			}
		break;

		case DIR_CONST:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->type == TT_HEX_CONST  || it->type == TT_DEC_CONST){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if(target_line == it->line_number){		// Check excess of operands.
								cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
								do {								// Get out of this line.
									it++;
									if (it == tokenlist.end()){		// Check end of token list to avoid errors.
										break;
									}
								} while (target_line == it->line_number);
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument, expected one constant." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
			}
		break;

		case DIR_EQU:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					it++;
					if (it != tokenlist.end()){		// Check end of token list to avoid errors.
						if(target_line == it->line_number){		// Check excess of operands.
							cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
							do {								// Get out of this line.
								it++;
								if (it == tokenlist.end()){		// Check end of token list to avoid errors.
									break;
								}
							} while (target_line == it->line_number);
						}
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
			}
		break;

		case DIR_IF:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check the presence of operand.
					if (it->type == TT_OPERAND || it->type == TT_DEC_CONST){		// Check if the operand is valid.	
						it++;
						if (it != tokenlist.end()){		// Check end of token list to avoid errors.
							if(target_line == it->line_number){		// Check excess of operands.
								cout << "Sintax Error @ Line " << target_line << " - too much arguments." << endl;
								do {								// Get out of this line.
									it++;
									if (it == tokenlist.end()){		// Check end of token list to avoid errors.
										break;
									}
								} while (target_line == it->line_number);
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
						do {								// Get out of this line.
							it++;
							if (it == tokenlist.end()){		// Check end of token list to avoid errors.
								break;
							}
						} while (target_line == it->line_number);
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
				}
			}else {
				cout << "Sintax Error @ Line " << target_line << " - expected one argument here." << endl;
			}
		break;

		case DIR_MACRO:
		case DIR_ENDMACRO:
			target_line = it->line_number;
			it++;
			if (it != tokenlist.end()){					// Check end of token list to avoid errors.
				if (target_line == it->line_number){	// Check excess of arguments.
					cout << "Sintax Error @ Line " << target_line << " - unexpected arguments." << endl;
					do {								// Get out of this line.
						it++;
						if (it == tokenlist.end()){		// Check end of token list to avoid errors.
							break;
						}
					} while (target_line == it->line_number);
				}
			}
		break;

		default:
			cout << "Parser: unknowm directive token." << endl;
			it++;
		break;		
	}

	return it;
}