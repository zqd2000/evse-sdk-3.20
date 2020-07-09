# <a name="目录">目录</a>
+ [OTA下载API详解](#OTA下载API详解)
    * [IOT_OTA_Init](#IOT_OTA_Init)
    * [IOT_OTA_Deinit](#IOT_OTA_Deinit)
    * [IOT_OTA_ReportVersion](#IOT_OTA_ReportVersion)
    * [IOT_OTA_ReportProgress](#IOT_OTA_ReportProgress)
    * [IOT_OTA_IsFetching](#IOT_OTA_IsFetching)
    * [IOT_OTA_IsFetchFinish](#IOT_OTA_IsFetchFinish)
    * [IOT_OTA_FetchYield](#IOT_OTA_FetchYield)
    * [IOT_OTA_Ioctl](#IOT_OTA_Ioctl)
    * [IOT_OTA_GetLastError](#IOT_OTA_GetLastError)

# <a name="OTA下载API详解">OTA下载API详解</a>
## <a name="IOT_OTA_Init">IOT_OTA_Init</a>

原型
---
```
void *IOT_OTA_Init(const char *product_key, const char *device_name, void *ch_signal);
```

接口说明
---
初始化OTA模块, 需要先建立与云端的MQTT连接后才能使用

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| product_key     | const char *    | 输入    | 设备三元组中的Product Key
| device_name     | const char *    | 输入    | 设备三元组中的Device Name
| ch_signal       | void *          | 输入    | MQTT句柄

返回值说明
---
| 值      | 说明
|---------|-------------
| NULL    | 失败
| 非NULL  | OTA句柄

-----

## <a name="IOT_OTA_Deinit">IOT_OTA_Deinit</a>

原型
---
```
int IOT_OTA_Deinit(void *handle)
```

接口说明
---
反初始化OTA模块, 释放所有资源

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_OTA_ReportVersion">IOT_OTA_ReportVersion</a>

原型
---
```
int IOT_OTA_ReportVersion(void *handle, const char *version);
```

接口说明
---
向云端上报当前SDK版本号

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------
| handle      | void *          | 输入    | OTA句柄
| version     | const char *    | 输入    | 版本号

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_OTA_ReportProgress">IOT_OTA_ReportProgress</a>

原型
---
```
int IOT_OTA_ReportProgress(void *handle, IOT_OTA_Progress_t progress, const char *msg);
```

接口说明
---
向云端上报升级进度

参数说明
---

| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|---------------------------------
| handle      | void *              | 输入    | OTA句柄
| progress    | IOT_OTA_Progress_t  | 输入    | 当前升级进度
| msg         | const char *        | 输入    | 升级状态的描述信息, 可以为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOT_OTAP_BURN_FAILED = -4,
    IOT_OTAP_CHECK_FALIED = -3,
    IOT_OTAP_FETCH_FAILED = -2,
    IOT_OTAP_GENERAL_FAILED = -1,
    IOT_OTAP_FETCH_PERCENTAGE_MIN = 0,
    IOT_OTAP_FETCH_PERCENTAGE_MAX = 100
} IOT_OTA_Progress_t;
```
+ `IOT_OTAP_BURN_FAILED`: 固件烧写失败
+ `IOT_OTAP_CHECK_FALIED`: 固件校验失败
+ `IOT_OTAP_FETCH_FAILED`: 固件下载失败
+ `IOT_OTAP_GENERAL_FAILED`: OTA其他错误
+ `IOT_OTAP_FETCH_PERCENTAGE_MIN`: 固件OTA进度最小值, 值为0
+ `IOT_OTAP_FETCH_PERCENTAGE_MAX`: 固件OTA进度最大值, 值为100
+ 升级进度取值范围为: [0,100]区间的整数

-----

## <a name="IOT_OTA_IsFetching">IOT_OTA_IsFetching</a>

原型
---
```
int IOT_OTA_IsFetching(void *handle);
```

接口说明
---
检测当前OTA模块是否处于从云端获取数据的状态

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值  | 说明
|-----|---------------------
| 0   | 未处于获取数据状态
| 1   | 正在从云端获取数据

-----

## <a name="IOT_OTA_IsFetchFinish">IOT_OTA_IsFetchFinish</a>

原型
---
```
int IOT_OTA_IsFetchFinish(void *handle);
```

接口说明
---
检测当前OTA模块是否获取数据完成

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值  | 说明
|-----|-------------------------
| 0   | 获取数据未完成
| 1   | 已从云端获取数据完成

-----

## <a name="IOT_OTA_FetchYield">IOT_OTA_FetchYield</a>

原型
---
```
int IOT_OTA_FetchYield(void *handle, char *buf, uint32_t buf_len, uint32_t timeout_s);
```

接口说明
---
该接口用于从网络接收报文, 需要用户周期性调用

参数说明
---

| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------
| handle      | void *  | 输入    | OTA句柄
| buf         | void *  | 输入    | 用于获取配置文件的临时buffer
| buf_len     | int     | 输入    | `data_buf`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_OTA_Ioctl">IOT_OTA_Ioctl</a>

原型
---
```
int IOT_OTA_Ioctl(void *handle, IOT_OTA_CmdType_t type, void *buf, size_t buf_len);
```

接口说明
---
用于设置OTA部分参数或获取当前OTA运行状态

参数说明
---

| 参数        | 数据类型            | 方向        | 说明
|-------------|---------------------|-------------|-----------------
| handle      | void *              | 输入        | OTA句柄
| type        | IOT_OTA_CmdType_t   | 输入        | 命令类型
| buf         | void *              | 输入/输出   | 命令buffer
| buf_len     | size_t              | 输入        | `buf`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOT_OTAG_COTA_CONFIG_ID,
    IOT_OTAG_COTA_CONFIG_SIZE,
    IOT_OTAG_COTA_SIGN,
    IOT_OTAG_COTA_SIGN_METHOD,
    IOT_OTAG_COTA_URL,
    IOT_OTAG_COTA_GETTYPE,
    IOT_OTAG_OTA_TYPE,
    IOT_OTAG_FETCHED_SIZE,     /* option for get already fetched size */
    IOT_OTAG_FILE_SIZE,        /* size of file */
    IOT_OTAG_MD5SUM,           /* md5 in string format */
    IOT_OTAG_VERSION,          /* version in string format */
    IOT_OTAG_CHECK_FIRMWARE,    /* Check firmware is valid or not */
    IOT_OTAG_CHECK_CONFIG,      /* Check config file is valid or not */
    IOT_OTAG_RESET_FETCHED_SIZE  /* reset the size_fetched parameter to be 0 */
} IOT_OTA_CmdType_t;
```
+ `IOT_OTAG_COTA_CONFIG_ID`: 当前可升级配置文件ID
+ `IOT_OTAG_COTA_CONFIG_SIZE`: 当前可升级配置文件大小
+ `IOT_OTAG_COTA_SIGN`: 当前可升级配置文件签名
+ `IOT_OTAG_COTA_SIGN_METHOD`: 当前可升级配置文件计算签名的方法
+ `IOT_OTAG_COTA_URL`: 当前可升级配置文件下载地址
+ `IOT_OTAG_COTA_GETTYPE`: 当前可升级配置文件类型
+ `IOT_OTAG_OTA_TYPE`: 当前OTA类型, COTA或FOTA
+ `IOT_OTAG_FETCHED_SIZE`: 当前可升级配置文件已下载大小
+ `IOT_OTAG_FILE_SIZE`: 当前可升级固件文件大小
+ `IOT_OTAG_MD5SUM`: 当前已下载文件MD5值
+ `IOT_OTAG_VERSION`: 当前可升级固件版本号
+ `IOT_OTAG_CHECK_FIRMWARE`: 对已下载固件文件进行校验
+ `IOT_OTAG_CHECK_CONFIG`: 对已下载配置文件进行校验
+ `IOT_OTAG_RESET_FETCHED_SIZE`: 下载开始前, 将已下载的数据量大小size_fetched值清零

-----

## <a name="IOT_OTA_GetLastError">IOT_OTA_GetLastError</a>

原型
---
```
int IOT_OTA_GetLastError(void *handle);
```

接口说明
---
获取最近一次的错误码

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值      | 说明
|---------|-------------------------
| 0       | 最近一次错误码为成功
| < 0     | 最近一次错误码为失败

-----
