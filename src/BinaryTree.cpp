/*!
    \file
    File with binary tree functions
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "BinaryTree.h"
#include "TreeDump.h"

/*!
    @brief Function that creates binary tree
    \param [out] root - pointer on tree root
    @return The pointer on the tree
*/
Tree* TreeCtor(Node* root) {
    ASSERT(root != NULL, "NULL POINTER WAS PASSED!\n");

    Tree* tree = (Tree*) calloc(1, sizeof(Tree));
    if (!tree) {
        fprintf(stderr, RED("MEMORY ERROR!\n"));

        return NULL;
    }

    tree->root = root;
    tree->size = 1;

    return tree;
}

/*!
    @brief Function that creates node
    \param [in] value - node data
    @return The pointer on the node
*/
Node* CreateNode(NodeDataType type, NodeData value, Node* left, Node* right) {
    Node* node = (Node*) calloc(1, sizeof(Node));
    if (!node) {
        fprintf(stderr, RED("MEMORY ERROR!\n"));

        return NULL;
    }

    node->type  =  type;
    node->data  = value;
    node->left  =  left;
    node->right = right;

    return node;
}

/*!
    @brief Function that deletes tree node
    \param [out] node - pointer on node
    @return The status of the function (return code)
*/
FuncReturnCode NodeDtor(Node* node) {
    ASSERT(node != NULL, "NULL POINTER WAS PASSED!\n");

    if (node->left) {
        NodeDtor(node->left);
    }

    if (node->right) {
        NodeDtor(node->right);
    }

    FREE(node);

    return SUCCESS;
}

/*!
    @brief Function that deletes binary tree
    \param [out] tree - pointer on tree
    @return The status of the function (return code)
*/
FuncReturnCode TreeDtor(Tree* tree) {
    ASSERT(tree != NULL, "NULL POINTER WAS PASSED!\n");

    NodeDtor(tree->root);
    FREE(tree);

    return SUCCESS;
}

/*!
    @brief Function that skips spaces in the file
    \param  [in] filename - pointer on the file
    \param [out]   symbol - symbol value
    @return The last readed symbol
*/
static int SkipSpacesInFile(FILE* filename, int symbol) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    while (isspace(symbol = fgetc(filename))) {
        ;
    }

    return symbol;
}

/*!
    @brief Function that skips symbols in the file until it meets the necessary one
    \param  [in]    filename - pointer on the file
    \param [out]      symbol - symbol value
    \param  [in] find_symbol - find symbol value
    @return The last readed symbol
*/
static int SkipUntilFindSymbol(FILE* filename, int symbol, char find_symbol) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    while ((symbol = fgetc(filename)) != find_symbol){
        ;
    }

    return symbol;
}

/*!
    @brief Function that writes binary tree in the file
    \param [in] filename - pointer on the file
    \param [in]     tree - pointer on tree
    @return The status of the function (return code)
*/
FuncReturnCode WriteTree(FILE* filename, Tree* tree) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(tree     != NULL, "NULL POINTER WAS PASSED!\n");

    WriteSubTree(filename, tree->root);

    return SUCCESS;
}

/*!
    @brief Function that writes subtree in file
    \param [in] filename - pointer on the file
    \param [in]     node - pointer on node
    @return The status of the function (return code)
*/
FuncReturnCode WriteSubTree(FILE* filename, Node* node) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    if (node == NULL) {
        fprintf(filename, "* ");

        return SUCCESS;
    }

    fprintf(filename, "{ ");

    fprintf(filename, "\"%d\" ", node->data);
    WriteSubTree(filename, node->left);
    WriteSubTree(filename, node->right);

    fprintf(filename, "} ");

    return SUCCESS;
}
