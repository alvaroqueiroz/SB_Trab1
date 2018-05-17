/** @brief Inclusão da biblioteca de verificação de argumentos */

#include "argument_checks.h"

/**  Instrução de uso correto do programa e escolha do tipo de output */
static void showUsage() {
    printf("Usage:    .\\assembler <argument> assembly_file.asm\n");
    printf("<argument> = '-p' or '-m' or '-o' or '-P' or '-M' or '-O'\n");
}

void validateArguments(int argc, char* argv[]) {
    checkArgumentAmount(argc);
    for (int i = 2; i < argc; ++i)
        checkFileExtension(argv[i]);
}

void checkArgumentAmount(int argc) {
    if (argc != 4) {
        fprintf(stderr, "[ERROR]: Invalid amount of arguments.\n");
        showUsage();
        exit(EXIT_FAILURE);
    }
}

/** Checagem da extensão do arquivo.
    @param[in] file_name Ponteiro do tipo char que aponta para o começo do arquivo.

*/
void checkFileExtension(char* file_name) {
    if (strstr(file_name, ".asm") == NULL) {
        fprintf(stderr, "[ERROr]: The file must have the extension '.asm'\n");
        showUsage();
        exit(EXIT_FAILURE);
    }
}

/** Escolha do tipo de Output definida pelo usuário.
    @param[in] op Paramentro de escolha de tipo de Output: Terminal ou Arquivo.
*/
int checkOutputOption(char* op) {
    if (strcmp(op, "-p") == 0 || strcmp(op, "-P") == 0)
        return 0;
    else if (strcmp(op, "-m") == 0 || strcmp(op, "-M") == 0)
        return 1;
    else if (strcmp(op, "-o") == 0 || strcmp(op, "-O") == 0)
        return 2;
    else {
        fprintf(stderr, "[ERROR]: Invalid argument\n");
        exit(EXIT_FAILURE);
    }
}
