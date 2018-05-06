#Software Básico - Trabalho 1

##Objetivo

Fixar o funcionamento de um processo de tradução. Especificamente as etapas de analise léxica, sintática e semântica e a etapa de geração de código objeto.

##Especificação

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

##Fluxo de programa

| Step | Feature | Headers | Input | Output | Intermediary Elements |
| :--: | ------- | ------- | ----- | ------ | --------------------- |
| 1    | Main    |         | argument / assembly file name | txt file |      |
| 2    | Scanner |       | complete assembly file | assembly token list / lexic error msg |      |
| 3    | Parser |    | token list | syntactic tree / syntactic error msg |       |
| 4    | Semantic Analiser |     | raw assembly file / Semantic error msg | noted syntactic tree |
| 5.1* | Macro Solver |     | raw assembly file | macro solved assembly file | macro prototype table / macro body table |
| 5.2* | First Pass |      | macro solved assembly file  | Symbol Table |      |
| 5.3* | Seccond Pass |    | macro solved assembly file / Symbol Table | Intermediary Code |      |
| 6    | Optmizer |     | Intermediary code | Optmized Intermediary Code |     |
| 7    | Object Code Generator | argument / Optmized Intermediary Code | Object Code / Macro Solved Code / Pre-process code |    |

(*) step 5 - Intermediary Code Generator







