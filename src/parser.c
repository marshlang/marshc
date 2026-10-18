#include <marsh/ast.h>
#include <marsh/lexer.h>
#include <marsh/string_view.h>
#include <marsh/token.h>
#include <marsh/parser.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->current = lexer_next(lexer);
}

static const char* token_kind_name(TokenKind kind) {
    switch (kind) {
        case KEYWORD_FUN: return "fun";
        case SYMBOL_LPAREN: return "(";
        case SYMBOL_RPAREN: return ")";
        case SYMBOL_LBRACE: return "{";
        case SYMBOL_RBRACE: return "}";
        case SYMBOL_COLON: return ":";
        case LITERAL_INT: return "integer";
        case LITERAL_ID: return "identifier";
        case SPECIAL_EOF: return "end of file";
        case SPECIAL_UNKOWN: return "unknown token";
    }
    return "unknown token";
}

Token parser_consume(Parser* parser, TokenKind expected_kind) {
    Token token = parser->current;

    if (token.kind != expected_kind) {
        fprintf(stderr, "%.*s:%zu:%zu: error: unexpected token: \"%.*s\" expected \"%s\"\n",
                (int)token.span.source_name.length, token.span.source_name.data,
                token.span.line, token.span.col, (int)token.value.length,
                token.value.data ? token.value.data : "", token_kind_name(expected_kind));
        return (Token){.kind = SPECIAL_UNKOWN, .span = token.span};
    }

    parser->current = lexer_next(parser->lexer);
    return token;
}

void parser_free(Parser* parser){
    free(parser);
}

static AstTypeKind id_to_type(StringView id){
    if(string_view_cmp_cstr(id, "int"))
        return AST_TYPE_INT;
    return 0;
} 

static AstType parse_type(Parser* parser){
    AstTypeKind kind = 0;
    if(parser->current.kind == LITERAL_ID){
       kind = id_to_type(parser->current.value); 
    }
    else {
        printf("what is this return type brother\n"); //TODO: print pretty error
        exit(-1);
    }
    return (AstType){
        .kind = kind
    };
}

static AstDecl* parse_fun(Parser* parser)
{
    AstDecl *decl = calloc(1, sizeof(*decl));
    AstExpr *expr = calloc(1, sizeof(*expr));
    AstStmt *stmt = calloc(1, sizeof(*stmt));
    AstType type = {0};

    if (decl == NULL || expr == NULL || stmt == NULL) {
        free(decl);
        free(expr);
        free(stmt);
        return NULL;
    }

    parser_consume(parser, KEYWORD_FUN);

    Token name = parser_consume(parser, LITERAL_ID);

    if (name.kind == SPECIAL_UNKOWN) goto fail;

    StringView fun_name = name.value;

    if (parser_consume(parser, SYMBOL_LPAREN).kind == SPECIAL_UNKOWN) goto fail;
    if (parser_consume(parser, SYMBOL_RPAREN).kind == SPECIAL_UNKOWN) goto fail;

    if(parser->current.kind == SYMBOL_COLON){
        (void)parser_consume(parser, SYMBOL_COLON);
        Token type_token = parser_consume(parser, LITERAL_ID);
        if (type_token.kind == SPECIAL_UNKOWN) goto fail;
        type = (AstType){.kind = id_to_type(type_token.value)};
    }

    if (parser_consume(parser, SYMBOL_LBRACE).kind == SPECIAL_UNKOWN) goto fail;

    Token body = parser_consume(parser, LITERAL_INT);

    if (body.kind == SPECIAL_UNKOWN) goto fail;

    int64_t value;
    if (!string_view_to_int(body.value, &value)) goto fail;

    expr->kind = AST_EXPR_INT;
    expr->as.int_value = value;
    expr->span = body.span;

    if (parser_consume(parser, SYMBOL_RBRACE).kind == SPECIAL_UNKOWN) goto fail;

    stmt->kind = AST_STMT_EXPR;
    stmt->as.expr = expr;
    decl->kind = AST_DECL_FUNCTION;
    decl->as.function.name = fun_name;
    decl->as.function.body = stmt;
    decl->as.function.return_type = type.kind;
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


 

