//
// Created by Haifa Bogdan Adnan on 06/08/2018.
//

#ifndef ARIOMINER_DEFS_H
#define ARIOMINER_DEFS_H

#define ARGON2_RAW_LENGTH               32
#define ARGON2_TYPE_VALUE               2
#define ARGON2_VERSION                  0x13
#define IXIAN_SEED_SIZE                 156
#define IXIAN_NONCE_SIZE                64
#define IXIAN_EXPANDED_NONCE_SIZE       234172

#define ARGON2_BLOCK_SIZE               1024
#define ARGON2_DWORDS_IN_BLOCK          ARGON2_BLOCK_SIZE / 4
#define ARGON2_QWORDS_IN_BLOCK          ARGON2_BLOCK_SIZE / 8
#define ARGON2_OWORDS_IN_BLOCK          ARGON2_BLOCK_SIZE / 16
#define ARGON2_HWORDS_IN_BLOCK          ARGON2_BLOCK_SIZE / 32
#define ARGON2_512BIT_WORDS_IN_BLOCK    ARGON2_BLOCK_SIZE / 64
#define ARGON2_PREHASH_DIGEST_LENGTH    64
#define ARGON2_PREHASH_SEED_LENGTH      72

#ifdef __cplusplus 
extern "C" {
#endif

typedef struct block_ { uint64_t v[ARGON2_QWORDS_IN_BLOCK]; } block;

typedef struct Argon2Profile {
    uint32_t mem_cost;
    uint32_t thr_cost;
    uint32_t tm_cost;
    size_t memsize;
    int32_t *block_refs;
    size_t block_refs_size;
    char profile_name[15];
    int32_t *segments; // { start segment / current block, stop segment (excluding) / previous block, addressing type = 0 -> i, 1 -> d }
    uint32_t seg_size;
    uint32_t seg_count;
    uint32_t succ_idx; // 0 - idx are precalculated, 1 - idx are successive
    int pwd_len; // in dwords
    int salt_len; // in dwords
} argon2profile;

extern DLLEXPORT argon2profile argon2profile_1_2_1024;
extern DLLEXPORT argon2profile *argon2profile_default;

#ifdef __cplusplus
}
#endif

#endif //ARIOMINER_DEFS_H
