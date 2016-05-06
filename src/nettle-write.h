/* nettle-write.h
 *
 * Prototypes for some internal functions to write out word-sized data
 * to byte arrays. */

#ifndef NETTLE_WRITE_H_INCLUDED
#define NETTLE_WRITE_H_INCLUDED

#include "nettle-stdint.h"

/* Write the word array at SRC to the byte array at DST, using little
   endian (le) or big endian (be) byte order, and truncating the
   result to LENGTH bytes. */

/* FIXME: Use a macro shortcut to memcpy for native endianness. */

void
_nettle_write_le64(size_t length, uint8_t *dst,
		   uint64_t *src);

#endif /* NETTLE_WRITE_H_INCLUDED */
