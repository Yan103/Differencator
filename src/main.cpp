#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"
#include "LaTeXCreate.h"

const char* INPUT_FILENAME = "../Differencator/Expressions/test1.txt";
const char* TEX_FILENAME   = "../Differencator/Solution.tex";

int main() {
    srand((unsigned int)time(NULL));
    ReadString* rs = ReadExpFromFile(INPUT_FILENAME);

    if (rs) {
        Node* root = GetG(rs);

        Tree* tree = TreeCtor(root);

        FILE* tex_file = fopen(TEX_FILENAME, "w");
        if (!tex_file) {
            fprintf(stderr, "Error occured the file!\n");
            return FILE_ERROR;
        }

        TeXHeader(tex_file);

        TREE_DUMP(tree, "%s", __func__);

        Tree* diff_tree = TreeDiff(tree);

        TeXEndAndClose(tex_file);

        system("pdflatex Solution.tex");

        TREE_DUMP(diff_tree, "%s", __func__);

        TreeDtor(tree);
        TreeDtor(diff_tree);
        ReadStringDtor(rs);
    }

    return SUCCESS;
}