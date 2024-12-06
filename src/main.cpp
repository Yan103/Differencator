#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BinaryTree.h"
#include "Differentiator.h"
#include "TreeDump.h"
#include "LaTeXCreate.h"

const char* INPUT_FILENAME = "../Differencator/Expressions/test1.txt";
#define TEX_DIRECTORY "TeXFiles/"
const char* TEX_FILENAME   = "../Differencator/TeXFiles/Solution.tex";

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

        PRINT_TO_TEX("$$ ");
        TeXSubTreePrint(tex_file, tree->root);
        PRINT_TO_TEX(" $$\n");

        Tree* diff_tree = TreeDiff(tree, tex_file);

        TeXEndAndClose(tex_file);

        system("pdflatex -aux-directory=" TEX_DIRECTORY " -output-directory="
                TEX_DIRECTORY " ../Differencator/TeXFiles/Solution.tex > NUL 2>&1");

        TREE_DUMP(diff_tree, "%s", __func__);

        MemoryFree(tree, diff_tree, rs);
    }

    return SUCCESS;
}