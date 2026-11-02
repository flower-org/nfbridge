/* SPDX-License-Identifier: Apache-2.0 */
#ifndef NFBRIDGE_CONFIG_H
#define NFBRIDGE_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "nfbridge/log.h"

#define NFB_DEFAULT_QUEUE 0
#define NFB_DEFAULT_SOCKET "/run/nfbridge/nfbridge.sock"
#define NFB_DEFAULT_TIMEOUT_MS 1000
/* Bytes of each packet copied from the kernel and sent to Java. Default: the whole packet. */
#define NFB_DEFAULT_COPY_RANGE 65535u
/* --headers-only copy range: IPv4 (<= 60) or IPv6 (40 + extension headers) + TCP (<= 60) headers */
#define NFB_HEADERS_ONLY_COPY_RANGE 256u
/* Smallest copy range that always holds a full IPv4 header plus TCP/UDP ports */
#define NFB_MIN_COPY_RANGE 64u

struct nfb_config {
    uint16_t queue_num;
    const char *socket_path;
    int timeout_ms;
    uint32_t copy_range;
    bool fail_open;
    enum nfb_log_level log_level;
};

enum nfb_config_result {
    NFB_CONFIG_OK = 0,
    NFB_CONFIG_EXIT_OK = 1,   /* --help / --version printed, exit 0 */
    NFB_CONFIG_EXIT_USAGE = 2 /* invalid arguments, exit with usage error */
};

enum nfb_config_result nfb_config_parse(struct nfb_config *cfg, int argc, char **argv);

#endif /* NFBRIDGE_CONFIG_H */
