#include <stdint.h>

#ifndef RSA_BIGINT_H
#define RSA_BIGINT_H

enum Sign {
    SIGN_NEGATIVE = -1,
    SIGN_ZERO = 0,
    SIGN_POSITIVE = 1
};

struct BigInt {
    enum Sign sign;
    uint32_t size;
    uint32_t arr[]; // Little-endian
};

struct BigInt *bigint_create_with_size(uint32_t size);
struct BigInt *bigint_create_zero(void);
struct BigInt *bigint_create_from_unumber(uint64_t number);
struct BigInt *bigint_create_from_number(int64_t number);
struct BigInt *bigint_create(char *number);
int bigint_is_zero(const struct BigInt *bigint);
void bigint_print_as_hex(const struct BigInt *bigint);
int bigint_compare_magnitude(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_copy(const struct BigInt *bigint);
struct BigInt *bigint_add_bits(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_subtract_bits(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_add(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_subtract(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_grade_school_multiply(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_multiply(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_divide(const struct BigInt *first, const struct BigInt *second);

#endif