#ifndef LATEXCREATE_H
#define LATEXCREATE_H

#include <stdio.h>

#include "BinaryTree.h"

#define PRINT_TO_TEX(__format__, ...) {fprintf(tex_file, __format__, ##__VA_ARGS__);}

FuncReturnCode TeXHeader(FILE* tex_file);

FuncReturnCode TeXEndAndClose(FILE* tex_file);

FuncReturnCode TeXSubTreePrint(FILE* tex_file, const Node* node);

int FindOperation(const int node_type);

#endif // LATEXCREATE_H