#include <marsh/ast.h>
#include <marsh/lexer.h>
#include <marsh/string_view.h>
#include <marsh/token.h>
#include <marsh/parser.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define advance() parser->current = lexer_next(parser->lexer)
#define consume() lexer_next(parser->lexer)

void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->current = lexer_next(lexer);
}

void parser_free(Parser *parser){
    free(parser);
}



static AstDecl *parse_fun(Parser *parser)
{
    AstDecl *decl = calloc(1, sizeof(*decl));
    AstExpr *expr = calloc(1, sizeof(*expr));
    AstStmt *stmt = calloc(1, sizeof(*stmt));

    if (decl == NULL || expr == NULL || stmt == NULL) {
        free(decl);
        free(expr);
        free(stmt);
        return NULL;
    }

    advance();
    if (parser->current.kind != LITERAL_ID) goto fail;

    StringView fun_name = parser->current.value;

    advance();
    if (parser->current.kind != SYMBOL_LPAREN) goto fail;

    advance();
    if (parser->current.kind != SYMBOL_RPAREN) goto fail;

    advance();
    if (parser->current.kind != SYMBOL_LBRACE) goto fail;

    advance();
    if (parser->current.kind != LITERAL_INT) goto fail;

    int64_t value;

    if (!string_view_to_int(parser->current.value, &value)) goto fail;

    expr->kind = AST_EXPR_INT;
    expr->as.int_value = value;
    expr->span = parser->current.span;

    advance();
    if (parser->current.kind != SYMBOL_RBRACE) goto fail;
    advance();

    stmt->kind = AST_STMT_EXPR;
    stmt->as.expr = expr;
    decl->kind = AST_DECL_FUNCTION;
    decl->as.function.name = fun_name;
    decl->as.function.body = stmt;
    return decl;

fail:
    free(stmt);
    free(expr);
    free(decl);
    return NULL;
}

static void ast_program_add(AstProgram* program, AstDecl* decl){
    decl->next = NULL;

    if(program->last == NULL){
        program->first = decl;
    }else{
        program->last->next = decl;
    }

    program->last = decl;
    program->function_count++;
}


AstDecl* parse_decl(Parser* parser){
    switch(parser->current.kind){
        case KEYWORD_FUN: 
            return parse_fun(parser);
        default: break;
        break;
    }

    return NULL;
}



AstProgram* parser_parse(Parser* parser){
    AstProgram* program = calloc(1, sizeof(*program));
    if (program == NULL)
        return NULL;

    while(parser->current.kind != SPECIAL_EOF){
       AstDecl *decl = parse_decl(parser);
       if (decl == NULL) {
           free(program);
           return NULL;
       }
       ast_program_add(program, decl);
    }
    return program;
}


 

