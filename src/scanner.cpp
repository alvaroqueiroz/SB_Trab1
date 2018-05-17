#include "scanner.h"
using namespace std;

int scanner (char * s, list<Token> & tokenlist){
    identify_tokens(s, tokenlist);      //generates token list
    print_tokenlist (tokenlist);
    rm_spaces(tokenlist);     //removes blank spaces
    print_tokenlist (tokenlist);
    verify_tokens(tokenlist);     //verifies token lexic validity
    return 0;
}


int identify_tokens (char * s, list<Token> & tokenlist){
    ifstream asmfile( s );  //opens ASM file
    string line;
    string delimiter = " ";
    string semicolon = ";";
    int lcount = 0;
    int tcount = 0;
    Token vtoken;
    if (asmfile){
        while(getline(asmfile, line)){  //scans whole file
        line = line.substr(0, line.find(semicolon));    //removes comments
            while (line.length() > 0){  //scans whole line
                vtoken.str = line.substr(0, line.find(delimiter));   //gets new token
                line.erase(0, vtoken.str.length() + delimiter.length()); //erases token from line
                vtoken.token_pos_il = tcount;   //stores token order in line
                vtoken.line_number = lcount;    //stores line number
                tokenlist.insert(tokenlist.end(), vtoken);   //inserts token to token list
                tcount++;
            }
        tcount = 0;
        lcount++;
        }
    }else{
        fprintf(stderr, "[ERRO]: Falha ao abrir o arquivo '%s'.\n", s);
        exit(EXIT_FAILURE);
    }
    asmfile.close();    //closes ASM file
    return 0;
}


void rm_spaces (list<Token> & tokenlist){
    list<Token>::iterator it, newit;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (it->str == "" || it->str == " " || it->str == "\n"){
            newit = it = tokenlist.erase(it); //erases node and advances iterator
            it--;   //places iterator back to place (bug fix for Linux)
            while (newit->line_number == it->line_number){
                newit->token_pos_il--;
                newit++;
            }
        }
    }
}


int is_mnemonic(Token & token){
    if (token.str.compare("ADD") == 0 || token.str.compare("add") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_ADD;
        return OP_ADD;
    }else if (token.str.compare("SUB") == 0 || token.str.compare("sub") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_SUB;
        return OP_SUB;
    }else if (token.str.compare("MULT") == 0 || token.str.compare("mult") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_MULT;
        return OP_MULT;
    }else if (token.str.compare("DIV") == 0 || token.str.compare("div") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_DIV;
        return OP_DIV;
    }else if (token.str.compare("JMP") == 0 || token.str.compare("jmp") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMP;
        return OP_JMP;
    }else if (token.str.compare("JMPN") == 0 || token.str.compare("jmpn") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPN;
        return OP_JMPN;
    }else if (token.str.compare("JMPP") == 0 || token.str.compare("jmpp") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPP;
        return OP_JMPP;
    }else if (token.str.compare("JMPZ") == 0 || token.str.compare("jmpz") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPZ;
        return OP_JMPZ;
    }else if (token.str.compare("COPY") == 0 || token.str.compare("copy") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_COPY;
        return OP_COPY;
    }else if (token.str.compare("LOAD") == 0 || token.str.compare("load") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_LOAD;
        return OP_LOAD;
    }else if (token.str.compare("STORE") == 0 || token.str.compare("store") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_STORE;
        return OP_STORE;
    }else if (token.str.compare("INPUT") == 0 || token.str.compare("input") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_INPUT;
        return OP_INPUT;
    }else if (token.str.compare("OUTPUT") == 0 || token.str.compare("output") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_OUTPUT;
        return OP_OUTPUT;
    }else if (token.str.compare("STOP") == 0 || token.str.compare("stop") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_STOP;
        return OP_STOP;
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_label(Token & token){
    char ch = token.str.back();
    if (ch == ':'){
        token.type = TT_LABEL;
        token.addit_info = 0;
        return TT_LABEL;
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_directive(Token & token){
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_operand(Token & token){
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_decimal(Token & token){
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_hexadecimal(Token & token){
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int categorize_token(Token & token){
    token.type = 0;
    if (is_mnemonic(token))
        return TT_MNEMONIC;
    if (is_label(token))
        return TT_LABEL;
    if (is_directive(token))
        return TT_DIRECTIVE;
    if (is_decimal(token))
        return TT_DEC_CONST;
    if (is_hexadecimal(token))
        return TT_HEX_CONST;
    if (is_operand(token))
        return TT_OPERAND;
    token.type = -1;
    return -1;
}


void lexic_analisys(Token & token){
    switch (token.type){
        case TT_MNEMONIC:
            break;
        case TT_LABEL:
            break;
        case TT_DIRECTIVE:
            break;
        case TT_OPERAND:
            break;
        case TT_DEC_CONST:
            break;
        case TT_HEX_CONST:
            break;
        default:
            break;
    }
}


void verify_tokens (list<Token> & tokenlist){
/*categorizes the token into six types: Mnemonic, Label, Decimal Constant, Hexadecimal Constant, Directive and Operand
**analyses the formation of each token and generates error messages for mistackes
*/
    list<Token>::iterator it = tokenlist.begin();
    for (it = tokenlist.begin();it != tokenlist.end(); it++){
        categorize_token(*it);
        lexic_analisys(*it);
        cout << it->type << " " << it->addit_info << endl;
    }
}


void print_tokenlist (list<Token> & tokenlist){
    cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
    list<Token>::iterator it;
    for (it = tokenlist.begin();it != tokenlist.end(); it++)
        cout << "Token: " << it->str << "   Line: " << it->line_number << " Number: " << it->token_pos_il << endl;  //print list element
    cout << "-----------------\n";
}
