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
    LOG  =  8,
    LN   =  9,
    SQRT = 10,
    EXP  = 11,
    POW  = 12,
    ASIN = 13,
    ACOS = 14,
    ATG  = 15,
    ACTG = 16,
    SH   = 17,
    CH   = 18,
    TH   = 19,
    CTH  = 20,
};

#endif // OPERATIONS_H