/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "infra_types.h"
#include "infra_defs.h"
#include "wrappers_defs.h"

/**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Free(void *ptr)
{
    free(ptr);
}

/**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
void *HAL_Malloc(uint32_t size)
{
    return malloc(size);
}

/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
    return (void *)1;
}


/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
    return;
}


/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
    return;
}


/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
    return;
}


/**
 * @brief Writes formatted data to string.
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int rc;

    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);
    return rc;
}


int HAL_GetDeviceAssetNo(char device_AssetNo[IOTX_DEVICE_ASSET_LEN])
{
    return 0;
}

int HAL_SetDeviceAssetNo(char *device_AssetNo)
{
    return 0;
}

int HAL_GetDeviceRegCode(char device_RegCode[IOTX_DEVICE_REGISTRATION_LEN])
{
    return 0;
}

int HAL_SetDeviceRegCode(char *device_RegCode)
{
    return 0;
}

int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN])
{
    return 0;
}

int HAL_SetDeviceName(char *device_name)
{
    return 0;
}

int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN])
{
    return 0;
}

int HAL_SetDeviceSecret(char *device_secret)
{
    return 0;
}

int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN])
{
    return 0;
}

int HAL_SetProductKey(char *product_key)
{
    return 0;
}

int HAL_GetProductSecret(char product_secret[IOTX_PRODUCT_SECRET_LEN])
{
    return 0;
}

int HAL_SetProductSecret(char *product_secret)
{
    return 0;
}

long HAL_UTC_Get(void)
{
    return 0;
}

int HAL_UTC_Set(long s)
{
    return 0;
}
