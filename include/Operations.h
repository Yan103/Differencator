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

struct Operation {
    NodeOperatorCodes OpCode;
    const char*         name;
    NodeDataType      OpType;
    int             priority;
};

const Operation OPERATIONS[] {
    { ADD,      "+", BI_OP, 1},
    { SUB,      "-", BI_OP, 1},
    { DIV,      "/", BI_OP, 2},
    { MUL,      "*", BI_OP, 2},
    { SIN,    "sin", UN_OP, 4},
    { COS,    "cos", UN_OP, 4},
    {  TG,    "tan", UN_OP, 4},
    { CTG,    "cot", UN_OP, 4},
    {  LN,     "ln", UN_OP, 4},
    {SQRT,   "sqrt", UN_OP, 4},
    { EXP,    "exp", UN_OP, 4},
    { POW,      "^", BI_OP, 3},
    {ASIN, "arcsin", UN_OP, 4},
    {ACOS, "arccos", UN_OP, 4},
    { ATG, "arctan", UN_OP, 4},
    {  SH,   "sinh", UN_OP, 4},
    {  CH,   "cosh", UN_OP, 4},
    {  TH,   "tanh", UN_OP, 4},
    { CTH,   "coth", UN_OP, 4},
};

const size_t OPERATIONS_COUNT = sizeof(OPERATIONS) / sizeof(Operation);

#endif // OPERATIONS_H