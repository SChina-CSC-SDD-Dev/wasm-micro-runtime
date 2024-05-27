#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdint.h>

struct iovec {
    void *iov_base;
    size_t iov_len;
};

ssize_t
readv(int fd, const struct iovec *iov, int iovcnt)
{
    ssize_t ntotal;
    ssize_t nread;
    size_t remaining;
    uint8_t *buffer;
    int i;

  /* Process each entry in the struct iovec array */

  for (i = 0, ntotal = 0; i < iovcnt; i++)
    {
      /* Ignore zero-length reads */

      if (iov[i].iov_len > 0)
        {
          buffer    = iov[i].iov_base;
          remaining = iov[i].iov_len;

          /* Read repeatedly as necessary to fill buffer */

          do
            {
              /* NOTE:  read() is a cancellation point */

              nread = read(fd, buffer, remaining);

              /* Check for a read error */

              if (nread < 0)
                {
                  return nread;
                }

              /* Check for an end-of-file condition */

              else if (nread == 0)
                {
                  return ntotal;
                }

              /* Update pointers and counts in order to handle partial
               * buffer reads.
               */

              buffer    += nread;
              remaining -= nread;
              ntotal    += nread;
            }
          while (remaining > 0);
        }
    }

  return ntotal;
}

ssize_t
writev(int fd, const struct iovec *iov, int iovcnt)
{
    uint16_t i, num;

    num = 0;
    for(i = 0; i < iovcnt; i ++) {
        write(fd, iov[i].iov_base, iov[i].iov_len);
        num += iov[i].iov_len;
    }
    return num;
}