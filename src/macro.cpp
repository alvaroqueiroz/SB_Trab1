#include "macro.h"

// at this stage the code is considered correct.

void solve_macro(list<Token> & tokenlist){
	list<Macro> macrolist; 

	create_macrolist(tokenlist, macrolist);
	expand_macro(tokenlist, macrolist);
	erase_macro(tokenlist);

}

void create_macrolist(list<Token> & tokenlist, list<Macro> & macrolist){
	list<Token>::iterator it_tk, tmp_tk;
	list<Macro>::iterator it_mc, tmp_mc;
	Macro macro;
	int i, j;

	it_tk = tokenlist.begin();
	it_mc = macrolist.begin();
	while (it_tk != tokenlist.end()){		// go through entire token list.
		if (it_tk->type == TT_DIRECTIVE && it_tk->addit_info == DIR_MACRO){	// is macro?
			it_tk--;
			tmp_tk = it_tk;
			macro.str = it_tk->str.substr(0, it_tk->str.length()-1);		// store macro label.
			
			i = it_tk->line_number;		// store arg label.
			j = 0;
			while (i == it_tk->line_number){
				if (it_tk->type == TT_OPERAND){
					macro.arg[j] = it_tk->str;
					j++;
				}

				it_tk++;
			}
			macro.argn = j;				// store number of arg in macro.

			macro.start = it_tk;		// store body beginning point;
			i = 0;						// store body length
			while (it_tk->type != TT_DIRECTIVE && it_tk->addit_info != DIR_ENDMACRO){
				i++;
				it_tk++;
			}
			macro.body_length = i;
		} else {
			it_tk++;
		}
	}

}

void expand_macro(list<Token> & tokenlist, list<Macro> & macrolist){
	list<Token>::iterator it_tk, it_mc, tmp;

}

void erase_macro(list<Token> & tokenlist){
	
}