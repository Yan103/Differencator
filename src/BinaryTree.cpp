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
FuncReturnCode SubTreeDtor(Node* node) {
    ASSERT(node != NULL, "NULL POINTER WAS PASSED!\n");

    if (node->left) {
        SubTreeDtor(node->left);
    }

    if (node->right) {
        SubTreeDtor(node->right);
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

    SubTreeDtor(tree->root);
    FREE(tree);

    return SUCCESS;
}

FuncReturnCode TreeNodeDtor(Node* node) {
    ASSERT(node != NULL, "NULL POINTER WAS PASSED!\n");
    FREE(node)

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

int SubTreeHaveArgs(Node* node) {
    if (!node)             return 0;
    if (node->type == NUM) return 0;
    if (node->type == VAR) return 1;

    return SubTreeHaveArgs(node->left) + SubTreeHaveArgs(node->right);
}

FuncReturnCode SubTreeToNum(Node* node, NodeData value) {
    ASSERT(node != NULL, "NULL POINTER WAS PASSED!\n");

    node->data = value;
    node->type = NUM;

    SubTreeDtor(node->left);
    SubTreeDtor(node->right);

    node->left = NULL;
    node->right = NULL;

    return SUCCESS;
}

void SyntaxError() {
    printf("ERROR!\n");
    abort();
}

Node* GetG(ReadString* rs) {
    Node* val = GetE(rs);
    if (rs->s[rs->p] != '$') {
        printf("%s %d\n", __func__, rs->p);
        SyntaxError();
    }
    rs->p++;
    return val;
}

Node* GetE(ReadString* rs) {
    Node* val = GetT(rs);
    while (rs->s[rs->p] == '+' || rs->s[rs->p] == '-') {
        int op = rs->s[rs->p];
        rs->p++;
        Node* val2 = GetT(rs);
        if (op == '+') {
            val = CreateNode(BI_OP, ADD, val, val2);
        } else {
            val = CreateNode(BI_OP, SUB, val, val2);
        }
    }
    return val;
}

Node* GetT(ReadString* rs) {
    Node* val = GetP(rs);
    while (rs->s[rs->p] == '*' || rs->s[rs->p] == '/') {
        int op = rs->s[rs->p];
        rs->p++;
        Node* val2 = GetP(rs);
        if (op == '*') {
            val = CreateNode(BI_OP, MUL, val, val2);
        } else {
            val = CreateNode(BI_OP, DIV, val, val2);
        }
    }
    return val;
}

Node* GetP(ReadString* rs) {
    Node* val = GetB(rs);
    while (rs->s[rs->p] == '^') {
        rs->p++;
        Node* val2 = GetB(rs);
        val = CreateNode(BI_OP, POW, val, val2);
    }
    return val;
}

Node* GetB(ReadString* rs) {
    if (rs->s[rs->p] == '(') {
        rs->p++;
        Node* val = GetE(rs);
        if (rs->s[rs->p] != ')') {
            printf("%s\n", __func__);
            SyntaxError();
        }
        rs->p++;
        return val;
    } else {
        return GetN(rs);
    }
}

Node* GetN(ReadString* rs) {
    int val = 0;
    int old_p = rs->p;
    while  ('0' <= rs->s[rs->p] && rs->s[rs->p] <= '9') {
        val *= 10;
        val += rs->s[rs->p] - '0';
        rs->p++;
    }
    if (old_p == rs->p) {
        printf("%s\n", __func__);
        SyntaxError();
    }
    return CreateNode(NUM, val, NULL, NULL);
}

FuncReturnCode ConnectChildWithParent(Node* node, NodeLocation location) {

    if (!node) return SUCCESS;

    Node* child_node = location == LEFT ? node->left : node->right;

    if (!child_node) fprintf(stderr, RED("Nothing to connect, child null pointer"));

    node->data  = child_node->data;
    node->type = child_node->type;

    if (child_node == node->left)
        TreeNodeDtor(node->right);
    else
        TreeNodeDtor(node->left);

    node->left  = child_node->left;
    node->right = child_node->right;

    TreeNodeDtor(child_node);

    return SUCCESS;
}

/*ReadString* ReadExpFromFile(const char* filename) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    FILE* read_file = fopen(filename, "r");
    if (!read_file) {
        fprintf(stderr, "Error with occured file!\n");

        return NULL;
    }

    char* buffer = (char*) calloc(1000, sizeof(char));
    fread(buffer, sizeof(char), 1000, read_file);

    ReadString rs = {.s = buffer, .p = 0};
    fclose(read_file);

    return &rs;
}*/