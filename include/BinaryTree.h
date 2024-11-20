/*!
    \file
    File with binary tree functions
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tools.h"
#include "BinaryTree.h"

/// @brief Type of items in a nodes' data
typedef int NodeData;

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
    NUM   = 1,
    VAR   = 2,
    OP    = 3,
    EQUAL = 4,
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
};

/// @brief Structure tree node
struct Node {
    NodeDataType type;
    NodeData     data;
    Node*        left;
    Node*       right;
};

/// @brief Structure binary tree
struct Tree {
    Node*    root;
    size_t   size;
};

/*!
    @brief Function that creates binary tree
    \param [out] root - pointer on tree root
    @return The pointer on the tree
*/
Tree* TreeCtor(Node* root);

/*!
    @brief Function that creates node
    \param [in]  type - node data type
    \param [in] value - node data
    @return The pointer on the node
*/
Node* CreateNode(NodeDataType type, NodeData value, Node* left, Node* right);

/*!
    @brief Function that deletes binary tree
    \param [out] tree - pointer on tree
    @return The status of the function (return code)
*/
FuncReturnCode TreeDtor(Tree* tree);

/*!
    @brief Function that deletes tree node
    \param [out] node - pointer on node
    @return The status of the function (return code)
*/
FuncReturnCode NodeDtor(Node* node);

/*!
    @brief Function that writes subtree in file
    \param [in] filename - pointer on the file
    \param [in]     node - pointer on node
    @return The status of the function (return code)
*/
FuncReturnCode WriteSubTree(FILE* filename, Node* node);

/*!
    @brief Function that writes binary tree in the file
    \param [in] filename - pointer on the file
    \param [in]     tree - pointer on tree
    @return The status of the function (return code)
*/
FuncReturnCode WriteTree(FILE* filename, Tree* tree);

#endif // BINARY_TREE_H