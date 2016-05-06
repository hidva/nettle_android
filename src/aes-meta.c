/* aes-meta.c */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "nettle-meta.h"

#include "nettle/aes.h"

const struct nettle_cipher nettle_aes256
= _NETTLE_CIPHER_SAME(aes, AES, 256);
