UM: EQU 1
SECTION TEXT
ROT: INPUT N1
COPY N1, N3
COPY N2, N1
COPY N3, N4
LOAD N5
STORE N4
OUTPUT N4
STOP
SECTION DATA
N1:  SPACE
N2:  CONST 5
N3:  SPACE
N4:  SPACE 4
N5:  SPACE
