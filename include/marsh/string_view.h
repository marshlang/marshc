#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

static inline bool string_view_to_int(StringView view, int64_t *out)
{
    if (view.length == 0 || view.data == NULL || out == NULL) {
        return false;
    }

    size_t i = 0;
    bool negative = false;

    if (view.data[i] == '-' || view.data[i] == '+') {
        negative = view.data[i] == '-';

        if (++i == view.length) {
            return false;
        }
    }

    uint64_t value = 0;
    const uint64_t limit = negative
        ? (uint64_t)INT64_MAX + 1
        : (uint64_t)INT64_MAX;

    for (; i < view.length; ++i) {
        unsigned char c = (unsigned char)view.data[i];

        if (c < '0' || c > '9') {
            return false;
        }

        unsigned digit = c - '0';

        if (value > (limit - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
    }

    if (negative) {
        *out = value == (uint64_t)INT64_MAX + 1
            ? INT64_MIN
            : -(int64_t)value;
    } else {
        *out = (int64_t)value;
    }

    return true;
}

