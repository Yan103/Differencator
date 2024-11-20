#include <stdio.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "Tools.h"
#include "TreeDump.h"

#define _NUM(num)         CreateNode(NUM, num, NULL, NULL)
#define _ADD(LEFT, RIGHT) CreateNode(OP, ADD, LEFT, RIGHT)
#define _SUB(LEFT, RIGHT) CreateNode(OP, SUB, LEFT, RIGHT)
#define _MUL(LEFT, RIGHT) CreateNode(OP, MUL, LEFT, RIGHT)
#define _DIV(LEFT, RIGHT) CreateNode(OP, DIV, LEFT, RIGHT)

#define dL Differentiator(node->left)
#define dR Differentiator(node->right)

#define cL SubTreeCopy(node->left)
#define cR SubTreeCopy(node->right)

Node* Differentiator(Node* node) {
    // TODO checks

    if (node->type == NUM) return _NUM(0);

    if (node->type == VAR) return _NUM(1);

    if (node->type == OP) {
        switch (node->data) {
            case ADD: return _ADD(dL, dR);

            case SUB: return _SUB(dL, dR);

            case MUL: return _ADD(_MUL(dL, cR), _MUL(cL, dR));

            case DIV: return _DIV(_SUB(_MUL(dL, cR), _MUL(cL, dR)), _MUL(cL, cR));

            default: fprintf(stderr, RED("UNKNOWN OPERATION!\n"));
        }
    }

    return NULL;
}

Tree* TreeDiff(Node* root) {
    ASSERT(root != NULL, "NULL POINTER WAS PASSED!\n");

    Node* diff_root = Differentiator(root);

    Tree* diff_tree = TreeCtor(diff_root);

    return diff_tree;
}

Node* SubTreeCopy(Node* node) {
    if (!node) return NULL;

    Node* copied_node = CreateNode(node->type, node->data, SubTreeCopy(node->left), SubTreeCopy(node->right));

    return copied_node;
}