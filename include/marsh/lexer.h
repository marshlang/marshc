#pragma once

#include <marsh/string_view.h>
#include <stddef.h>
#include <marsh/token.h>
typedef struct{
   const char* source;
   size_t length;
   size_t cur;
   size_t line;
   size_t column;
   StringView source_name;
} Lexer;

Lexer lexer_create(const char* source, StringView src_name, size_t length);
Token lexer_next(Lexer *lexer);
