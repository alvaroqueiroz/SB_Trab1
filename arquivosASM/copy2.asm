UM: EQU 1
SECTION TEXT
ROT: INPUT N1
COPY N1, N4 +                                      UM
COPY N2, N3
COPY N3, N4
OUTPUT N4
STOP
SECTION DATA
N1:  SPACE
N2:  CONST 5
N3:  SPACE
N4:  SPACE 2
