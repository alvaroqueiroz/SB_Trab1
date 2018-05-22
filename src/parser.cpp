#include "parser.h"

int parser (list <Token> & tokenlist, list <Token> & labellist){
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
			
			case TT_CONST:
				cout << "Sintax Error @ Line " << it->line_number << " - unexpected value." << endl;
				it++;
			break;

			default:
				cout << "Parser: unknowm token type." << endl;
				it++;
			break;
		}
	}

	return 0;
}

list<Token>::iterator parser_mnemonic(list <Token> & tokenlist, list<Token>::iterator it){
	int target_line;

	target_line = it->line_number;
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
			it++;
			if (it != tokenlist.end() && target_line == it->line_number){			// check if argument exists.
				if (it->type == TT_OPERAND){										// check if valid argument.
					it++;
					if (it != tokenlist.end() && target_line == it->line_number){	// check extra operation.
						if (it->type == TT_PLUS_OPERATOR){											// check if valid operation +.
							it++;
							if (it != tokenlist.end() && target_line == it->line_number){			// check if + argument exist.
								if (it->type == TT_CONST){											// check if + valid argument.
									it++;
									if (it != tokenlist.end() && target_line == it->line_number){	// check if too much arguments.
										cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
										do {		// get out of line.
											it++;
										} while(it != tokenlist.end() && target_line == it->line_number);
									}
								} else {
									cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
									do {		// get out of line.
										it++;
									} while(it != tokenlist.end() && target_line == it->line_number);
								}
							} else {
								cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
							}
						} else {
							cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
							do {		// get out of line.
								it++;
							} while(it != tokenlist.end() && target_line == it->line_number);
						}
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
					do {		// get out of line.
						it++;
					} while(it != tokenlist.end() && target_line == it->line_number);
				}
			} else {
				cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
			}
		break;

		case OP_COPY:
			it++;
			if (it != tokenlist.end() && target_line == it->line_number){	// check if arguments exists.
				
				// first argument.
				if (it->type == TT_OPERAND){										// check if valid argument.
					it++;
					if (it != tokenlist.end() && target_line == it->line_number){	// check if next argument exist.
						if (it->type == TT_PLUS_OPERATOR){									// check if it is + operation.
							it++;
							if (it != tokenlist.end() && target_line == it->line_number){	// check if + argument exist.
								if (it->type == TT_CONST){									// check if + valid argument.
									it++;
									if (it == tokenlist.end() || target_line != it->line_number){	// check if next argument exist.
										cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
										break;		// get out of switch.
									}
								} else {
									cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
									do {		// get out of line.
										it++;
									} while(it != tokenlist.end() && target_line == it->line_number);
									break;		// get out of switch.
								}
							} else {
								cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
								break;		// get out of switch.
							}
						}
					} else {
						cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
						break;		// get out of switch.
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
					do {		// get out of line.
						it++;
					} while(it != tokenlist.end() && target_line == it->line_number);
					break;		// get out of switch.
				}

				// comma argument.
				if (it->type == TT_COMMA_OPERATOR){									// check if valid argument.
					it++;
					if (it == tokenlist.end() || target_line != it->line_number){	// check if next argument exist.
						cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
						break;		// get out of switch.
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
					do {		// get out of line.
						it++;
					} while(it != tokenlist.end() && target_line == it->line_number);
					break;
				}

				// second argument.
				if (it->type == TT_OPERAND){										// check if valid argument.
					it++;
					if (it != tokenlist.end() && target_line == it->line_number){	// check extra operation.
						if (it->type == TT_PLUS_OPERATOR){											// check if valid operation +.
							it++;
							if (it != tokenlist.end() && target_line == it->line_number){			// check if + argument exist.
								if (it->type == TT_CONST){											// check if + valid argument.
									it++;
									if (it != tokenlist.end() && target_line == it->line_number){	// check if too much arguments.
										cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
										do {		// get out of line.
											it++;
										} while(it != tokenlist.end() && target_line == it->line_number);
									}
								} else {
									cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
									do {		// get out of line.
										it++;
									} while(it != tokenlist.end() && target_line == it->line_number);
								}
							} else {
								cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
							}
						} else {
							cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
							do {		// get out of line.
								it++;
							} while(it != tokenlist.end() && target_line == it->line_number);
						}
					}
				} else {
					cout << "Sintax Error @ Line " << target_line << " - invalid argument." << endl;
					do {		// get out of line.
						it++;
					} while(it != tokenlist.end() && target_line == it->line_number);
				}

			} else {
				cout << "Sintax Error @ Line " << target_line << " - missing argument." << endl;
			}
		break;

		case OP_STOP:
			it++;
			if (it != tokenlist.end() && target_line == it->line_number){		// check if argument exist.
				cout << "Sintax Error @ Line " << target_line << " - unexpected argument." << endl;
				do {		// get out of line.
					it++;
				} while(it != tokenlist.end() && target_line == it->line_number);
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
	int target_line;

	target_line = it->line_number;
	switch (it->addit_info){
		case DIR_SECTION:
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		case DIR_SPACE:
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		case DIR_CONST:
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		case DIR_IF:
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		case DIR_MACRO:
		case DIR_ENDMACRO:
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		case DIR_EQU:	// if found in this stage, it must be an invalid EQU.
			do {		// get out of line.
				it++;
			} while(it != tokenlist.end() && target_line == it->line_number);
		break;

		default:
			cout << "Parser: unknowm directive token." << endl;
			it++;
		break;		
	}

	return it;
}