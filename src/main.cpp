#include <stdio.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"

const char* INPUT_FILENAME = "../Differencator/Expressions/test1.txt";

int main() {
    srand((unsigned int)time(NULL));

    ReadString* rs = ReadExpFromFile(INPUT_FILENAME);
    if (rs) {
        Node* root = GetG(rs);

        Tree* tree = TreeCtor(root);

        TREE_DUMP(tree, "%s", __func__);

        Tree* diff_tree = TreeDiff(tree);

        TREE_DUMP(diff_tree, "%s", __func__);

        TreeDtor(tree);
        TreeDtor(diff_tree);
        ReadStringDtor(rs);
    }

    return SUCCESS;
}