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
    size_t size;
    uint32_t *arr; // Little-endian
};

struct BigInt *bigint_create_with_size(size_t size);
struct BigInt *bigint_create_zero(void);
struct BigInt *bigint_create_from_unumber(uint64_t number);
struct BigInt *bigint_create_from_number(int64_t number);
struct BigInt *bigint_create(char *number);
int bigint_is_zero(const struct BigInt *bigint);
void bigint_print_as_hex(const struct BigInt *bigint);
int bigint_compare_magnitude(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_copy(const struct BigInt *bigint);
struct BigInt *bigint_shl(const struct BigInt *bigint, size_t shift);
struct BigInt *bigint_shr(const struct BigInt *bigint, size_t shift);
struct BigInt *bigint_add_bits(size_t first_size, const uint32_t *first, size_t second_size, const uint32_t *second, size_t offset);
struct BigInt *bigint_subtract_bits(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_add(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_subtract(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_grade_school_multiply(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_karatsuba_multiply(size_t first_size, const uint32_t *first, size_t second_size, const uint32_t *second);
struct BigInt *bigint_multiply(const struct BigInt *first, const struct BigInt *second);
struct BigInt *bigint_divide(const struct BigInt *first, const struct BigInt *second);

#endif