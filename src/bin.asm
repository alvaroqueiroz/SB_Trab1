l2: macro &arg1
add &arg1
endmacro

cray:  macro	&arg1, & arg2
l2 &arg1
l3 &arg2
l4 &arg1, &arg2
l5 l2, XX
endmacro


l3: macro &arg1
l2 &arg1
load &arg1
endmacro

l4: macro &arg1, &arg2
copy &arg1, &arg2 + 2
l3 &arg1
endmacro

l5: macro &arg1, &arg2
&arg1 &arg2
endmacro

SECTION TEXT
INPUT OLD_DaTa
LOAD OLD_DATA
L1: MULT DOIS
STORE  NEW_DATA
div DOIS
STORE DOIS
copy dois, new_data
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA
LOAD OLD_DATA
JMPP L1
STOP
SECTION DATA
DOIS: CONST 0
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE

section data
AA: const 5
XX: space
BB: space 3
add op
op: space
