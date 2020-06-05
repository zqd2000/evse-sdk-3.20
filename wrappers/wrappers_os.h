#ifndef _WRAPPERS_OS_H_
#define _WRAPPERS_OS_H_
#include <stdarg.h>
#include "infra_types.h"
#include "infra_defs.h"

#define HAL_Printf printf

void *HAL_Malloc(uint32_t size);

void HAL_Free(void *ptr);

uint64_t HAL_UptimeMs(void);

void HAL_SleepMs(uint32_t ms);

void HAL_Srandom(uint32_t seed);

uint32_t HAL_Random(uint32_t region);

int HAL_Snprintf(char *str, const int len, const char *fmt, ...);

int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap);

void *HAL_SemaphoreCreate(void);

void HAL_SemaphoreDestroy(void *sem);

void HAL_SemaphorePost(void *sem);

int HAL_SemaphoreWait(void *sem, uint32_t timeout_ms);

int HAL_ThreadCreate(
    void **thread_handle,
    void *(*work_routine)(void *),
    void *arg,
    hal_os_thread_param_t *hal_os_thread_param,
    int *stack_used);

void *HAL_MutexCreate(void);

void HAL_MutexDestroy(void *mutex);

void HAL_MutexLock(void *mutex);

void HAL_MutexUnlock(void *mutex);

void HAL_Reboot(void);

int HAL_GetFirmwareVersion(char *version);

void HAL_Firmware_Persistence_Start(void);

int HAL_Firmware_Persistence_Write(char *buffer, uint32_t length);

int HAL_Firmware_Persistence_Stop(void);

int HAL_GetDeviceAssetNo(char device_AssetNo[IOTX_DEVICE_ASSET_LEN]);

int HAL_SetDeviceAssetNo(char *device_AssetNo);

int HAL_GetDeviceRegCode(char device_RegCode[IOTX_DEVICE_REGISTRATION_LEN]);

int HAL_SetDeviceRegCode(char *device_RegCode);

int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN]);

int HAL_SetDeviceName(char *device_name);

int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);

int HAL_SetDeviceSecret(char *device_secret);

int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN]);

int HAL_SetProductKey(char *product_key);

int HAL_GetProductSecret(char product_secret[IOTX_PRODUCT_SECRET_LEN]);

int HAL_SetProductSecret(char *product_secret);

long HAL_UTC_Get(void);

int HAL_UTC_Set(long s);

#endif
