#ifndef DIFFERENCATOR_H
#define DIFFERENCATOR_H

#include <stdio.h>

#include "BinaryTree.h"
#include "Operations.h"

#define _NUM(num)         CreateNode(NUM, num, NULL, NULL)
#define _ADD(LEFT, RIGHT) CreateNode(BI_OP, ADD, LEFT, RIGHT)
#define _SUB(LEFT, RIGHT) CreateNode(BI_OP, SUB, LEFT, RIGHT)
#define _MUL(LEFT, RIGHT) CreateNode(BI_OP, MUL, LEFT, RIGHT)
#define _DIV(LEFT, RIGHT) CreateNode(BI_OP, DIV, LEFT, RIGHT)
#define _POW(LEFT, RIGHT) CreateNode(BI_OP, POW, LEFT, RIGHT)

#define _SIN(RIGHT)       CreateNode(UN_OP, SIN, NULL, RIGHT)
#define _COS(RIGHT)       CreateNode(UN_OP, COS, NULL, RIGHT)
#define _EXP(RIGHT)       CreateNode(UN_OP, EXP, NULL, RIGHT)
#define  _LN(RIGHT)       CreateNode(UN_OP,  LN, NULL, RIGHT)
#define  _SH(RIGHT)       CreateNode(UN_OP,  SH, NULL, RIGHT)
#define  _CH(RIGHT)       CreateNode(UN_OP,  CH, NULL, RIGHT)

#define dL Differentiator(node->left)
#define dR Differentiator(node->right)

#define cL SubTreeCopy(node->left)
#define cR SubTreeCopy(node->right)

const double EXPONENT = 2.718281828459045;
const double PI       = 3.141592653589793;

enum TreeSimplifyCode {
    TREE_SIMPLIFY_SUCCESS =  0,
    TREE_SIMPLIFY_ERROR   = -1,
};

Node* Differentiator(Node* node);

Tree* TreeDiff(Node* root);

Node* SubTreeCopy(Node* node);

TreeSimplifyCode TreeSimplify(Tree* tree);

TreeSimplifyCode SubTreeSimplify(Node* node);

TreeSimplifyCode SubTreeSimplifyConstants(Node* node, int* tree_changed_flag);

FuncReturnCode SubTreeEvalUnOperation(Node* node, NodeData arg, NodeData* result);

FuncReturnCode SubTreeEvalBiOperation(Node* node, NodeData left_arg, NodeData right_arg, NodeData* result);

TreeSimplifyCode SubTreeSimplifyTrivialCases(Node* node, int* tree_changed_flag);

#endif // DIFFERENCATOR_H