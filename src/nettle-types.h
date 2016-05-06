/* nettle-types.h */

#ifndef NETTLE_TYPES_H
#define NETTLE_TYPES_H

/* Pretend these types always exists. Nettle doesn't use them. */
#define _STDINT_HAVE_INT_FAST32_T 1

#include "nettle-stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Randomness. Used by key generation and dsa signature creation. */
typedef void nettle_random_func(void *ctx,
				size_t length, uint8_t *dst);

/* Progress report function, mainly for key generation. */
typedef void nettle_progress_func(void *ctx, int c);

/* Realloc function, used by struct nettle_buffer. */
typedef void *nettle_realloc_func(void *ctx, void *p, size_t length);

/* Ciphers */
typedef void nettle_set_key_func(void *ctx,
				 size_t length,
				 const uint8_t *key);

/* Uses a void * for cipher contexts.

   For block ciphers it would make sense with a const void * for the
   context, but we use the same typedef for stream ciphers where the
   internal state changes during the encryption. */

typedef void nettle_crypt_func(void *ctx,
			       size_t length, uint8_t *dst,
			       const uint8_t *src);

/* Hash algorithms */
typedef void nettle_hash_init_func(void *ctx);
typedef void nettle_hash_update_func(void *ctx,
				     size_t length,
				     const uint8_t *src);
typedef void nettle_hash_digest_func(void *ctx,
				     size_t length, uint8_t *dst);

/* ASCII armor codecs. NOTE: Experimental and subject to change. */

typedef size_t nettle_armor_length_func(size_t length);
typedef void nettle_armor_init_func(void *ctx);

typedef size_t nettle_armor_encode_update_func(void *ctx,
					       uint8_t *dst,
					       size_t src_length,
					       const uint8_t *src);

typedef size_t nettle_armor_encode_final_func(void *ctx, uint8_t *dst);

typedef int nettle_armor_decode_update_func(void *ctx,
					    size_t *dst_length,
					    uint8_t *dst,
					    size_t src_length,
					    const uint8_t *src);

typedef int nettle_armor_decode_final_func(void *ctx);

#ifdef __cplusplus
}
#endif

#endif /* NETTLE_TYPES_H */
