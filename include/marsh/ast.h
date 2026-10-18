#pragma once
#include "marsh/string_view.h"
#include <marsh/source_span.h>
#include <stddef.h>
#include <string.h>

typedef struct AstExpr AstExpr;
typedef struct AstStmt AstStmt;
typedef struct AstFunction AstFunction;
typedef struct AstDecl AstDecl;

typedef enum {
    AST_STMT_EXPR,
    AST_STMT_BLOCK
} AstStmtKind;

typedef enum{
    AST_EXPR_INT
} AstExprKind;

typedef enum{
    AST_DECL_FUNCTION
} AstDeclKind;

struct AstExpr{
    AstExprKind kind;
    SourceSpan span;

    union {
        long long int_value;
    } as;
};

typedef struct{
    AstStmt* first;
    AstStmt* last;
    size_t count;
} AstStmtList;

typedef struct {
    AstStmtList statements;
} AstBlockStmt;

struct AstStmt {
    AstStmtKind kind;
    SourceSpan span;

    union{
        AstExpr* expr;
        AstBlockStmt block;
    } as;

    AstStmt* next;
};

struct AstFunction {
    StringView name;
    AstStmt *body;
    AstFunction* next;
};

struct AstDecl {
    AstDeclKind kind;
    SourceSpan span;

    union {
        AstFunction function;
    } as;

    AstDecl* next;
};

typedef struct{
    AstDecl* first;
    AstDecl* last;
    size_t function_count;
} AstProgram;
