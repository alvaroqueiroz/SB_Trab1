l2: macro arg1
add arg1
endmacro

cray:  macro	arg1 arg2
l2 arg1
l3 arg2
l4 arg1 arg2
endmacro


l3: macro arg1
l2 arg1
load arg1
endmacro

l4: macro arg1 arg2
copy arg1, arg2
l3 arg1
endmacro


SECTION TEXT
cray AA BB
