/* aes-decrypt-internal.c
 *
 * Decryption function for the aes/rijndael block cipher.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>

#include "aes-internal.h"
#include "macros.h"

void
_nettle_aes_decrypt(const struct aes_ctx *ctx,
		    const struct aes_table *T,
		    size_t length, uint8_t *dst,
		    const uint8_t *src)
{
  FOR_BLOCKS(length, dst, src, AES_BLOCK_SIZE)
    {
      uint32_t w0, w1, w2, w3;		/* working ciphertext */
      uint32_t t0, t1, t2, t3;
      unsigned round;
      
      /* Get clear text, using little-endian byte order.
       * Also XOR with the first subkey. */

      w0 = LE_READ_UINT32(src)      ^ ctx->keys[0];
      w1 = LE_READ_UINT32(src + 4)  ^ ctx->keys[1];
      w2 = LE_READ_UINT32(src + 8)  ^ ctx->keys[2];
      w3 = LE_READ_UINT32(src + 12) ^ ctx->keys[3];

      for (round = 1; round < ctx->nrounds; round++)
	{
	  t0 = AES_ROUND(T, w0, w3, w2, w1, ctx->keys[4*round]);
	  t1 = AES_ROUND(T, w1, w0, w3, w2, ctx->keys[4*round + 1]);
	  t2 = AES_ROUND(T, w2, w1, w0, w3, ctx->keys[4*round + 2]);
	  t3 = AES_ROUND(T, w3, w2, w1, w0, ctx->keys[4*round + 3]);

	  /* We could unroll the loop twice, to avoid these
	     assignments. If all eight variables fit in registers,
	     that should give a slight speedup. */
	  w0 = t0;
	  w1 = t1;
	  w2 = t2;
	  w3 = t3;
	}

      /* Final round */

      t0 = AES_FINAL_ROUND(T, w0, w3, w2, w1, ctx->keys[4*round]);
      t1 = AES_FINAL_ROUND(T, w1, w0, w3, w2, ctx->keys[4*round + 1]);
      t2 = AES_FINAL_ROUND(T, w2, w1, w0, w3, ctx->keys[4*round + 2]);
      t3 = AES_FINAL_ROUND(T, w3, w2, w1, w0, ctx->keys[4*round + 3]);

      LE_WRITE_UINT32(dst, t0);
      LE_WRITE_UINT32(dst + 8, t2);
      LE_WRITE_UINT32(dst + 4, t1);
      LE_WRITE_UINT32(dst + 12, t3);
    }
}
