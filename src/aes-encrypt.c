/* aes-encrypt.c
 *
 * Encryption function for the aes/rijndael block cipher.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>

#include "aes-internal.h"

/* The main point on this function is to help the assembler
   implementations of _nettle_aes_encrypt to get the table pointer.
   For PIC code, the details can be complex and system dependent. */
void
aes_encrypt(const struct aes_ctx *ctx,
	    size_t length, uint8_t *dst,
	    const uint8_t *src)
{
  assert(!(length % AES_BLOCK_SIZE) );
  _aes_encrypt(ctx, &_aes_encrypt_table,
	       length, dst, src);
}
