/* sha3.c
 *
 * The sha3 hash function.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>
#include <string.h>

#include "nettle/sha3.h"

#include "macros.h"

/* 为什么这里不使用 nettle 自带的 memxor() 操作.
 *
 * 因为如果要是将 nettle 的 memxor.h,memxor.c 文件引入,那么在 config.h 中还得配置若干宏,
 * 最关键是,异或操作已经继承到 pp_qq/common/cipher 模块中了.
 */
static void *
memxor(void * const dst_in, const void *src_in, size_t s)
{
    unsigned char *optr = (unsigned char*)(dst_in);
    const unsigned char *iptr = (const unsigned char*)(src_in);

    size_t i = 0;
    for (i = 0; i < s; ++i)
        optr[i] ^= iptr[i];

    return dst_in;
}

static void
sha3_absorb (struct sha3_state *state, unsigned length, const uint8_t *data)
{
  assert ( (length & 7) == 0);
#if WORDS_BIGENDIAN
  {
    uint64_t *p;
    for (p = state->a; length > 0; p++, length -= 8, data += 8)
      *p ^= LE_READ_UINT64 (data);
  }
#else /* !WORDS_BIGENDIAN */
  memxor (state->a, data, length);
#endif

  sha3_permute (state);
}

unsigned
_sha3_update (struct sha3_state *state,
          unsigned block_size, uint8_t *block,
          unsigned pos,
          size_t length, const uint8_t *data)
{
  if (pos > 0)
    {
      unsigned left = block_size - pos;
      if (length < left)
    {
      memcpy (block + pos, data, length);
      return pos + length;
    }
      else
    {
      memcpy (block + pos, data, left);
      data += left;
      length -= left;
      sha3_absorb (state, block_size, block);
    }
    }
  for (; length >= block_size; length -= block_size, data += block_size)
    sha3_absorb (state, block_size, data);

  memcpy (block, data, length);
  return length;
}

void
_sha3_pad (struct sha3_state *state,
       unsigned block_size, uint8_t *block, unsigned pos)
{
  assert (pos < block_size);
  block[pos++] = 1;

  memset (block + pos, 0, block_size - pos);
  block[block_size - 1] |= 0x80;

  sha3_absorb (state, block_size, block);
}
