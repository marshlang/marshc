#pragma once
#include <marsh/string_view.h>
#include <marsh/source_span.h>
#include <stddef.h>

 
typedef enum{
    //keywords
    KEYWORD_FUN,
    //symbols
    SYMBOL_LPAREN,
    SYMBOL_RPAREN,
    SYMBOL_LBRACE,
    SYMBOL_RBRACE,
    SYMBOL_COLON,
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
