#ifndef DIFFERENCATOR_H
#define DIFFERENCATOR_H

#include <stdio.h>

#include "BinaryTree.h"
#include "Operations.h"

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

#endif // DIFFERENCATOR_H