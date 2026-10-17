#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marsh/driver.h"
#include "marsh/lexer.h"

#define VERSION "0.1"

int driver_help(){
    printf("-v, --version   prints compiler version\n");
    return 0;
}

int driver_version(){
    printf("%s\n", VERSION);
    return 0;
}

static const char *token_kind_name(TokenKind kind) {
    switch (kind) {
        case KEYWORD_FUN: return "KEYWORD_FUN";
        case SYMBOL_LPAREN: return "SYMBOL_LPAREN";
        case SYMBOL_RPAREN: return "SYMBOL_RPAREN";
        case SYMBOL_LBRACE: return "SYMBOL_LBRACE";
        case SYMBOL_RBRACE: return "SYMBOL_RBRACE";
        case LITERAL_INT: return "LITERAL_INT";
        case LITERAL_ID: return "LITERAL_ID";
        case SPECIAL_EOF: return "SPECIAL_EOF";
        case SPECIAL_UNKOWN: return "SPECIAL_UNKOWN";
    }
    return "UNKNOWN_TOKEN_KIND";
}

int driver_lex_example(void) {
    const char *path = "examples/basic.marsh";
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror(path);
        return 1;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        perror(path);
        fclose(file);
        return 1;
    }
    long file_size = ftell(file);
    if (file_size < 0 || fseek(file, 0, SEEK_SET) != 0) {
        perror(path);
        fclose(file);
        return 1;
    }

    char *source = malloc((size_t)file_size + 1);
    if (!source) {
        fprintf(stderr, "Cannot allocate memory for %s\n", path);
        fclose(file);
        return 1;
    }
    size_t length = fread(source, 1, (size_t)file_size, file);
    if (length != (size_t)file_size) {
        fprintf(stderr, "Cannot read %s\n", path);
        free(source);
        fclose(file);
        return 1;
    }
    fclose(file);
    source[length] = '\0';

    Lexer lexer = lexer_create(source, (StringView){path, strlen(path)}, length);
    Token token;
    do {
        token = lexer_next(&lexer);
        printf("%zu:%zu %-16s %.*s\n", token.span.line, token.span.col,
               token_kind_name(token.kind), (int)token.span.length,
               source + token.span.offset);
    } while (token.kind != SPECIAL_EOF);

    free(source);
    return 0;
}
