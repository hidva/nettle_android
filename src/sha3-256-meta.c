/* sha3-256-meta.c */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "nettle-meta.h"

#include "sha3.h"

const struct nettle_hash nettle_sha3_256
= _NETTLE_HASH(sha3_256, SHA3_256);
