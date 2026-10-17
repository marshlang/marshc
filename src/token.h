#pragma once
#include <stddef.h>
#include<marsh/string_view.h>

typedef struct{
    size_t line;
    size_t col;
    size_t offset;
} SourceSpan;

typedef struct{
    SourceSpan span;
    StringView value;
} Token;
