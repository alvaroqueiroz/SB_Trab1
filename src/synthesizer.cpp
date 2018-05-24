#include "synthesizer.h"
using namespace std;


int synthesizer (list<Token> & tokenlist){
	list<Symbol> symboltable;

	first_pass(tokenlist, symboltable);
	second_pass(tokenlist, symboltable);

    return 0;
}
