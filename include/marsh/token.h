#pragma once
#include <marsh/string_view.h>
#include <stddef.h>
typedef struct{
    size_t line;
    size_t col;
    size_t offset;
    size_t length;
    StringView source_name;
} SourceSpan;

typedef enum{
    //keywords
    KEYWORD_FUN,
    //symbols
    SYMBOL_LPAREN,
    SYMBOL_RPAREN,
    SYMBOL_LBRACE,
    SYMBOL_RBRACE,
    //literals
    LITERAL_INT,
    LITERAL_ID,
    //special
    SPECIAL_EOF,
    SPECIAL_UNKOWN
} TokenKind;

typedef struct {
    SourceSpan span;
    TokenKind kind;
    StringView value;
} Token;
