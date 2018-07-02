SECTION TEXT
public l1
INPUT OLD_DATA
LOAD OLD_DATA
L1: DIV DOIS

a1: extern

add a1 + 99
jmp l1

public tmp_data
public dois
public old_data

SECTION DATA
TMP_DATA: SPACE 3
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE

