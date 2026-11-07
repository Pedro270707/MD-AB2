#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include "rsa_math.h"
#include "rsa_utility.h"

struct SecretKey scan_secret_key(void) {
    struct SecretKey key = { 0, 0, 0 };

    printf("Digite p, q, e: ");

    if (scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &key.p, &key.q, &key.e) != 3) {
        return (struct SecretKey){ 0, 0, 0 };
    }

    return key;
}

struct PublicKey scan_public_key(void) {
    struct PublicKey key = { 0, 0 };

    printf("Digite n, e: ");

    if (scanf("%" SCNu64 "%" SCNu64, &key.n, &key.e) != 2) {
        return (struct PublicKey){ 0, 0 };
    }

    return key;
}

struct PrivateKey to_private_key(struct SecretKey key) {
    int d = inverse_mod(key.e, (key.p - 1) * (key.q - 1));

    return (struct PrivateKey){ .n = key.p * key.q, .d = d };
}

struct PublicKey to_public_key(struct SecretKey key) {
    return (struct PublicKey){ .n = key.p * key.q, .e = key.e };
}
