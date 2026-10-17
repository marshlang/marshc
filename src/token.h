#pragma once
#include <stddef.h>
#include<marsh/string_view.h>

typedef enum{
    //keywords
    KEYWORD_FUN,
    //symbols
    SYMBOL_LPAREN,
    SYMBOL_RPAREN,
    SYMBOL_LBRACE,
    SYMBOL_RBRACE,
    //literals
    LITERAL_INT
} TokenType;

typedef struct{
    size_t line;
    size_t col;
    size_t offset;
} SourceSpan;

typedef struct{
    SourceSpan span;
    StringView value;
    TokenType kind;
} Token;
