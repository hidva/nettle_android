/* aes-internal.h
 *
 * The aes/rijndael block cipher.
 */

#ifndef NETTLE_AES_INTERNAL_H_INCLUDED
#define NETTLE_AES_INTERNAL_H_INCLUDED

#include "aes.h"

/* Name mangling */
#define _aes_encrypt _nettle_aes_encrypt
#define _aes_decrypt _nettle_aes_decrypt
#define _aes_encrypt_table _nettle_aes_encrypt_table

/* Define to use only small tables. */
#ifndef AES_SMALL
# define AES_SMALL 0
#endif

#if AES_SMALL
# define AES_TABLE_SIZE 1
#else
# define AES_TABLE_SIZE 4
#endif

struct aes_table
{
  uint8_t sbox[0x100];
  uint32_t table[AES_TABLE_SIZE][0x100];
};

void
_aes_encrypt(const struct aes_ctx *ctx,
	     const struct aes_table *T,
	     size_t length, uint8_t *dst,
	     const uint8_t *src);

void
_aes_decrypt(const struct aes_ctx *ctx,
	     const struct aes_table *T,
	     size_t length, uint8_t *dst,
	     const uint8_t *src);

/* Macros */
/* Get the byte with index 0, 1, 2 and 3 */
#define B0(x) ((x) & 0xff)
#define B1(x) (((x) >> 8) & 0xff)
#define B2(x) (((x) >> 16) & 0xff)
#define B3(x) (((x) >> 24) & 0xff)

#define SUBBYTE(x, box) ((uint32_t)(box)[B0(x)]		\
		      | ((uint32_t)(box)[B1(x)] << 8)	\
		      | ((uint32_t)(box)[B2(x)] << 16)	\
		      | ((uint32_t)(box)[B3(x)] << 24))

#define AES_ROUND(T, w0, w1, w2, w3, k)		\
((  T->table[0][ B0(w0) ]			\
  ^ T->table[1][ B1(w1) ]			\
  ^ T->table[2][ B2(w2) ]			\
  ^ T->table[3][ B3(w3) ]) ^ (k))

#define AES_FINAL_ROUND(T, w0, w1, w2, w3, k)		\
((   (uint32_t) T->sbox[ B0(w0) ]			\
  | ((uint32_t) T->sbox[ B1(w1) ] << 8)			\
  | ((uint32_t) T->sbox[ B2(w2) ] << 16)		\
  | ((uint32_t) T->sbox[ B3(w3) ] << 24)) ^ (k))
     
/* Globally visible so that the same sbox table can be used by aes_set_encrypt_key */

extern const struct aes_table _aes_encrypt_table;
#define aes_sbox (_aes_encrypt_table.sbox)

#endif /* NETTLE_AES_INTERNAL_H_INCLUDED */
