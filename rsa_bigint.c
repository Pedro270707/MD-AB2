#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rsa_bigint.h"

#define KARATSUBA_THRESHOLD 32
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

struct BigInt *bigint_create_with_size(uint32_t size) {
    struct BigInt *list = (struct BigInt *) malloc(sizeof(struct BigInt) + size * sizeof(uint32_t));

    if (list == NULL) {
        return NULL;
    }

    list->size = size;
    list->sign = SIGN_POSITIVE;
    list->arr = (uint32_t *) (list + 1);

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

struct BigInt *bigint_create_from_number(int64_t number) {
    if (number < 0) {
        struct BigInt *result = bigint_create_from_unumber((uint64_t) (-number));
        result->sign = SIGN_NEGATIVE;
        return result;
    }
    return bigint_create_from_unumber((uint64_t) number);
}

struct BigInt *bigint_create(char *number) {
    
}

int bigint_is_zero(const struct BigInt *bigint) {
    return bigint->sign == SIGN_ZERO || bigint->size == 0;
}

static struct BigInt *bigint_remove_leading_zeros(struct BigInt *bigint) {
    uint32_t size = bigint->size;
    for (uint32_t i = bigint->size; i > 0; i--) {
        if (bigint->arr[i - 1] == 0) {
            size--;
        }
    }

    bigint->size = size;
    if (size == 0) {
        bigint->sign = SIGN_ZERO;
    }

    struct BigInt *new_bigint = (struct BigInt *) realloc(bigint, sizeof(struct BigInt) + size * sizeof(uint32_t));
    
    if (new_bigint == NULL) {
        return NULL;
    }

    new_bigint->arr = (uint32_t *)(new_bigint + 1);

    return new_bigint;
}

void bigint_print_as_hex(const struct BigInt *bigint) {
    if (bigint_is_zero(bigint)) {
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

struct BigInt *bigint_add_bits(uint32_t first_size, const uint32_t *first, uint32_t second_size, const uint32_t *second, uint32_t offset) {
    uint32_t final_size;
    uint32_t max_size = max(first_size, second_size);
    uint32_t min_size = min(first_size, second_size);
    final_size = max(max_size, min_size + offset) + 1;
    
    struct BigInt *result = bigint_create_with_size(final_size);

    uint32_t carry = 0;
    for (uint32_t i = 0; i < final_size; i++) {
        uint64_t value = carry;

        if (i < first_size) {
            value += (uint64_t) first[i];
        }
        
        if (i >= offset && (i - offset) < second_size) {
            value += (uint64_t) second[i - offset];
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
    if (bigint_is_zero(first)) return bigint_copy(second);
    if (bigint_is_zero(second)) return bigint_copy(first);

    struct BigInt *result;
    if (first->sign == second->sign) {
        result = bigint_add_bits(first->size, first->arr, second->size, second->arr, 0);
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

struct BigInt *bigint_grade_school_multiply(const struct BigInt *first, const struct BigInt *second) {
    uint32_t final_size = first->size + second->size;
    struct BigInt *result = bigint_create_with_size(final_size);

    for (uint32_t i = 0; i < first->size; i++) {
        if (first->arr[i] == 0) continue;
        
        uint64_t carry = 0;
        for (uint32_t j = 0; j < second->size; j++) {
            uint32_t result_index = i + j;
            uint64_t value = (uint64_t) first->arr[i] * (uint64_t) second->arr[j] + result->arr[result_index] + carry;

            result->arr[result_index] = (uint32_t) value; // least significant 32 bits
            carry = value >> 32;
        }

        result->arr[i + second->size] += (uint32_t) carry;
    }

    return bigint_remove_leading_zeros(result);
}

struct BigInt *bigint_karatsuba_multiply(uint32_t first_size, const uint32_t *first, uint32_t second_size, const uint32_t *second) {
    if (first_size <= KARATSUBA_THRESHOLD || second_size <= KARATSUBA_THRESHOLD) {
        struct BigInt temp_1 = (struct BigInt) { .size = first_size, .arr = (uint32_t *) first };
        struct BigInt temp_2 = (struct BigInt) { .size = second_size, .arr = (uint32_t *) second };
        return bigint_grade_school_multiply(&temp_1, &temp_2);
    }

    uint32_t split_point = max(first_size, second_size) / 2;

    uint32_t first_low_size;
    uint32_t first_high_size;
    if (first_size < split_point) {
        first_low_size = first_size;
        first_high_size = 0;
    } else {
        first_low_size = split_point;
        first_high_size = first_size - split_point;
    }
    const uint32_t *first_low = first;
    const uint32_t *first_high = first + split_point;

    uint32_t second_low_size;
    uint32_t second_high_size;
    if (second_size < split_point) {
        second_low_size = second_size;
        second_high_size = 0;
    } else {
        second_low_size = split_point;
        second_high_size = second_size - split_point;
    }
    const uint32_t *second_low = second;
    const uint32_t *second_high = second + split_point;

    struct BigInt *low_product = bigint_karatsuba_multiply(first_low_size, first_low, second_low_size, second_low);
    struct BigInt *high_product = bigint_karatsuba_multiply(first_high_size, first_high, second_high_size, second_high);

    struct BigInt *first_sum = bigint_add_bits(first_low_size, first_low, first_high_size, first_high, 0);
    struct BigInt *second_sum = bigint_add_bits(second_low_size, second_low, second_high_size, second_high, 0);

    struct BigInt *product = bigint_karatsuba_multiply(first_sum->size, first_sum->arr, second_sum->size, second_sum->arr);

    struct BigInt *subtraction_1 = bigint_subtract(product, low_product);
    struct BigInt *subtraction_2 = bigint_subtract(subtraction_1, high_product);
    
    struct BigInt *result_1 = bigint_add_bits(high_product->size, high_product->arr, subtraction_2->size, subtraction_2->arr, split_point);
    struct BigInt *result_2 = bigint_add_bits(result_1->size, result_1->arr, low_product->size, low_product->arr, 2 * split_point);

    free(low_product);
    free(high_product);
    free(first_sum);
    free(second_sum);
    free(product);
    free(subtraction_1);
    free(subtraction_2);
    free(result_1);

    return bigint_remove_leading_zeros(result_2);
}

struct BigInt *bigint_multiply(const struct BigInt *first, const struct BigInt *second) {
    if (bigint_is_zero(first) || bigint_is_zero(second)) return bigint_create_zero();
    struct BigInt *result = bigint_karatsuba_multiply(first->size, first->arr, second->size, second->arr);
    if (first->sign != second->sign) {
        result->sign = SIGN_NEGATIVE;
    }
    return result;
}

// Integer-like division: first // second
struct BigInt *bigint_divide(const struct BigInt *first, const struct BigInt *second) {
    
}