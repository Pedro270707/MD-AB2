#ifndef RSA_UTILITY_H
#define RSA_UTILITY_H
#include <stdint.h>

struct SecretKey {
    uint64_t p;
    uint64_t q;
    uint64_t e;
};

struct PrivateKey {
    uint64_t n;
    uint64_t d;
};

struct PublicKey {
    uint64_t n;
    uint64_t e;
};

struct SecretKey scan_secret_key(void);
struct PublicKey scan_public_key(void);
struct PrivateKey to_private_key(struct SecretKey key);
struct PublicKey to_public_key(struct SecretKey key);

#endif