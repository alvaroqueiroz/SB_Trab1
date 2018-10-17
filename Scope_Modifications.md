# Scope Modifications from last semester's version

## Major Differences

- Macros: no need for macros
- BSS section: new BSS section - must be after .TEXT, but interchangeable with the .DATA section
- Tokens are now 20 char long
- there's now only one assembling fase, which does everything
        * generates two output files: the .pre file and the .o file
- assembler program must be called 'montador.c' and linker program must be called 'ligador.c'
- THE OBJ FILE MUST CONTAIN THE TABLE USE, THE TABLE DEFINITION, THE RELATIVE AND THE CODE
- the linker output must be an array of instructions in hex code
