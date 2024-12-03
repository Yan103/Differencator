#include <stdio.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"

const char* INPUT_FILENAME = "../Differencator/Expressions/test1.txt";

int main() {
    srand((unsigned int)time(NULL));

    //ReadString rs = {.s = "25+25^2^3-3*10$", .p = 0};
    //ReadString* rs = ReadExpFromFile(INPUT_FILENAME);
    //Node* root = GetG(&rs);

    Node* node1 = CreateNode(VAR, -666, NULL, NULL);
    Node* node11 = CreateNode(NUM, 3, NULL, NULL);
    Node* node2 = CreateNode(NUM, 3, NULL, NULL);

    Node* node = CreateNode(BI_OP, POW, node1, node11);
    Node* root = CreateNode(BI_OP, MUL, node2, node);

    Tree* tree = TreeCtor(root);

    TREE_DUMP(tree, "%s", __func__);

    Tree* diff_tree = TreeDiff(tree->root);

    TREE_DUMP(diff_tree, "%s", __func__);

    TreeDtor(tree);
    TreeDtor(diff_tree);

    return SUCCESS;
}