/* aes.h
 *
 * The aes/rijndael block cipher.
 */

#ifndef NETTLE_AES_H_INCLUDED
#define NETTLE_AES_H_INCLUDED

#include "nettle-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Name mangling */
#define aes_set_encrypt_key nettle_aes_set_encrypt_key
#define aes_set_decrypt_key nettle_aes_set_decrypt_key
#define aes_invert_key nettle_aes_invert_key
#define aes_encrypt nettle_aes_encrypt
#define aes_decrypt nettle_aes_decrypt

#define AES_BLOCK_SIZE 16

/* Variable key size between 128 and 256 bits. But the only valid
 * values are 16 (128 bits), 24 (192 bits) and 32 (256 bits). */
#define AES_MIN_KEY_SIZE 16
#define AES_MAX_KEY_SIZE 32

#define AES_KEY_SIZE 32

#define AES128_KEY_SIZE 16
#define AES192_KEY_SIZE 24
#define AES256_KEY_SIZE 32

/* FIXME: Change to put nrounds first, to make it possible to use a
   truncated ctx struct, with less subkeys, for the shorter key
   sizes? */
struct aes_ctx
{
  uint32_t keys[60];  /* maximum size of key schedule */
  unsigned  nrounds;  /* number of rounds to use for our key size */
};

/// 初始化 aes_ctx,将其设置为加密模式,并将 [key,length) 设置为密钥.
void
aes_set_encrypt_key(struct aes_ctx *ctx,
		    size_t length, const uint8_t *key);

/// 初始化 aes_ctx,将其设置为解密模式,并将 [key,length) 设置为密钥.
void
aes_set_decrypt_key(struct aes_ctx *ctx,
		   size_t length, const uint8_t *key);

void
aes_invert_key(struct aes_ctx *dst,
	       const struct aes_ctx *src);
/**
 * 对 [src,src + length) 范围内的数据进行加密,结果存放在 dst 中.
 * @param src,length length 必须是数据块字节的整数倍,若多余一个数据快时,采用 ECB 模式.
 * @param dst 可以与 src 相同;但是不能重叠.
 */
void
aes_encrypt(const struct aes_ctx *ctx,
	    size_t length, uint8_t *dst,
	    const uint8_t *src);
/// @ref aes_encrypt().
void
aes_decrypt(const struct aes_ctx *ctx,
	    size_t length, uint8_t *dst,
	    const uint8_t *src);

#ifdef __cplusplus
}
#endif

#endif /* NETTLE_AES_H_INCLUDED */
