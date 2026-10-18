#pragma once
#include <marsh/token.h>
#include <marsh/lexer.h>
#include <marsh/ast.h>

typedef struct{
    Lexer* lexer;
    Token current;
    Token next;
} Parser;

void parser_init(Parser* parser, Lexer* lexer);
Token parser_consume(Parser* parser, TokenKind expected_kind);
AstProgram* parser_parse(Parser* parser);
void parser_free(Parser* parser);

