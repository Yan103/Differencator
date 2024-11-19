#include <stdio.h>
#include <time.h>

#include "BinaryTree.h"
#include "Enums.h"

#include "TreeDump.h"

int main() {
    srand((unsigned int)time(NULL));

    Node* node21 = CreateNode(NUM, 3, NULL, NULL);
    Node* node22 = CreateNode(NUM, 5, NULL, NULL);

    Node* node23 = CreateNode(NUM, 9, NULL, NULL);
    Node* node24 = CreateNode(VAR, -666, NULL, NULL);

    Node* node11 = CreateNode(OP, ADD, node21, node22);
    Node* node12 = CreateNode(OP, SUB, node23, node24);

    Node* root = CreateNode(OP, MUL, node11, node12);
    Tree* tree = TreeCtor(root);

    TREE_DUMP(tree, "%s", __func__);

    TreeDtor(tree);

    return SUCCESS;
}