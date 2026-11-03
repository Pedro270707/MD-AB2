#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rsa_bigint.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

struct BigInt *bigint_create_with_size(uint32_t size) {
    struct BigInt *list = (struct BigInt *) malloc(sizeof(struct BigInt) + size * sizeof(uint32_t));

    if (list == NULL) {
        return NULL;
    }

    list->size = size;
    list->sign = SIGN_POSITIVE;

    return list;
}

struct BigInt *bigint_create_zero() {
    struct BigInt *result = bigint_create_with_size(0);
    result->sign = SIGN_ZERO;
    return result;
}

struct BigInt *bigint_create_from_unumber(uint64_t number) {
    if (number == 0) {
        return bigint_create_zero();
    }

    if (number == ((uint32_t) number)) {
        struct BigInt *result = bigint_create_with_size(1);
        result->arr[0] = (uint32_t) number;
        return result;
    }

    struct BigInt *result = bigint_create_with_size(2);
    result->arr[0] = (uint32_t) number;
    result->arr[1] = (uint32_t) (number >> 32);
    return result;
}

struct BigInt *bigint_create(char *number) {
    
}

static struct BigInt *bigint_remove_leading_zeros(struct BigInt *bigint) {
    uint32_t size = bigint->size;
    for (uint32_t i = bigint->size; i > 0; i--) {
        if (bigint->arr[i - 1] == 0) {
            size--;
        }
    }
    bigint->size = size;
    return (struct BigInt *) realloc(bigint, sizeof(struct BigInt) + size * sizeof(uint32_t));
}

void bigint_print_as_hex(const struct BigInt *bigint) {
    if (bigint->size == 0 || bigint->sign == SIGN_ZERO) {
        printf("0");
        return;
    }

    if (bigint->sign == SIGN_NEGATIVE) {
        printf("-");
    }

    for (uint32_t i = bigint->size; i > 0; i--) {
        printf("%x", (uint32_t) bigint->arr[i - 1]);
    }
}

// 1 if first > second; -1 if second > first; else 0
int bigint_compare_magnitude(const struct BigInt *first, const struct BigInt *second) {
    if (first->size > second->size) {
        return 1;
    }
    if (second->size > first->size) {
        return -1;
    }

    for (uint32_t i = first->size; i > 0; i--) {
        if (first->arr[i - 1] != second->arr[i - 1]) {
            return first->arr[i - 1] > second->arr[i - 1] ? 1 : -1;
        }
    }
    return 0;
}

struct BigInt *bigint_copy(const struct BigInt *bigint) {
    struct BigInt *result = bigint_create_with_size(bigint->size);
    for (uint32_t i = 0; i < bigint->size; i++) {
        result->arr[i] = bigint->arr[i];
    }
    return result;
}

struct BigInt *bigint_add_bits(const struct BigInt *first, const struct BigInt *second) {
    uint32_t final_size = max(first->size, second->size) + 1;
    struct BigInt *result = bigint_create_with_size(final_size);

    uint32_t carry = 0;
    for (uint32_t i = 0; i < final_size; i++) {
        uint64_t value = carry;

        if (i < first->size) {
            value += (uint64_t) first->arr[i];
        }
        if (i < second->size) {
            value += (uint64_t) second->arr[i];
        }

        result->arr[i] = (uint32_t) value; // least significant 32 bits
        carry = (uint32_t) (value >> 32);
    }

    return bigint_remove_leading_zeros(result);
}

// first - second
struct BigInt *bigint_subtract_bits(const struct BigInt *first, const struct BigInt *second) {
    struct BigInt *result = bigint_create_with_size(first->size);

    uint32_t borrow = 0;
    uint32_t i;
    for (i = 0; i < second->size; i++) {
        uint64_t value = (uint64_t) first->arr[i] - (uint64_t) second->arr[i] - borrow;
        result->arr[i] = (uint32_t) value; // least significant 32 bits
        borrow = (uint32_t) (value >> 63);
    }

    for (; i < first->size; i++) {
        uint64_t value = (uint64_t) first->arr[i] - borrow;
        result->arr[i] = (uint32_t) value; // least significant 32 bits
        borrow = (uint32_t) (value >> 63);
    }
    
    return bigint_remove_leading_zeros(result);
}

struct BigInt *bigint_add(const struct BigInt *first, const struct BigInt *second) {
    if (first->sign == SIGN_ZERO) return bigint_copy(second);
    if (second->sign == SIGN_ZERO) return bigint_copy(first);

    struct BigInt *result;
    if (first->sign == second->sign) {
        result = bigint_add_bits(first, second);
        result->sign = first->sign;
        return result;
    }

    int magnitude = bigint_compare_magnitude(first, second);
    
    if (magnitude == 0) {
        return bigint_create_zero();
    }

    if (magnitude > 0) {
        printf("First is larger\n");
    } else {
        printf("Second is larger\n");
    }
    result = magnitude > 0 ? bigint_subtract_bits(first, second) : bigint_subtract_bits(second, first);

    if ((magnitude > 0 && first->sign == SIGN_NEGATIVE) || (magnitude < 0 && second->sign == SIGN_NEGATIVE)) {
        result->sign = SIGN_NEGATIVE;
    }

    return result;
}

// first - second
struct BigInt *bigint_subtract(const struct BigInt *first, const struct BigInt *second) {
    struct BigInt *subtracted = bigint_copy(second);
    if (subtracted->sign == SIGN_POSITIVE) {
        subtracted->sign = SIGN_NEGATIVE;
    } else if (subtracted->sign == SIGN_NEGATIVE) {
        subtracted->sign = SIGN_POSITIVE;
    }
    return bigint_add(first, subtracted);
}

struct BigInt *bigint_multiply(const struct BigInt *first, const struct BigInt *second) {

}

// Integer-like division: first // second
struct BigInt *bigint_divide(const struct BigInt *first, const struct BigInt *second) {
    
}