#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdint.h>

korp_tid
os_self_thread(void)
{
    return rt_thread_self();
}

uint8 *
os_thread_get_stack_boundary(void)
{
    rt_thread_t tid = rt_thread_self();
    return tid->stack_addr;
}

void
os_thread_jit_write_protect_np(bool enabled)
{}

int
os_mutex_init(korp_mutex *mutex)
{
    return rt_mutex_init(mutex, "wamr0", RT_IPC_FLAG_FIFO);
}

int
os_mutex_destroy(korp_mutex *mutex)
{
    return rt_mutex_detach(mutex);
}

int
os_mutex_lock(korp_mutex *mutex)
{
    return rt_mutex_take(mutex, RT_WAITING_FOREVER);
}

int
os_mutex_unlock(korp_mutex *mutex)
{
    return rt_mutex_release(mutex);
}

/*
 * functions below was not implement
 */

int
os_cond_init(korp_cond *cond)
{
    return 0;
}

int
os_cond_destroy(korp_cond *cond)
{
    return 0;
}

int
os_cond_wait(korp_cond *cond, korp_mutex *mutex)
{
    return 0;
}