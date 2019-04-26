# Software Básico - Trabalho 1

## Objetivo

Fixar o funcionamento de um processo de tradução. Especificamente as etapas de analise léxica, sintática e semântica e a etapa de geração de código objeto.

## Especificação

Criar um *montador* para a linguagem assembly didática inventada, para o conjunto de 14 instruções pré-definidas, sendo necessário o suporte para:

- Instruções, diretivas e rótulos, not case sensitive;
- Macros com até 4 parâmetros;
- Comentários - indicados por ponto e vírgula;
- Montagem em três modos:
	- pre-processamento: "-p" - somente avalia as diretivas EQU e IF;
	- processamento de macros: "-m" - diretivas EQU e IF e substitue as MACROS;
	- montagem: "-o" - realiza a montagem de programa.
- Identificação de erros, indicando linha e tipo do erro (Léxico, Sintático ou Semântico):
	- ver lista de erros na descrição do trabalho;

Todos os arquivos de saída devem estar em formato TEXTO. No casso do arquivo objeto, o arquivo de saída deve ser somente os OPCODES e operandos sem quebra de linha, nem endereço indicado, mas sepradados por espaço.

## Fluxo de programa

### Descritivo de módulos

| Step | Feature | Headers | Input | Output | Intermediary Elements |
| :--: | ------- | ------- | ----- | ------ | --------------------- |
| 1    | Main    |         | argument / assembly file name | asm file |      |
| 2    | Scanner |       | complete assembly file | assembly token list / lexic error msg |      |
| 3    | Parser |    | token list | syntactic tree / syntactic error msg |       |
| 4    | Semantic Analyser |     | raw assembly file / Semantic error msg | noted syntactic tree |
| 5.1* | Macro Solver |     | raw assembly file | macro solved assembly file | macro prototype table / macro body table |
| 5.2* | First Pass |      | macro solved assembly file  | Symbol Table |      |
| 5.3* | Seccond Pass |    | macro solved assembly file / Symbol Table | Intermediary Code |      |
| 6    | Optmizer |     | Intermediary code | Optmized Intermediary Code |     |
| 7    | Object Code Generator |    | argument / Optmized Intermediary Code | Object Code / Macro Solved Code / Pre-process code |    |

(*) step 5 - Intermediary Code Generator

### Fluxo entre módulos

- Argumento "-p":

	Input -> Main -> Scanner -> Parser -> Semantic Analyser -> Main -> Output

- Argumento "-m":

	Input -> Main -> Scanner -> Parser -> Semantic Analyser -> Macro Solver -> Main -> Output

- Argumento "-o":

	Input -> Main -> Scanner -> Parser -> Semantic Analyser -> Macro Solver -> Intermediary Code Generator -> Optmizer -> Object Code Generator -> Main -> Output

#Instruções

To compile this program, please use the following terminal command:

	clang++ -Wall *.cpp -o assembler

And to use it, please use:

	./assembler filename

Where "-d" is one of the directives "-p", "-m" or "-o" (not case sensitive).

# Referências

### Scanner
- https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

### Lists in C++
- https://www.youtube.com/watch?v=lSIoWv92rrU
- http://www.cplusplus.com/forum/beginner/3396/
