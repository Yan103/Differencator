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
#define _POW(LEFT, RIGHT) CreateNode(OP, POW, LEFT, RIGHT)

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

            case POW: return _MUL(dL, _MUL(cR, _POW(cL, _SUB(cR, _NUM(1))))); // TODO 2^2 | 2^x | x^x situations

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

TreeSimplifyCode TreeSimplify(Tree* tree) {
    ASSERT(tree != NULL, "NULL POINTER WAS PASSED!\n");

    return SubTreeSimplify(tree->root);
}

TreeSimplifyCode SubTreeSimplify(Node* node) {

    if (!node) return TREE_SIMPLIFY_SUCCESS;

    TreeSimplifyCode simpify_status = TREE_SIMPLIFY_SUCCESS;

    int tree_changed_flag = 0;

    do {
        tree_changed_flag = 0;

        simpify_status = SubTreeSimplifyConstants(node, &tree_changed_flag);
        if (simpify_status != TREE_SIMPLIFY_SUCCESS) break;

        /*simpify_status = SubTreeSimplify();
        if (simpify_status != TREE_SIMPLIFY_SUCCESS) break;*/

    } while (tree_changed_flag);

    return simpify_status;
}

TreeSimplifyCode SubTreeSimplifyConstants(Node* node, int* tree_changed_flag) {
    return TREE_SIMPLIFY_SUCCESS;
}