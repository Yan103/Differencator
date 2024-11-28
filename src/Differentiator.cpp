#include <stdio.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "Tools.h"
#include "TreeDump.h"

Node* Differentiator(Node* node) {
    // TODO checks

    if (node->type == NUM) return _NUM(0);

    if (node->type == VAR) return _NUM(1);

    ////            case POW: return _MUL(dL, _MUL(cR, _POW(cL, _SUB(cR, _NUM(1))))); // TODO 2^2 | 2^x | x^x situations

    switch ((int) node->data) {
        case  ADD: return _ADD(dL, dR);

        case  SUB: return _SUB(dL, dR);

        case  MUL: return _ADD(_MUL(dL, cR), _MUL(cL, dR));

        case  DIV: return _DIV(_SUB(_MUL(dL, cR), _MUL(cL, dR)), _MUL(cL, cR));

        case  SIN: return _MUL(dR, _COS(cR));

        case  COS: return _MUL(dR, _SUB(_NUM(0), _SIN(cR)));

        case   TG: return _MUL(dR, _DIV(_NUM(1), _POW(_COS(cR), _NUM(2))));

        case  CTG: return _MUL(dR, _SUB(_NUM(0), _DIV(_NUM(1), _POW(_SIN(cR), _NUM(2)))));

        case  EXP: return _MUL(dR, _EXP(cR));

        case   SH: return _MUL(dR, _CH(cR));

        case   CH: return _MUL(dR, _SH(cR));

        case   TH: return _MUL(dR, _DIV(_NUM(1), _POW(_CH(cR), _NUM(2))));

        case  CTH: return _MUL(dR, _SUB(_NUM(0), _DIV(_NUM(1), _POW(_SH(cR), _NUM(2)))));

        case ASIN: return _MUL(dR, _DIV(_NUM(1), _POW(_SUB(_NUM(1), _POW(cR, _NUM(2))), _NUM(0.5))));

        case ACOS: return _MUL(dR, _SUB(_NUM(0), _DIV(_NUM(1), _POW(_SUB(_NUM(1), _POW(cR, _NUM(2))), _NUM(0.5)))));

        case  ATG: return _MUL(dR, _DIV(_NUM(1), _ADD(_NUM(1), _POW(cR, _NUM(2)))));

        case ACTG: return _MUL(dR, _SUB(_NUM(0), _DIV(_NUM(1), _ADD(_NUM(1), _POW(cR, _NUM(2))))));

        case   LN: return _MUL(dR, _DIV(_NUM(1), cR));

        case SQRT: return _MUL(dR, _DIV(_NUM(1), _MUL(_NUM(2), _POW(cR, _NUM(0.5)))));

        case  POW: { // TODO check it in tests (mb tut est' oshibki...)
            if        (!SubTreeHaveArgs(node->left) && !SubTreeHaveArgs(node->right)) {  //* const^const
                return _NUM(0);
            } else if (!SubTreeHaveArgs(node->left) &&  SubTreeHaveArgs(node->right)) {  //* const^variable
                return _MUL(dR, _MUL(_POW(cL, cR), _LN(cL)));
            } else if ( SubTreeHaveArgs(node->left) && !SubTreeHaveArgs(node->right)) {  //* variable^const
                return _MUL(dL, _MUL(cR, _POW(cL, _SUB(cR, _NUM(1)))));
            } else {                                                                     //* variable^variable
                return _MUL(_ADD(_MUL(dR, _LN(cL)), _DIV(_MUL(dL, cR), cL)), _POW(cL, cR));
            }
        }

        default: {
            fprintf(stderr, RED("Unknown operation %d!\n"), (int) node->data);
            break;
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