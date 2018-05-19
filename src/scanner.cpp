/*SCANNER:
* This program analyses the code searching for lexical errorsand divides the
*  text into tokens, organizing them in a token list.
* Tokens have 5 elements: string (str), line number, position in line (pos_il),
* type and additional information.
* The additional information field stores different values for different types:
*   - Mnemonics:  addit_info == OPCODE;
*   - Labels:     addit_info == '0' for valid labels and '-1' for invalid ones;
*   - Directives: addit_info == directive identifier from directives table;
*   - Operand:    addit_info == '0' for valid operands and '-1' for invalid ones;
*   - Dec Const:  addit_info == int constant value
*   - Hex Const:  addit_info == int constant value
*/

#include "scanner.h"
using namespace std;

//#define __DEBUG__


int scanner (char * s, list<Token> & tokenlist, list<Token> & labellist){
    identify_tokens(s, tokenlist);      //generates token list
    comma_operand(tokenlist);
    verify_tokens(tokenlist, labellist);       //verifies token lexic validity
    ifequ(tokenlist, labellist);
#ifdef __DEBUG__
    print_list (tokenlist);
    print_list (labellist);
#endif
    return 0;
}


int identify_tokens (char * s, list<Token> & tokenlist){
    string line;
    char semicolon = ';';

    int lcount = 1;
    int tcount = 0;
    Token vtoken;
    unsigned int i = 0;

    ifstream asmfile( s );  //opens ASM file
    if (asmfile){
        while(getline(asmfile, line)){  //scans whole file
            for (i=0; i<line.length(); i++)     // Turn all upper.
                line.at(i) = toupper(line.at(i));

            line = line.substr(0, line.find(semicolon));    //removes comments

            while (line.length() > 0){  //scans whole line

                // Eliminates desnecessary.
                i = 0;
                while (line.at(i) == ' ' || line.at(i) == '\t' || line.at(i) == '\n'){
                    i++;
                    if (i == line.length())     // Prevent error.
                        break;
                }
                line.erase(0, i);
                if (line.length() == 0){        // Check end line.
                    break;
                }

                i = 0;
                while (line.at(i) != ' ' && line.at(i) != '\t' && line.at(i) != '\n'){
                    i++;
                    if (i == line.length())     // Prevent error.
                        break;
                }

                vtoken.str = line.substr(0, i);             //gets new token.
                vtoken.token_pos_il = tcount;               //stores token order in line.
                vtoken.line_number = lcount;                //stores line number.
                tokenlist.insert(tokenlist.end(), vtoken);  //inserts token to token list.
                line.erase(0, vtoken.str.length() + 1);     //erases token and delimiter from line.
                tcount++;
            }
            tcount = 0;
            lcount++;
        }
    }else{
        fprintf(stderr, "[ERROR]: Falha ao abrir o arquivo '%s'.\n", s);
        exit(EXIT_FAILURE);
    }
    asmfile.close();    //closes ASM file
    return 0;
}


int comma_operand (list<Token> & tokenlist){
    list<Token>::iterator it, newit;
    string delimiter = ",";
    string substr1, substr2, substr3;
    Token newtoken;
    for (it = tokenlist.begin(); it != tokenlist.end(); it++){
        if (strstr(it->str.c_str(),",")){
            string substr1 = it->str.substr(0, it->str.find(delimiter));
            string substr2 = it->str.substr(it->str.find(delimiter),1);
            string substr3 = it->str.substr(it->str.find(delimiter)+1,it->str.length());

#ifdef __DEBUG__
    cout << "RESOLVE VIRGULA" << endl << "substr1 = " << substr1 << endl << "substr2 = " << substr2 << endl << "substr3 = " << substr3 << endl;
#endif

            it->str = substr1;
            newtoken.str = substr2;
            newtoken.line_number = it->line_number;
            newtoken.token_pos_il = it->token_pos_il+1;
            newtoken.type = TT_COMMA_OPERATOR;
            newtoken.addit_info = 0;
            it++;
            tokenlist.insert(it,newtoken);
            newtoken.str = substr3;
            newtoken.line_number = it->line_number;
            newtoken.token_pos_il = it->token_pos_il+1;
            it++;
            tokenlist.insert(it,newtoken);
            newit = it;
            while (newit->line_number == it->line_number){
                newit->token_pos_il++;
                newit++;
            }
        }
    }
    return 0;
}


int is_mnemonic(Token & token){
    if (token.str.compare("ADD") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_ADD;
        return OP_ADD;
    }else
    if (token.str.compare("SUB") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_SUB;
        return OP_SUB;
    }else
    if (token.str.compare("MULT") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_MULT;
        return OP_MULT;
    }else
    if (token.str.compare("DIV") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_DIV;
        return OP_DIV;
    }else
    if (token.str.compare("JMP") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMP;
        return OP_JMP;
    }else
    if (token.str.compare("JMPN") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPN;
        return OP_JMPN;
    }else
    if (token.str.compare("JMPP") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPP;
        return OP_JMPP;
    }else
    if (token.str.compare("JMPZ") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_JMPZ;
        return OP_JMPZ;
    }else
    if (token.str.compare("COPY") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_COPY;
        return OP_COPY;
    }else
    if (token.str.compare("LOAD") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_LOAD;
        return OP_LOAD;
    }else
    if (token.str.compare("STORE") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_STORE;
        return OP_STORE;
    }else
    if (token.str.compare("INPUT") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_INPUT;
        return OP_INPUT;
    }else
    if (token.str.compare("OUTPUT") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_OUTPUT;
        return OP_OUTPUT;
    }else
    if (token.str.compare("STOP") == 0){
        token.type = TT_MNEMONIC;
        token.addit_info = OP_STOP;
        return OP_STOP;
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_label(Token & token, list<Token> & labellist){
    unsigned int i;
    Token tmp;

    if (token.str.at(token.str.length()-1) == ':'){
        token.type = TT_LABEL;

        if (token.str.length()-1 < 1 || token.str.length()-1 > 20){     // Check length.
            cout << "Lexical Error @ Line " << token.line_number << " - invalid label length." << endl;
            token.addit_info = INVALID_TOKEN;
            return INVALID_TOKEN;
        }

        if (isdigit(token.str.at(0))){      // Check start with digit.
            cout << "Lexical Error @ Line " << token.line_number << " - invalid label, label can't start with a number." << endl;
            token.addit_info = INVALID_TOKEN;
            return INVALID_TOKEN;
        }

        for (i = 0; i < token.str.length()-1; i++){       // Check composition.
            if (!isalnum(token.str.at(i))){
                if (token.str.at(i) != '_'){
                    cout << "Lexical Error @ Line " << token.line_number << " - invalid label." << endl;
                    token.addit_info = INVALID_TOKEN;
                    return INVALID_TOKEN;
                }
            }
        }

        // Valid label.
        token.type = TT_LABEL;
        token.addit_info = 0;
        tmp = token;
        tmp.str = token.str.substr(0, token.str.length()-1);    // take just the name of the label.
        labellist.insert(labellist.end(), tmp);         // add label to labellist.
        return TT_LABEL;
    }
    return 0;
}


int is_directive(Token & token){
    if (token.str.compare("SECTION") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_SECTION;
        return DIR_SECTION;
    }else
    if (token.str.compare("SPACE") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_SPACE;
        return DIR_SPACE;
    }else
    if (token.str.compare("CONST") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_CONST;
        return DIR_CONST;
    }else
    if (token.str.compare("EQU") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_EQU;
        return DIR_EQU;
    }else
    if (token.str.compare("IF") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_IF;
        return DIR_IF;
    }else
    if (token.str.compare("MACRO") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_MACRO;
        return DIR_MACRO;
    }else
    if (token.str.compare("ENDMACRO") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_ENDMACRO;
        return DIR_ENDMACRO;
    }else
    if (token.str.compare("TEXT") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_TEXT;
        return DIR_TEXT;
    }else
    if (token.str.compare("DATA") == 0){
        token.type = TT_DIRECTIVE;
        token.addit_info = DIR_DATA;
        return DIR_DATA;
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_decimal(Token & token){
    unsigned int i = 0;
    char * cstr = new char [token.str.length()+1];
    strcpy (cstr, token.str.c_str());   //casts string to char* for compatibility with <cctype>
    if (cstr[0] == '-' || cstr[0] == '+'){
        strcpy (cstr, token.str.substr(1, token.str.length()).c_str()); //removes sign
    }
    for (i=0; i<strlen(cstr); i++){
        if (!isdigit(cstr[i])){  //checks if it is a decimal number
            break;      //exits if it's not
        }
    }
    if (i == strlen(cstr)){
        token.type = TT_DEC_CONST;      //stores token type
        token.addit_info = (int)strtol(token.str.c_str(), NULL, 0);  //stores int value
        return TT_DEC_CONST;
    }else if (i != 0 && token.str.compare(0, 2, "0x") && token.str.compare(0, 2, "0X")){
        token.type = TT_OPERAND;            //not constant type!!
        token.addit_info = INVALID_TOKEN;
        return INVALID_TOKEN;
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_hexadecimal(Token & token){
    unsigned int i = 0;
    char * cstr = new char [token.str.length()+1];
    string s;
    if (!token.str.compare(0, 2, "0x") || !token.str.compare(0, 2, "0X")){    //IF HAS HEX IDENTIFIER
        s = token.str.substr(2, token.str.length()); // removes HEX identifier
        cstr[s.length()] = '\0';
        strcpy (cstr, s.c_str());   //casts string to char* for compatibility with <cctype>
        for (i=0; i<=s.length(); i++){
            if (!isdigit(cstr[i]) && cstr[i] != 'A' && cstr[i] != 'a' && cstr[i] != 'B'
                            && cstr[i] != 'b' && cstr[i] != 'C' && cstr[i] != 'c'
                            && cstr[i] != 'D' && cstr[i] != 'd' && cstr[i] != 'E'
                            && cstr[i] != 'e' && cstr[i] != 'F' && cstr[i] != 'f')  //checks if it is an hexadecimal number
                break;      //exits if it's not
        }
        if (i==s.length()){
            token.type = TT_HEX_CONST;      //stores token type
            token.addit_info = (int)strtol(token.str.c_str(), NULL, 16);  //stores int value
            return TT_HEX_CONST;
        }else{
            token.type = TT_OPERAND;            //not constant type!!
            token.addit_info = INVALID_TOKEN;
            return INVALID_TOKEN;
        }
    }
    token.type = 0;
    token.addit_info = 0;
    return 0;
}


int is_operand(Token & token){
    unsigned int i = 0;
    token.type = TT_OPERAND;
    char * cstr = new char [token.str.length()+1];
    strcpy (cstr, token.str.c_str());   //casts string to char* for compatibility with <cctype>
    for (i=0; i<token.str.length(); i++){
        if (!isalpha(cstr[0]))
            break;
        if (!isalnum(cstr[i]) && cstr[i] != '_' && cstr[i] != ',')
            break;
    }
    if (i == token.str.length()){
        token.addit_info = 0;
        return TT_OPERAND;
    }
    token.addit_info = INVALID_TOKEN;
    return TT_OPERAND;
}


int categorize_token(Token & token, list<Token> & labellist){
    token.type = 0;
    if (is_mnemonic(token))
        return TT_MNEMONIC;
    if (is_label(token, labellist))
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
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid mnemonic (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        case TT_LABEL:
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid label (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        case TT_DIRECTIVE:
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid directive (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        case TT_OPERAND:
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid operand (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        case TT_DEC_CONST:
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid decimal constant (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        case TT_HEX_CONST:
            if (token.addit_info == INVALID_TOKEN){
                fprintf(stderr, "Lexical error @ line %d - Invalid hexadecimal constant (%s).\n", token.line_number, token.str.c_str());
                pre_error = 1;
            }
            break;
        default:
            break;
    }
}


void verify_tokens (list<Token> & tokenlist, list<Token> & labellist){
/*categorizes the token into six types: Mnemonic, Label, Decimal Constant, Hexadecimal Constant, Directive and Operand
**analyses the formation of each token and generates error messages for mistackes
*/
    list<Token>::iterator it = tokenlist.begin();
    for (it = tokenlist.begin();it != tokenlist.end(); it++){
        categorize_token(*it, labellist);

#ifdef __DEBUG__
        cout << "Token: " << it->str << "  type: " << it->type << "  info: " << it->addit_info << endl;
#endif

        //lexic_analisys(*it);
    }
}
