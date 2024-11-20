#include <stdio.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"

int main() {
    srand((unsigned int)time(NULL));

    Node* node21 = CreateNode(NUM, 3, NULL, NULL);
    Node* node22 = CreateNode(NUM, 5, NULL, NULL);

    Node* node23 = CreateNode(NUM, 9, NULL, NULL);
    Node* node24 = CreateNode(VAR, -666, NULL, NULL);

    Node* node11 = CreateNode(OP, ADD, node21, node22);
    Node* node12 = CreateNode(OP, MUL, node23, node24);

    Node* root = CreateNode(OP, ADD, node11, node12);
    Tree* tree = TreeCtor(root);

    TREE_DUMP(tree, "%s", __func__);

    Tree* diff_tree = TreeDiff(tree->root);

    TREE_DUMP(diff_tree, "%s", __func__);

    TreeDtor(tree);
    TreeDtor(diff_tree);

    return SUCCESS;
}