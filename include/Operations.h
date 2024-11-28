#ifndef OPERATIONS_H
#define OPERATIONS_H

enum NodeDataType {
    NUM   = 1,
    VAR   = 2,
    UN_OP = 3,
    BI_OP = 4,
};

enum NodeOperatorCodes {
    ADD  =  0,
    SUB  =  1,
    DIV  =  2,
    MUL  =  3,
    SIN  =  4,
    COS  =  5,
    TG   =  6,
    CTG  =  7,
    LN   =  8,
    SQRT =  9,
    EXP  = 10,
    POW  = 11,
    ASIN = 12,
    ACOS = 13,
    ATG  = 14,
    ACTG = 15,
    SH   = 16,
    CH   = 17,
    TH   = 18,
    CTH  = 19,
};

#endif // OPERATIONS_H