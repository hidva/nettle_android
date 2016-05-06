/* write-le64.c */


#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "nettle-write.h"

#include "macros.h"

void
_nettle_write_le64(size_t length, uint8_t *dst,
		   uint64_t *src)
{
  size_t i;
  size_t words;
  unsigned leftover;
  
  words = length / 8;
  leftover = length % 8;

  for (i = 0; i < words; i++, dst += 8)
    LE_WRITE_UINT64(dst, src[i]);

  if (leftover)
    {
      uint64_t word;
      
      word = src[i];

      do
	{
	  *dst++ = word & 0xff;
	  word >>= 8;
	}
      while (--leftover);
    }
}
