#include "linker.h"

#define DEBUG_

void linker(ifstream& ofile1, ifstream& ofile2, list<int>& object){
	int ofile1_size = 0;
	list<int> realoc1, realoc2;
	list<Symbol> ut1, ut2, definT;

	ofile1_size = getBasic(ofile1, ofile2, realoc1, realoc2);
	getDefinitionTable(ofile1, ofile2, definT, ofile1_size);
	getUseTable(ofile1, ofile2, ut1, ut2);
	link(ofile1, ofile2, realoc1, realoc2, definT, ut1, ut2, ofile1_size, object);
}

int getBasic(ifstream& ofile1, ifstream& ofile2, list<int>& realoc1, list<int>& realoc2){
	int i;
	int size = 0;
	string line1, line2;

	// Remove HEAD:.
	getline(ofile1, line1);
	getline(ofile2, line2);

	// Remove name.
	getline(ofile1, line1);
	getline(ofile2, line2);
	#ifdef	DEBUG_
		printf("%s..\n", line1.c_str());
		printf("%s..\n", line2.c_str());
	#endif

	// Remove size.
	getline(ofile1, line1);
	getline(ofile2, line2);
	#ifdef	DEBUG_
		printf("%s..\n", line1.c_str());
		printf("%s..\n", line2.c_str());
	#endif
		// Get size offset of file1.
	line1 = line1.substr(3, line1.length());
	size = atoi(line1.c_str());
	#ifdef	DEBUG_
		printf("%d\n", size);
	#endif

	// Remove realoc.
	getline(ofile1, line1);
	getline(ofile2, line2);
	#ifdef	DEBUG_
		printf("%s..\n", line1.c_str());
		printf("%s..\n", line2.c_str());
	#endif
		// Get realoc file1.
	for (i = 0; -(4+i*2 - (long)line1.size()) > 0; i++){
		realoc1.insert(realoc1.end(), atoi(line1.substr(3+i*2, 4+i*2).c_str()));
	}
		// Get realoc file2.
	for (i = 0; -(4+i*2 - (long)line2.size()) > 0; i++){
		realoc2.insert(realoc2.end(), atoi(line2.substr(3+i*2, 4+i*2).c_str()));
	}
	#ifdef	DEBUG_
		for(list<int>::iterator it = realoc1.begin(); it != realoc1.end(); it++){
			printf("%d", *it);
		}
		printf("\n");
		for(list<int>::iterator it = realoc2.begin(); it != realoc2.end(); it++){
			printf("%d", *it);
		}
		printf("\n");
	#endif

	return size;
}

void getUseTable(ifstream& ofile1, ifstream& ofile2, list<Symbol>& useT1, list<Symbol>& useT2){
	string line;
	Symbol symb;

	if(ofile1.peek() == 'U'){
		// Remove file definition table.
		getline(ofile1, line);
		#ifdef	DEBUG_
			printf("%s..\n", line.c_str());
		#endif

		line.erase(0, 3);	// Remove "U. ".
		while(line.size() > 0){
			symb.str = line.substr(0, line.find(' '));
			line.erase(0, line.find(' ')+1);
			symb.atrb = atoi(line.substr(0, line.find(' ')+1).c_str());
			line.erase(0, line.find(' ')+1);
			useT1.insert(useT1.end(), symb);
			#ifdef	DEBUG_
				printf("%s..", symb.str.c_str());
				printf("%d\n", symb.atrb);
			#endif
		}
	}
	if(ofile2.peek() == 'U'){
		// Remove file definition table.
		getline(ofile2, line);
		#ifdef	DEBUG_
			printf("%s..\n", line.c_str());
		#endif

		line.erase(0, 3);	// Remove "U. ".
		while(line.size() > 0){
			symb.str = line.substr(0, line.find(' '));
			line.erase(0, line.find(' ')+1);
			symb.atrb = atoi(line.substr(0, line.find(' ')+1).c_str());
			line.erase(0, line.find(' ')+1);
			useT2.insert(useT2.end(), symb);
			#ifdef	DEBUG_
				printf("%s..", symb.str.c_str());
				printf("%d\n", symb.atrb);
			#endif
		}
	}
}

void getDefinitionTable(ifstream& ofile1, ifstream& ofile2, list<Symbol>& definT, int offset){
	string line;
	Symbol symb;

	if(ofile1.peek() == 'D'){
		// Remove file definition table.
		getline(ofile1, line);
		#ifdef	DEBUG_
			printf("%s..\n", line.c_str());
		#endif

		line.erase(0, 3);	// Remove "D. ".
		while(line.size() > 0){
			symb.str = line.substr(0, line.find(' '));
			line.erase(0, line.find(' ')+1);
			symb.atrb = atoi(line.substr(0, line.find(' ')+1).c_str());
			line.erase(0, line.find(' ')+1);
			definT.insert(definT.end(), symb);
			#ifdef	DEBUG_
				printf("%s..", symb.str.c_str());
				printf("%d\n", symb.atrb);
			#endif
		}
	}
	if(ofile2.peek() == 'D'){
		// Remove file definition table.
		getline(ofile2, line);
		#ifdef	DEBUG_
			printf("%s..\n", line.c_str());
		#endif

		line.erase(0, 3);	// Remove "D. ".
		while(line.size() > 0){
			symb.str = line.substr(0, line.find(' '));
			line.erase(0, line.find(' ')+1);
			symb.atrb = atoi(line.substr(0, line.find(' ')+1).c_str()) + offset;
			line.erase(0, line.find(' ')+1);
			definT.insert(definT.end(), symb);
			#ifdef	DEBUG_
				printf("%s..", symb.str.c_str());
				printf("%d\n", symb.atrb);
			#endif
		}
	}
}

void link(ifstream& ofile1, ifstream& ofile2, list<int>& realoc1, list<int>& realoc2, list<Symbol>& definT, list<Symbol>& useT1, list<Symbol>& useT2, int offset, list<int>& object){
	string line;
	int code, count, flag, flag2;
	list<int>::iterator it_rloc;

	// Remove file1 code.
	getline(ofile1, line);
	#ifdef	DEBUG_
		printf("%s..\n", line.c_str());
	#endif

	line.erase(0, 6);	// Remove "TEXT: ".
	count = 0;
	while(line.size() > 0){
		// Get code fragment.
		code = atoi(line.substr(0, line.find(' ')).c_str());
		line.erase(0, line.find(' ')+1);

		// Check if is use table related.
		for (list<Symbol>::iterator it = useT1.begin(); it != useT1.end(); it++){
			if(it->atrb == count){
				flag = 0;
				for(list<Symbol>::iterator ti = definT.begin(); ti != definT.end(); ti++){
					if(it->str == ti->str){
						code += ti->atrb;
						flag = 1;
						break;
					}
				}
				if (!flag){		// Error if the definition doesn't exist.
					fprintf(stderr, "[ERROR]: Definition of '%s' not found.\n", it->str.c_str());
        			exit(EXIT_FAILURE);
				}
				break;
			}
		}

		object.insert(object.end(), code);
		count++;

		#ifdef	DEBUG_
			printf("%d ", code);
		#endif
	}
	#ifdef	DEBUG_
		printf("\n");
	#endif

	// Remove file2 code.
	getline(ofile2, line);
	#ifdef	DEBUG_
		printf("%s..\n", line.c_str());
	#endif

	line.erase(0, 6);	// Remove "TEXT: ".
	count = 0;
	it_rloc = realoc2.begin();
	while(line.size() > 0){
		// Get code fragment.
		code = atoi(line.substr(0, line.find(' ')).c_str());
		line.erase(0, line.find(' ')+1);

		// Check if is use table related.
		flag2 = 0;
		for (list<Symbol>::iterator it = useT2.begin(); it != useT2.end(); it++){
			if(it->atrb == count){
				flag = 0;
				for(list<Symbol>::iterator ti = definT.begin(); ti != definT.end(); ti++){
					if(it->str == ti->str){
						code += ti->atrb;
						flag = 1;
						break;
					}
				}
				if (!flag){		// Error if the definition doesn't exist.
					fprintf(stderr, "[ERROR]: Definition of '%s' not found.\n", it->str.c_str());
        			exit(EXIT_FAILURE);
				}
				flag2 = 1;
				break;
			}
		}

		// Check if is not use table related and is realoc code.
		if ((!flag2) && (*it_rloc)) {
			code += offset;
		}

		object.insert(object.end(), code);
		count++;
		it_rloc++;

		#ifdef	DEBUG_
			printf("%d ", code);
		#endif
	}
	#ifdef	DEBUG_
		printf("\n");
	#endif
}