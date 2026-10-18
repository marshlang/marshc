#include "marsh/string_view.h"
#include <marsh/token.h>
#include <marsh/lexer.h>
#include <stddef.h>
#include <string.h>

static char peek(const Lexer* lexer){
    if(lexer->cur >= lexer->length)
        return '\0';

    return lexer->source[lexer->cur];
}

static char advance(Lexer* lexer){
    char c = peek(lexer);

    if(lexer->cur >= lexer->length)
        return  '\0';

    lexer->cur++;

    if(c == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }

    return c;
}

static Token make_token(TokenKind kind, StringView source_name, size_t start, size_t length, size_t line, size_t column){
    return (Token){
        .kind = kind,
        .value = {0},
        .span = {
            .line = line,
            .col = column,
            .offset = start,
            .length = length,
            .source_name = source_name
        }
    };
}

Lexer lexer_create(const char *source, StringView src_name, size_t length){
    return (Lexer){
        .source = source,
        .source_name = src_name,
        .length = length,
        .cur = 0,
        .line = 1,
        .column = 1
    };
}

Token lexer_next(Lexer *lexer) {
    while (peek(lexer) == ' ' ||
           peek(lexer) == '\t' ||
           peek(lexer) == '\n' ||
           peek(lexer) == '\r') {
        advance(lexer);
    }

    size_t start = lexer->cur;
    size_t line = lexer->line;
    size_t col = lexer->column;

    if (start >= lexer->length) {
        return make_token(SPECIAL_EOF,lexer->source_name, start, 0, line, col);
    }

    char c = advance(lexer);
    TokenKind kind = SPECIAL_UNKOWN;

    switch (c) {
        case '(': kind = SYMBOL_LPAREN; break;
        case ')': kind = SYMBOL_RPAREN; break;
        case '{': kind = SYMBOL_LBRACE; break;
        case '}': kind = SYMBOL_RBRACE; break;
        case ':': kind = SYMBOL_COLON; break;

        default:
            if (c >= '0' && c <= '9') {
                while (peek(lexer) >= '0' &&
                       peek(lexer) <= '9') {
                    advance(lexer);
                }

                kind = LITERAL_INT;
            }
            else if ((c >= 'a' && c <= 'z') ||
                     (c >= 'A' && c <= 'Z') ||
                     c == '_') {

                while (
                    (peek(lexer) >= 'a' && peek(lexer) <= 'z') ||
                    (peek(lexer) >= 'A' && peek(lexer) <= 'Z') ||
                    (peek(lexer) >= '0' && peek(lexer) <= '9') ||
                    peek(lexer) == '_'
                ) {
                    advance(lexer);
                }

                kind = LITERAL_ID;
                if (lexer->cur - start == 3 &&
                    memcmp(lexer->source + start, "fun", 3) == 0)
                    kind = KEYWORD_FUN;
            }

            break;
    }

    Token token = make_token(
        kind,
        lexer->source_name,
        start,
        lexer->cur - start,
        line,
        col
    );
    token.value = (StringView){lexer->source + start, token.span.length};
    return token;
}
