#include <stdio.h>
#include <math.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "Tools.h"
#include "TreeDump.h"

Node* Differentiator(Node* node) {
    // TODO checks

    if (node->type == NUM) return _NUM(0);

    if (node->type == VAR) return _NUM(1);

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

Tree* TreeDiff(Tree* tree) {
    ASSERT(tree != NULL, "NULL POINTER WAS PASSED!\n");

    Node* diff_root = Differentiator(tree->root);

    Tree* diff_tree = TreeCtor(diff_root);

    TREE_DUMP(diff_tree, "%s", __func__);

    TreeSimplify(diff_tree);

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

        simpify_status = SubTreeSimplifyTrivialCases(node, &tree_changed_flag);
        if (simpify_status != TREE_SIMPLIFY_SUCCESS) break;

    } while (tree_changed_flag);

    return simpify_status;
}

TreeSimplifyCode SubTreeSimplifyConstants(Node* node, int* tree_changed_flag) {
    ASSERT(tree_changed_flag != NULL, "NULL POINTER WAS PASSED!\n"); //TODO checks

    if (!node)             return TREE_SIMPLIFY_SUCCESS;
    if (node->type == NUM) return TREE_SIMPLIFY_SUCCESS;
    if (node->type == VAR) return TREE_SIMPLIFY_SUCCESS;

    TreeSimplifyCode simpify_result = TREE_SIMPLIFY_SUCCESS;

    simpify_result = SubTreeSimplifyConstants(node->left, tree_changed_flag);

    simpify_result = SubTreeSimplifyConstants(node->right, tree_changed_flag);

    if (node->type == UN_OP && node->right->type == NUM) {
        SubTreeEvalUnOperation(node, node->right->data, &(node->data)); //TODO checks

        node->type = NUM;
        TreeNodeDtor(node->right);
        node->right = NULL;

        *tree_changed_flag += 1;

        return TREE_SIMPLIFY_SUCCESS;
    }

    if (node->type == BI_OP && node->right->type == NUM && node->left->type == NUM) { //TODO checks
        SubTreeEvalBiOperation(node, node->left->data, node->right->data, &(node->data));

        node->type  = NUM;
        TreeNodeDtor(node->right);
        TreeNodeDtor(node->left);
        node->right = NULL;
        node->left  = NULL;

        *tree_changed_flag += 1;

        return TREE_SIMPLIFY_SUCCESS;
    }

    return simpify_result;
}

FuncReturnCode SubTreeEvalUnOperation(Node* node, NodeData arg, NodeData* result) {
    ASSERT(result != NULL, "NULL POINTER WAS PASSED!\n"); //TODO checks

    switch ((int) node->data) {
        case EXP:
            *result = pow(EXPONENT, arg);
            break;
        case LN:
            *result = log(arg);
            break;
        case SIN:
            *result = sin(arg);
            break;
        case COS:
            *result = cos(arg);
            break;
        case TG:
            *result = tan(arg);
            break;
        case CTG:
            *result = 1 / tan(arg);
            break;
        case SH:
            *result = sinh(arg);
            break;
        case CH:
            *result = cosh(arg);
            break;
        case TH:
            *result = tanh(arg);
            break;
        case CTH:
            *result = 1 / tanh(arg);
            break;
        case ASIN:
            *result = asin(arg);
            break;
        case ACOS:
            *result = acos(arg);
            break;
        case ATG:
            *result = atan(arg);
            break;
        case ACTG:
            *result = PI / 2 - atan(arg);
            break;
        default:
            fprintf(stderr, "Something went wrong...\n");
            return UNKNOWN_ERROR;
    }

    return SUCCESS;
}

FuncReturnCode SubTreeEvalBiOperation(Node* node, NodeData left_arg, NodeData right_arg, NodeData* result) {
    ASSERT(result != NULL, "NULL POINTER WAS PASSED!\n"); //TODO checks

    switch ((int) node->data) {
        case ADD:
            *result = left_arg + right_arg;
            break;
        case SUB:
            *result = left_arg - right_arg;
            break;
        case MUL:
            *result = left_arg * right_arg;
            break;
        case DIV:
            *result = left_arg / right_arg;
            break;
        case POW:
            *result = pow(left_arg, right_arg);
            break;
        default:
            fprintf(stderr, "Something went wrong...\n");
            return UNKNOWN_ERROR;
    }

    return SUCCESS;
}

TreeSimplifyCode SubTreeSimplifyTrivialCases(Node* node, int* tree_changed_flag) {
    ASSERT(tree_changed_flag != NULL, "NULL POINTER WAS PASSED!\n"); //TODO checks

    if (!node)             return TREE_SIMPLIFY_SUCCESS;
    if (node->type == NUM) return TREE_SIMPLIFY_SUCCESS;
    if (node->type == VAR) return TREE_SIMPLIFY_SUCCESS;

    TreeSimplifyCode simpify_result = TREE_SIMPLIFY_SUCCESS;

    if (node->left)  simpify_result = SubTreeSimplifyTrivialCases(node->left,  tree_changed_flag);

    if (node->right) simpify_result = SubTreeSimplifyTrivialCases(node->right, tree_changed_flag);

    switch ((int) node->data) {
        case ADD:
            if (node->left->type == NUM && IS_ZERO(node->left->data)) {
                ConnectChildWithParent(node, RIGHT);

                *tree_changed_flag = 1;
            } else if (node->right->type == NUM && IS_ZERO(node->right->data)) {
                ConnectChildWithParent(node, LEFT);

                *tree_changed_flag = 1;
            }

            break;

        case SUB:
            if (node->right->type == NUM && IS_ZERO(node->right->data)) {
                ConnectChildWithParent(node, LEFT);

                *tree_changed_flag = 1;
            }

            break;

        case MUL:
            if (node->left->type == NUM && IS_ONE(node->left->data)) {
                ConnectChildWithParent(node, RIGHT);

                *tree_changed_flag = 1;
            } else if (node->right->type == NUM && IS_ONE(node->right->data)) {
                ConnectChildWithParent(node, LEFT);

                *tree_changed_flag = 1;
            } else if (node->left->type == NUM && IS_ZERO(node->left->data)) {
                SubTreeToNum(node, 0);

                *tree_changed_flag = 1;
            } else if (node->right->type == NUM && IS_ZERO(node->right->data)) {
                SubTreeToNum(node, 0);

                *tree_changed_flag = 1;
            }

            break;

        case DIV:
            if (node->left->type == NUM && IS_ZERO(node->left->data)) {
                SubTreeToNum(node, 0);

                *tree_changed_flag = 1;
            }

            break;

        case POW:
            if (node->right->type == NUM && IS_ZERO(node->right->data)) {
                SubTreeToNum(node, 1);

                *tree_changed_flag = 1;
            } else if (node->right->type == NUM && IS_ONE(node->right->data)) {
                ConnectChildWithParent(node, LEFT);

                *tree_changed_flag = 1;
            }
            break;

        default:
            break;
    }

    return simpify_result;
}