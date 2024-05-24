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

int
fstatat(int fd, const char *path, struct stat *buf, int flag)
{
    printf("fstatat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
mkdirat(int fd, const char *path, mode_t mode)
{
    printf("mkdirat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

ssize_t
readlinkat(int fd, const char *path, char *buf, size_t bufsize)
{
    printf("readlinkat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
linkat(int fd1, const char *path1, int fd2, const char *path2, int flag)
{
    printf("linkat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
renameat(int fromfd, const char *from, int tofd, const char *to)
{
    printf("renameat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
symlinkat(const char *target, int fd, const char *path)
{
    printf("symlinkat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
unlinkat(int fd, const char *path, int flag)
{
    printf("unlinkat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
utimensat(int fd, const char *path, const struct timespec ts[2], int flag)
{
    printf("utimensat defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

void *fdopendir(int fd)
{
    printf("fdopendir defined by test error !!! \n");
    errno = ENOSYS;
    return NULL;
}

char *realpath(char *path, char *resolved_path)
{
    printf(" realpath defined by test error !!! \n");
    errno = ENOSYS;
    return NULL;
}

int
futimens(int fd, const struct timespec *times)
{
    printf(" futimens defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
posix_fallocate(int __fd, off_t __offset, off_t __length)
{
    printf("posix_fallocate defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

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

ssize_t
preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    printf("preadv defined by test error !!! \n");
    errno = ENOSYS;
    return 0;
}

ssize_t
pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    printf("pwritev defined by test error !!! \n");
    errno = ENOSYS;
    return 0;
}

int
fdatasync(int fd)
{
    printf("fdatasync defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
os_rwlock_destroy(korp_rwlock *lock)
{
    printf("os_rwlock_destroy defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
os_rwlock_unlock(korp_rwlock *lock)
{
    printf("os_rwlock_unlock defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
os_rwlock_wrlock(korp_rwlock *lock)
{
    printf("os_rwlock_wrlock defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
os_rwlock_rdlock(korp_rwlock *lock)
{
    printf("os_rwlock_rdlock defined by test error !!! \n");
    errno = ENOSYS;
    return -1;
}

int
os_rwlock_init(korp_rwlock *lock)
{
    printf("os_rwlock_init defined by test error !!! \n \n");
    errno = ENOSYS;
    return 0;
}
