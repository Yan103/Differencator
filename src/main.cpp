#include <stdio.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"

int main() {
    srand((unsigned int)time(NULL));

    Node* node1 = CreateNode(VAR, -666, NULL, NULL);
    Node* node11 = CreateNode(NUM, 3, NULL, NULL);
    Node* node2 = CreateNode(NUM, 3, NULL, NULL);

    Node* node = CreateNode(OP, POW, node1, node11);
    Node* root = CreateNode(OP, MUL, node2, node);

    Tree* tree = TreeCtor(root);

    TREE_DUMP(tree, "%s", __func__);

    Tree* diff_tree = TreeDiff(tree->root);

    TREE_DUMP(diff_tree, "%s", __func__);

    TreeDtor(tree);
    TreeDtor(diff_tree);

    return SUCCESS;
}