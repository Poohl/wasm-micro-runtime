
#include "rodos.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

#include "platform_common.h"
#include "platform_internal.h"

int bh_platform_init(void) {
	return 0;
}

#define NOT_IMPLEMENTED \
	PRINTF("FUCK, NOT IMPLEMENTED\n"); \
	*((int*) NULL);

void bh_platform_destroy(void) {}

int* __errno() {
	return 0;
}

/**
 ******** memory allocator APIs **********
 */

void *
os_malloc(unsigned size) {
	PRINTF("Malloc (%u)\n", size);
	return malloc(size);
}

void *
os_realloc(void *ptr, unsigned size) {
	PRINTF("realloc (%u)\n", size);
	return realloc(ptr, size);
}

void
os_free(void *ptr) {
	PRINTF("free (%u)\n", ptr);
	free(ptr);
}

/**
 * Note: the above APIs can simply return NULL if wasm runtime
 *       isn't initialized with Alloc_With_System_Allocator.
 *       Refer to wasm_runtime_full_init().
 */

int os_printf(const char *format, ...) {
	va_list args;
	va_start( args, format );
	int o = os_vprintf(format, args);
	va_end(args);
	return o;
}

int
os_vprintf(const char *format, va_list ap) {
	return vprintf(format, ap);
}

/**
 * Get microseconds after boot.
 */
uint64
os_time_get_boot_microsecond(void) {
	return NOW() / 1000;
}

korp_tid os_self_thread(void) {
	return 0;
}

/**
 * Get current thread's stack boundary address, used for runtime
 * to check the native stack overflow. Return NULL if it is not
 * easy to implement, but may have potential issue.
 */
uint8 *
os_thread_get_stack_boundary(void) {
	return (uint8*) (RUNNER()->getStackLimitAddr());
}

/**
 * Set whether the MAP_JIT region write protection is enabled for this thread.
 * Pass true to make the region executable, false to make it writable.
 */
void
os_thread_jit_write_protect_np(bool enabled);

/**
 ************** mutext APIs ***********
 *  vmcore:  Not required until pthread is supported by runtime
 *  app-mgr: Must be implemented
 */

int
os_mutex_init(korp_mutex *mutex) {
	PRINTF("NOT IMPLEMENTED: os_mutex_init()\n");
	*mutex = 0;
	return 0;
}

int
os_mutex_destroy(korp_mutex *mutex) {
	PRINTF("NOT IMPLEMENTED: os_mutex_destroy()\n");
	*mutex = 1;
	return 0;
}

int
os_mutex_lock(korp_mutex *mutex) {
	if (*mutex != 0)
		PRINTF("FATAL: Deadlock, locking locked mutex\n");
	*mutex = 1;
	return 0;
}

int
os_mutex_unlock(korp_mutex *mutex) {
	if (*mutex != 1)
		PRINTF("FATAL: Deadlock, unlocking unlocked mutex\n");
	*mutex = 0;
	return 0;
}

int
os_cond_init(korp_cond *cond) {
	PRINTF("NOT IMPLEMENTED: os_cond_init()\n");
	return 0;
}

int
os_cond_destroy(korp_cond *cond) {
	PRINTF("NOT IMPLEMENTED: os_cond_destroy()\n");
	return 0;
}

int
os_dumps_proc_mem_info(char *out, unsigned int size)
{
    return -1;
}


/**************************************************
 *                    Section 2                   *
 *            APIs required by WAMR AOT           *
 **************************************************/

#if (WASM_MEM_DUAL_BUS_MIRROR != 0)
void *
os_get_dbus_mirror(void *ibus);
#endif

/**
 * Flush cpu data cache, in some CPUs, after applying relocation to the
 * AOT code, the code may haven't been written back to the cpu data cache,
 * which may cause unexpected behaviour when executing the AOT code.
 * Implement this function if required, or just leave it empty.
 */
void
os_dcache_flush(void){}

/**
 * Flush instruction cache.
 */
void
os_icache_flush(void *start, size_t len){}

#ifdef __cplusplus
}
#endif

