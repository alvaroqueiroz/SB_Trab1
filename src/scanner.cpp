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

#define __DEBUG__


int scanner (char * s, list<Token> & tokenlist, list<Token> & labellist){
    identify_tokens(s, tokenlist);      //generates token list
    verify_tokens(tokenlist, labellist);       //verifies token lexic validity

#ifdef __DEBUG__
    print_tokenlist (tokenlist, labellist);
#endif
    return 0;
}


int identify_tokens (char * s, list<Token> & tokenlist){
    string line;
    char semicolon = ';';
    
    int lcount = 1;
    int tcount = 0;
    Token vtoken, tmp;
    unsigned int i = 0;

    ifstream asmfile( s );  //opens ASM file
    if (asmfile){
        while(getline(asmfile, line)){  //scans whole file
            for (i=0; i<line.length(); i++)     // Turn all upper.
                line.at(i) = toupper(line.at(i));

            line = line.substr(0, line.find(semicolon));    //removes comments

            while (line.length() > 0){  //scans whole line
                
                // Eliminates unnecessary.
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

                i = 0;      // find token end.
                while (line.at(i) != ' ' && line.at(i) != '\t' && line.at(i) != '\n'){
                    i++;
                    if (i == line.length())     // Prevent error.
                        break;
                }

                
                vtoken.str = line.substr(0, i);             //gets new token.
                // Check basic operators , and +.
                while(vtoken.str.find(",") != string::npos || vtoken.str.find("+") != string::npos){
                    if (vtoken.str.find(",") < vtoken.str.find("+")){
                        tmp.str = vtoken.str;
                        
                        if(vtoken.str.find(",") == 0){      //found in the beginning.
                            vtoken.str = vtoken.str.substr(0, 1);       //get , token.
                            vtoken.token_pos_il = tcount;               //stores token order in line.
                            vtoken.line_number = lcount;                //stores line number.

                            vtoken.type = TT_COMMA_OPERATOR;            //comma type token.
                            vtoken.addit_info = INVALID_TOKEN;          //invalid.
                            cout << "Sintax Error @ Line " << vtoken.line_number << " - invalid use of comma." << endl;

                            tokenlist.insert(tokenlist.end(), vtoken);  //inserts token to token list.
                            line.erase(0, 1);                           //erases token.
                            vtoken.str = tmp.str;
                            vtoken.str.erase(0, 1);                     //erases token.
                            tcount++;                                   //adivance token count.
                        }else {
                            vtoken.str = vtoken.str.substr(0, vtoken.str.find(","));       //get token.
                            vtoken.token_pos_il = tcount;               //stores token order in line.
                            vtoken.line_number = lcount;                //stores line number.
                            tokenlist.insert(tokenlist.end(), vtoken);  //inserts token to token list.
                            tcount++;

                            vtoken.str = ",";
                            if ()
                        }
                    } else{

                    }
                }

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
        fprintf(stderr, "[ERRO]: Falha ao abrir o arquivo '%s'.\n", s);
        exit(EXIT_FAILURE);
    }
    asmfile.close();    //closes ASM file
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

    if (token.str.at(token.str.length()-1) == ':'){     // Check if is label.
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
    unsigned int i;
    Token tmp;

    if(token.str.at(0) == '-' || token.str.at(0) == '+'){       // Check if has signal together.
        tmp.str = token.str.substr(1, token.str.length());
    } else {
        tmp.str = token.str;
    }
    
    for(i = 0; i < tmp.str.length(); i++){      // Check if is number.
        if(!isdigit(tmp.str.at(i))){
            return 0;
        }
    }

    // Is number decimal.
    token.type = TT_CONST;
    tmp.addit_info = atoi(token.str.c_str());
    if (tmp.addit_info > 32767 || tmp.addit_info < -32768){     // Check value range.
        cout << "Lexical Error @ Line " << token.line_number << " - invalid number." << endl;
        token.addit_info = INVALID_TOKEN;
        return INVALID_TOKEN;
    }

    // Valid number.
    token.addit_info = tmp.addit_info;
    return TT_CONST;
}


int is_hexadecimal(Token & token){
    unsigned int i;
    Token tmp;

    if(token.str.at(0) == '-' || token.str.at(0) == '+'){       // Check if has signal together.
        tmp.str = token.str.substr(1, token.str.length());
    } else {
        tmp.str = token.str;
    }

    if(tmp.str.compare(0, 2, "0X") == 0){       // Check the hexa indicator.
        tmp.str = tmp.str.substr(2, tmp.str.length());
    } else{
        return 0;   // not hexa.
    }

    for(i = 0; i < tmp.str.length(); i++){      // Check hexa content.
        if ((tmp.str.at(i) < 'A' || tmp.str.at(i) > 'F') && !isdigit(tmp.str.at(i))){
            return 0;   // not hexa.
        }
    }

    // Is number hexa.
    token.type = TT_CONST;
    tmp.addit_info = (int)strtol(token.str.c_str(), NULL, 16);
    if (tmp.addit_info > 32767 || tmp.addit_info < -32768){     // Check value range.
        cout << "Lexical Error @ Line " << token.line_number << " - invalid number." << endl;
        token.addit_info = INVALID_TOKEN;
        return INVALID_TOKEN;
    }

    // Valid number.
    token.str = to_string(tmp.addit_info);
    token.addit_info = tmp.addit_info;
    return TT_CONST;
}


int is_operand(Token & token, list<Token> & tokenlist){
    unsigned int i;

    if (token.str.find(",") != string::npos){     // Check if operand has , mixed.
        cout << "find-----------------" << endl;
    }

    if (token.str.find("+") != string::npos){     // Check if operand has + mixed.

    }

    // Is simple operand.
    token.type = TT_OPERAND;
    if (token.str.length() < 1 || token.str.length() > 20){     // Check length.
        cout << "Lexical Error @ Line " << token.line_number << " - invalid operand length." << endl;
        token.addit_info = INVALID_TOKEN;
        return INVALID_TOKEN;
    }

    if (isdigit(token.str.at(0))){      // Check start with digit.
        cout << "Lexical Error @ Line " << token.line_number << " - invalid operand, operand can't start with a number." << endl;
        token.addit_info = INVALID_TOKEN;
        return INVALID_TOKEN;
    }

    for (i = 0; i < token.str.length()-1; i++){       // Check composition.
        if (!isalnum(token.str.at(i))){
            if (token.str.at(i) != '_'){
                cout << "Lexical Error @ Line " << token.line_number << " - invalid operand." << endl;
                token.addit_info = INVALID_TOKEN;
                return INVALID_TOKEN;
            }
        }
    }

    // Valid operand.
    token.type = TT_OPERAND;
    token.addit_info = 0;
    return TT_OPERAND;
}


int categorize_token(Token & token, list<Token> & labellist, list<Token> & tokenlist){
    token.type = 0;
    if (is_mnemonic(token))
        return TT_MNEMONIC;
    if (is_label(token, labellist))
        return TT_LABEL;
    if (is_directive(token))
        return TT_DIRECTIVE;
    if (is_decimal(token))
        return TT_CONST;
    if (is_hexadecimal(token))
        return TT_CONST;
    if (is_operand(token, tokenlist))
        return TT_OPERAND;
    token.type = -1;
    return -1;
}

void verify_tokens (list<Token> & tokenlist, list<Token> & labellist){
/*categorizes the token into six types: Mnemonic, Label, Decimal Constant, Hexadecimal Constant, Directive and Operand
**analyses the formation of each token and generates error messages for mistackes
*/
    list<Token>::iterator it = tokenlist.begin();
    for (it = tokenlist.begin();it != tokenlist.end(); it++){
        categorize_token(*it, labellist, tokenlist);

#ifdef __DEBUG__
        cout << "Token: " << it->str << "  type: " << it->type << "  info: " << it->addit_info << endl;
#endif
    }
}


void print_tokenlist (list<Token> & tokenlist, list<Token> & labellist){
    cout << "Tamanho da Lista: " << tokenlist.size() << endl << "-----------------\n"; //print list size
    list<Token>::iterator it;
    for (it = tokenlist.begin();it != tokenlist.end(); it++)
        cout << "Token: " << it->str << "..   Line: " << it->line_number << " Number: " << it->token_pos_il << endl;  //print list element
    cout << "-----------------\n";

    for (it = labellist.begin();it != labellist.end(); it++)
        cout << "label: " << it->str << "..   Line: " << it->line_number << " Number: " << it->token_pos_il << endl;  //print list element
    cout << "-----------------\n";
}
