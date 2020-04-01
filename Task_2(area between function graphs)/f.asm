%include "io.inc"

section .data:
    two dq -2.0
    ft dq 14.0
    six dq 6.0
    dva dq 2.0

section .text:
global _f1
global _f2
global _f3
finit
CEXTERN log
_f1:
    fld qword[esp + 4]
    sub esp, 12
    fstp qword[esp]
    call log
    add esp, 12
    ret
    
_f2:
    fld qword[ft]
    fld qword[two]  
    fld qword[esp + 4]
    fmulp
    faddp
    ret

_f3:
    fld qword[six]
    fld1
    fld qword[dva]
    fld qword[esp + 4]
    fsubp
    fdivp
    faddp
    ret
    
    
    
    