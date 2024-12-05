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

    PRINT_TO_TEX("\\hspace{1cm}Дорогие читатели, это моя первая серьёзная (честно) работа по математическому анализу "
                 "(опустим тот факт, что это 2 том моей книги). Здесь я хотел бы обсудить с вами важнейший "
                 "раздел математического анализа -- \\textbf{Дифференцальное исчисление}. Я уверен, что "
                 "эту книгу читают люди, прочувствовашие всю красоту матанализа и изучившие достаточное "
                 "количество теорем, поэтому о производных элементарных функций я даже не буду говорить"
                 ", ведь все они очевидны любому советскому детсадовцу, но, если вам вдруг что-то не очевидно, "
                 "то примите мои соболезнования и обязательно изучите учебники Редкозубова, Зорича и Иванова.\\vspace{0.5cm}\n\n");

    PRINT_TO_TEX("\\hspace{1cm}В качестве несложного примера продифференцируем следующее выражение:\n\n");

    return SUCCESS;
}

FuncReturnCode TeXEndAndClose(FILE* tex_file) {
    if (!tex_file) return FILE_ERROR;

    PRINT_TO_TEX("\n\\end{document}\n");

    fclose(tex_file);

    return SUCCESS;
}

FuncReturnCode TeXSubTreePrint(FILE* tex_file, const Node* node) {
    ASSERT(tex_file != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(node     != NULL, "NULL POINTER WAS PASSED!\n");

    if (!node) return SUCCESS;

    const char* op_name = NULL;
    int op_number = -1;

    switch (node->type) {
        case NUM:
            PRINT_TO_TEX(" {%3lg} ", node->data);
            break;

        case VAR:
            PRINT_TO_TEX(" {x} ");
            break;

        case UN_OP:
            op_number = FindOperation((int)(node->data));
            op_name = OPERATIONS[op_number].name;

            PRINT_TO_TEX(" ( ");
            PRINT_TO_TEX(" \\%s ", op_name);
            TeXSubTreePrint(tex_file, node->right);
            PRINT_TO_TEX(" ) ");

            break;

        case BI_OP:
            op_number = FindOperation((int)(node->data));
            PRINT_TO_TEX(" ( ");

            if (OPERATIONS[op_number].OpCode == DIV) PRINT_TO_TEX(" \\frac");

            PRINT_TO_TEX(" { ");
            TeXSubTreePrint(tex_file, node->left);
            PRINT_TO_TEX(" } ");

            if (OPERATIONS[op_number].OpCode == MUL) {
                PRINT_TO_TEX(" \\cdot");
            } else if (OPERATIONS[op_number].OpCode != DIV) PRINT_TO_TEX(" %s ", OPERATIONS[op_number].name);

            PRINT_TO_TEX(" { ");
            TeXSubTreePrint(tex_file, node->right);
            PRINT_TO_TEX(" } ");

            PRINT_TO_TEX(" ) ");
            break;

        default:
            fprintf(stderr, RED("Error with node type!\n"));
            break;
    }

    return SUCCESS;
}

int FindOperation(const int node_type) {
    for (size_t i = 0; i < OPERATIONS_COUNT; i++) {
        if (OPERATIONS[i].OpCode == node_type) return (int)i;
    }

    return -1;
}