/* sha3-256.c
 *
 * The sha3 hash function, 256 bit output.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <stddef.h>
#include <string.h>

#include "sha3.h"

#include "nettle-write.h"

void
sha3_256_init (struct sha3_256_ctx *ctx)
{
  memset (&ctx->state, 0, offsetof (struct sha3_256_ctx, block));
}

void
sha3_256_update (struct sha3_256_ctx *ctx,
		 size_t length,
		 const uint8_t *data)
{
  ctx->index = _sha3_update (&ctx->state, SHA3_256_DATA_SIZE, ctx->block,
			     ctx->index, length, data);
}

void
sha3_256_digest(struct sha3_256_ctx *ctx,
		size_t length,
		uint8_t *digest)
{
  _sha3_pad (&ctx->state, SHA3_256_DATA_SIZE, ctx->block, ctx->index);
  _nettle_write_le64 (length, digest, ctx->state.a);
  sha3_256_init (ctx);
}
