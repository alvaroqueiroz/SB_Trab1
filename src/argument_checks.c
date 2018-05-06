/** @brief Inclusão da biblioteca de verificação de argumentos */

#include "argument_checks.h"

/**  Instrução de uso correto do programa e escolha do tipo de output */
static void showUsage() {
    printf("Uso:    .\\montador <argumento> arquivo_assembly.asm\n");
    printf("<argumento> = '-p' ou '-m' ou '-o' ou '-P' ou '-M' ou '-O'\n");
}

void validateArguments(int argc, char* argv[]) {
    checkArgumentAmount(argc);
    for (int i = 2; i < argc; ++i)
        checkFileExtension(argv[i]);
}

void checkArgumentAmount(int argc) {
    if (argc != 2) {
        fprintf(stderr, "[ERRO]: Quantidade invalida de argumentos.\n");
        showUsage();
        exit(EXIT_FAILURE);
    }
}

/** Checagem da extensão do arquivo.
    @param[in] file_name Ponteiro do tipo char que aponta para o começo do arquivo.

*/
void checkFileExtension(char* file_name) {
    if (strstr(file_name, ".asm") == NULL) {
        fprintf(stderr, "[ERRO]: O arquivo deve ter a extensao '.asm'\n");
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
        fprintf(stderr, "[ERRO]: Argumento invalido\n");
        exit(EXIT_FAILURE);
    }
}
