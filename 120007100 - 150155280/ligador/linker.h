#ifndef LINKER_H_
#define LINKER_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
using namespace std;

/*--------------STRUCTS---------------*/
struct Symbol {
    string str;
    int atrb;
};
typedef struct Symbol Symbol;
/*------------------------------------*/

void 	linker(ifstream&, ifstream&, list<int>&);
int 	getBasic(ifstream&, ifstream&, list<int>&, list<int>&);
void 	getUseTable(ifstream&, ifstream&, list<Symbol>&, list<Symbol>&);
void 	getDefinitionTable(ifstream&, ifstream&, list<Symbol>&, int);
void 	link(ifstream&, ifstream&, list<int>&, list<int>&, list<Symbol>&, list<Symbol>&, list<Symbol>&, int, list<int>&);


#endif	//LINKER_H_