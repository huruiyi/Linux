#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)    \
  do {                  \
    perror(msg);        \
    exit(EXIT_FAILURE); \
  } while (0)

int main(int argc, char *argv[]) {
  char buf[100];
  struct in_addr addr;
  int bits;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s presentation-form [addr-init-value]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* If argv[2] is supplied (a numeric value), use it to initialize the output buffer given to inet_net_pton(), so that we can see
        that inet_net_pton() initializes only those bytes needed for the network number. If argv[2] is not supplied, then initialize
        the buffer to zero (as is recommended practice). */

  addr.s_addr = (argc > 2) ? strtod(argv[2], NULL) : 0;

  /* Convert presentation network number in argv[1] to binary */

  bits = inet_net_pton(AF_INET, argv[1], &addr, sizeof(addr));
  if (bits == -1)
    errExit("inet_net_ntop");

  printf("inet_net_pton() returned: %d\n", bits);

  /* Convert binary format back to presentation, using 'bits'        returned by inet_net_pton() */

  if (inet_net_ntop(AF_INET, &addr, bits, buf, sizeof(buf)) == NULL)
    errExit("inet_net_ntop");

  printf("inet_net_ntop() yielded:  %s\n", buf);

  /* Display 'addr' in raw form (in network byte order), so we can  see bytes not displayed by inet_net_ntop(); some of those bytes
        may not have been touched by inet_net_ntop(), and so will still have any initial value that was specified in argv[2]. */

  printf("Raw address:              %x\n", htonl(addr.s_addr));

  exit(EXIT_SUCCESS);
}