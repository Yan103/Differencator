/*!
    \file
    File with return codes enum
*/

#ifndef FUNCRETURNCODE_H
#define FUNCRETURNCODE_H

/// @brief Enum with return functions codes
enum FuncReturnCode {
    SUCCESS         =  0,
    MEMORY_ERROR    = -1,
    FILE_ERROR      = -2,
    UNKNOWN_ERROR   = -3,
    TREE_READ_ERROR = -4,
    UNKNOWN_FLAG    = -5,
};

enum NodeDataType {
    NUM = 1,
    VAR = 2,
    OP  = 3,
};

enum NodeOperatorCodes {
    ADD = 0,
    SUB = 1,
    DIV = 2,
    MUL = 3,
    SIN = 4,
    COS = 5,
    TAN = 6,
    COT = 7,
    LOG = 8,
    LN  = 9,
};

#endif // FUNCRETURNCODE_H