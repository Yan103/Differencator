#include <stdio.h>

#include "LaTeXCreate.h"

FuncReturnCode TeXHeader(FILE* tex_file) {
    if (!tex_file) return FILE_ERROR;

    PRINT_TO_TEX("\\documentclass[12pt, a4paper]{article}\n"
                 "\\usepackage[margin=1in]{geometry}\n"
                 "\\usepackage{mathtext}\n"
                 "\\usepackage[T2A]{fontenc}\n"
                 "\\usepackage[utf8]{inputenc}\n"
                 "\\usepackage{amsmath, amssymb}\n"
                 "\\usepackage[english, russian]{babel}\n"
                 "\n"
                 "\\title{Основы дифференцального исчисления (2 том)}\n"
                 "\\author{Фазлеев Ян}\n"
                 "\n"
                 "\\begin{document}\n"
                 "\\maketitle\n"
                 "\\setlength{\\parindent}{0pt}\n"
                 "\\large\n"
                 "\n");

    return SUCCESS;
}

FuncReturnCode TeXEndAndClose(FILE* tex_file) {
    if (!tex_file) return FILE_ERROR;

    PRINT_TO_TEX("\n\\end{document}\n");

    fclose(tex_file);

    return SUCCESS;
}