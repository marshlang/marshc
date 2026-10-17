#pragma once
#include <stddef.h>
struct SourceSpan{
    size_t line;
    size_t col;
    size_t offset;
}
struct Token{
    SourceSpan sp
}
