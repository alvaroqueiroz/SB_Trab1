/*
Universidade de Brasilia - 02/2018
CIC 116432 - Software Basico - Turma B
Professor Bruno Macchiavello
Trabalho Pratico 1 - Montador + Ligador

Alunos: Andre Abreu Rodrigues de Almeida    12/0007100
        Alvaro Queiroz dos Reis Silva       15/0155280
*/

#include <fstream>
#include <cstdlib>
#include <string>
#include <list>
#include "linker.h"
using namespace std;

int main (int argc, char** argv){
	list<int> object;
	string file_name;

	if (argc != 3){		// Check amount of inputs.
		fprintf(stderr, "[ERROR]: Invalid amount of arguments.\n");
    	printf("Usage:    .\\linker object_file1 object_file2\n");
    	printf("Obs: archives assumed to be .o extension.");
        exit(EXIT_FAILURE);
	}

	file_name = string(argv[1]) + ".o";
	ifstream ofile1( file_name.c_str() );	// Opens object file1.
	file_name = string(argv[2]) + ".o";
	ifstream ofile2( file_name.c_str() );	// Opens object file2.

	if (!ofile1){	// Check if open file1.
		fprintf(stderr, "[ERROR]: Failed to open file '%s.o'.\n", argv[1]);
        exit(EXIT_FAILURE);
	}
	if (!ofile2){	// Check if open file2.
		fprintf(stderr, "[ERROR]: Failed to open file '%s.o'.\n", argv[2]);
        exit(EXIT_FAILURE);
	}

	linker(ofile1, ofile2, object);

	/*create output file*/
    ofstream fpo ("linker_output.o");  //opens output file
    for (list<int>::iterator it = object.begin(); it != object.end(); it++){
    	fpo << *it << " ";
    }
    fpo.close();

	return 0;
}
