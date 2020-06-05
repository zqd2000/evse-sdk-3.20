#ifndef _WRAPPERS_H_
#define _WRAPPERS_H_

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdarg.h>
#include "stdarg.h"

#define HAL_Printf printf
    /**
 *
 * 函数 HAL_GetDeviceAssetNo() 获取设备的资产码, 用于唯一标识单个设备在IOT平台的资产，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用。
 * ---
 * Interface of HAL_GetDeviceAssetNo() requires to be implemented by user of SDK, according to target device platform
 * 
 * 
 */
    /**
 * @brief get the asset No of charge-pile that have elapsed since the system was boot.
 *
 * @param [out] device_AssetNo @n the specified device_AssetNo.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetDeviceAssetNo(char device_AssetNo[]);
    /**
 *
 * 函数 HAL_SetDeviceAssetNo() 设置设备的资产码，在IOT平台注册后得到并烧写到设备中，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用。
 * ---
 * Interface of HAL_SetDeviceAssetNo() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Set charge-pile Asset NO.
 * @param [in] device Asset No @n the specified device_AssetNo.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetDeviceAssetNo(char *device_AssetNo);
    /**
 *
 * 函数 HAL_GetDeviceRegCode() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetDeviceRegCode() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile registration code.
 * @param [out] device registration code @n the specified device_RegCode.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetDeviceRegCode(char device_RegCode[]);
    /**
 *
 * 函数 HAL_SetDeviceRegCode() 获取设备的注册码, IOT平台分发用于确认设备合法性，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用。
 * ---
 * Interface of HAL_SetDeviceRegCode() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Set the charge-pile registration code.
 * @param [out] device regoistration code @n the specified device_RegCode.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetDeviceRegCode(char *device_RegCode);

    /**
 *
 * 函数 HAL_GetDeviceName() 获取设备的注册码，用于唯一标识单个设备的名字, 三元组之一,在IOT平台申请后得到并烧写到设备中，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用。
 * ---
 * Interface of HAL_GetDeviceName() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetDeviceName(char device_name[]);

    /**
 *
 * 函数 HAL_SetDeviceName() 设置设备的DeviceName, 用于唯一标识单个设备的名字, 三元组之一, 在IOT平台注册后得到并烧写到设备中
 * ---
 * Interface of HAL_SetDeviceName() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Set the charge-pile device name.
 * @param [in] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetDeviceName(char *device_name);

    /**
 *
 * 函数 HAL_GetDeviceSecret() 获取设备的DeviceSecret, 用于标识单个设备的密钥, 三元组之一, 在IOT平台注册得到并烧写到设备中.
 * ---
 * Interface of HAL_GetDeviceSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetDeviceSecret(char device_secret[]);

    /**
 *
 * 函数 HAL_SetDeviceSecret() 设置设备的DeviceSecret, 用于标识单个设备的密钥, 三元组之一, 在IOT注册得到并烧写到设备中.
 * ---
 * Interface of HAL_SetDeviceSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetDeviceSecret(char *device_secret);

    /**
 *
 * 函数 HAL_GetProductKey() 获取设备的ProductKey, 用于标识设备的品类, 三元组之一, 在IOT平台注册得到并烧写到设备中.
 * ---
 * Interface of HAL_GetProductKey() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetProductKey(char product_key[]);

    /**
 *
 * 函数 HAL_SetProductKey() 设置设备的ProductKey, 用于标识设备的品类, 三元组之一, 在IOT平台注册得到并烧写到设备中.
 * ---
 * Interface of HAL_SetProductKey() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetProductKey(char *product_key);

    /**
 *
 * 函数 HAL_GetProductSecret() 获取设备的ProductSecret, 用于标识品类的密钥, 在IOT平台注册得到并烧写到设备中, 在一型一密的场景下将会使用到此字符串，
 * 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用.
 * ---
 * Interface of HAL_GetProductSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_GetProductSecret(char product_secret[]);

    /**
 *
 * 函数 HAL_SetProductSecret() 设置设备的ProductSecret, 用于标识品类的密钥, 在IOT平台注册得到并烧写到设备中, 在一型一密的场景下将会使用到此字符串，
 * 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SetProductSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Get the charge-pile device name.
 * @param [out] device name @n the specified device_name.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    int HAL_SetProductSecret(char *product_secret);

    /**
 *
 * 函数 HAL_UTC_Get() 获取设备的UTC时间，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UTC_Get() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Retrieves the number of seconds that have elapsed since 1970.
 * @param None.
 * @return the number of seconds.
 * @see None.
 * @note None.
 */
    long HAL_UTC_Get(void);

    /**
 *
 * 函数 HAL_UTC_Set() 设置设备的UTC时间，需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UTC_Set() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    /**
 * @brief Set the number of seconds that have elapsed since 1970 to RTC.
 * @param [in] the number of seconds. @n the specified s.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_UTC_Set(long s);

    /**
 *
 * 函数 HAL_Reboot() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Reboot() requires to be implemented by user of SDK, according to target device platform
 *
 * 
 */
    void HAL_Reboot(void);

    /**
 *
 * 函数 HAL_Firmware_Persistence_Start() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Start() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Start(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Start, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    void HAL_Firmware_Persistence_Start(void);

    /**
 *
 * 函数 HAL_Firmware_Persistence_Stop() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Stop() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Stop(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Stop, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_Firmware_Persistence_Stop(void);

    /**
 *
 * 函数 HAL_Firmware_Persistence_Write() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Write() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Write(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Write, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_Firmware_Persistence_Write(char *buffer, uint32_t length);

    /**
 *
 * 函数 HAL_Free() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Free() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Free(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Free, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_Free(void *ptr);

    /**
 *
 * 函数 HAL_GetFirmwareVersion() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetFirmwareVersion() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetFirmwareVersion(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetFirmwareVersion, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
    int HAL_GetFirmwareVersion(char *version);

    /**
 *
 * 函数 HAL_Kv_Get() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Kv_Get() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Kv_Get(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Kv_Get, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_KV_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_Kv_Get(const char *key, void *val, int *buffer_len);

    /**
 *
 * 函数 HAL_Kv_Set() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Kv_Set() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Kv_Set(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Kv_Set, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_KV_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_Kv_Set(const char *key, const void *val, int len, int sync);

    /**
 *
 * 函数 HAL_Malloc() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Malloc() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Malloc(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Malloc, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
    void *HAL_Malloc(uint32_t size);

    /**
 *
 * 函数 HAL_MutexCreate() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexCreate() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexCreate(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexCreate, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
    void *HAL_MutexCreate(void);

    /**
 *
 * 函数 HAL_MutexDestroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexDestroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexDestroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexDestroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_MutexDestroy(void *mutex);

    /**
 *
 * 函数 HAL_MutexLock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexLock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexLock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexLock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_MutexLock(void *mutex);

    /**
 *
 * 函数 HAL_MutexUnlock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexUnlock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexUnlock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexUnlock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_MutexUnlock(void *mutex);

    /**
 *
 * 函数 HAL_Random() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Random() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Random(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Random, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    uint32_t HAL_Random(uint32_t region);

    /**
 *
 * 函数 HAL_SSL_Destroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Destroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Destroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Destroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int32_t HAL_SSL_Destroy(uintptr_t handle);

    /**
 *
 * 函数 HAL_SSL_Establish() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Establish() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Establish(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Establish, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    uintptr_t HAL_SSL_Establish(const char *host,
                                uint16_t port,
                                const char *ca_crt,
                                uint32_t ca_crt_len);

    /**
 *
 * 函数 HAL_SSL_Read() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Read() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Read(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Read, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_SSL_Read(uintptr_t handle, char *buf, int len, int timeout_ms);

    /**
 *
 * 函数 HAL_SSL_Write() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Write() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Write(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Write, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_SSL_Write(uintptr_t handle, const char *buf, int len, int timeout_ms);

    /**
 *
 * 函数 HAL_SleepMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SleepMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SleepMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SleepMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Sleep thread itself.
 *
 * @param [in] ms @n the time interval for which execution is to be suspended, in milliseconds.
 * @return None.
 * @see None.
 * @note None.
 */
    void HAL_SleepMs(uint32_t ms);

    /**
 *
 * 函数 HAL_Snprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Snprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Snprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Snprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
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
    int HAL_Snprintf(char *str, const int len, const char *fmt, ...);

    /**
 *
 * 函数 HAL_Srandom() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Srandom() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Srandom(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Srandom, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    void HAL_Srandom(uint32_t seed);

    /**
 *
 * 函数 HAL_UptimeMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UptimeMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_UptimeMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_UptimeMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    /**
 * @brief Retrieves the number of milliseconds that have elapsed since the system was boot.
 *
 * @return the number of milliseconds.
 * @see None.
 * @note None.
 */
    uint64_t HAL_UptimeMs(void);

    /**
 *
 * 函数 HAL_Vsnprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Vsnprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Vsnprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Vsnprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
    int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap);

#if defined(__cplusplus)
}
#endif

#endif
