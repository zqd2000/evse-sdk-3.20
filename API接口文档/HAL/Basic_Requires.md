# <a name="目录">目录</a>
+ [基础HAL接口详解](#基础HAL接口详解)
    * [HAL_Free](#HAL_Free)
    * [HAL_GetChipID](#HAL_GetChipID)
    * [HAL_GetDeviceID](#HAL_GetDeviceID)
    * [HAL_GetDeviceName](#HAL_GetDeviceName)
    * [HAL_GetDeviceSecret](#HAL_GetDeviceSecret)
    * [HAL_GetFirmwareVersion](#HAL_GetFirmwareVersion)
    * [HAL_GetModuleID](#HAL_GetModuleID)
    * [HAL_GetPartnerID](#HAL_GetPartnerID)
    * [HAL_GetProductKey](#HAL_GetProductKey)
    * [HAL_GetProductSecret](#HAL_GetProductSecret)
    * [HAL_GetTimeStr](#HAL_GetTimeStr)
    * [HAL_Kv_Del](#HAL_Kv_Del)
    * [HAL_Kv_Erase_All](#HAL_Kv_Erase_All)
    * [HAL_Kv_Get](#HAL_Kv_Get)
    * [HAL_Kv_Set](#HAL_Kv_Set)
    * [HAL_Malloc](#HAL_Malloc)
    * [HAL_Printf](#HAL_Printf)
    * [HAL_Random](#HAL_Random)
    * [HAL_Reboot](#HAL_Reboot)
    * [HAL_SetDeviceName](#HAL_SetDeviceName)
    * [HAL_SetDeviceSecret](#HAL_SetDeviceSecret)
    * [HAL_SetProductKey](#HAL_SetProductKey)
    * [HAL_SetProductSecret](#HAL_SetProductSecret)
    * [HAL_SleepMs](#HAL_SleepMs)
    * [HAL_Snprintf](#HAL_Snprintf)
    * [HAL_Srandom](#HAL_Srandom)
    * [HAL_Timer_Create](#HAL_Timer_Create)
    * [HAL_Timer_Delete](#HAL_Timer_Delete)
    * [HAL_Timer_Start](#HAL_Timer_Start)
    * [HAL_Timer_Stop](#HAL_Timer_Stop)
    * [HAL_UptimeMs](#HAL_UptimeMs)
    * [HAL_UTC_Get](#HAL_UTC_Get)
    * [HAL_UTC_Set](#HAL_UTC_Set)
    * [HAL_Vsnprintf](#HAL_Vsnprintf)

# <a name="基础HAL接口详解">基础HAL接口详解</a>


## <a name="HAL_Free">HAL_Free</a>

原型
---
```
void HAL_Free(_IN_ void *ptr);
```

接口说明
---
释放参数`ptr`指向的一块堆内存, 当传入的参数为NULL时不执行任何操作

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------------------
| ptr     | void *  | 输入    | 指向将要释放的堆内存的指针

返回值说明
---
void

-----

## <a name="HAL_GetChipID">HAL_GetChipID</a>
(在3.0.1及以后版本中不需要实现）
原型
---
```
char *HAL_GetChipID(_OU_ char cid_str[HAL_CID_LEN]);
```

接口说明
---
获取唯一的芯片ID字符串, 字符串长度不能超过`HAL_CID_LEN`定义的数值。

注：该HAL只需要芯片商进行适配，如果用户不是芯片商，该HAL返回空字符串即可

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-----------------------------
| cid_str     | char[]  | 输出    | 存放芯片ID的字符串缓冲区

返回值说明
---
指向字符串缓冲区的指针

-----

## <a name="HAL_GetDeviceID">HAL_GetDeviceID</a>
(在2.3.1及以后版本中不需要实现）
原型
---
```
int HAL_GetDeviceID(_OU_ char device_id[DEVICE_ID_LEN]);
```

接口说明
---
获取设备的`DeviceID`, 用于标识设备单品的ID

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------
| device_id   | char[]  | 输出    | 存放`DeviceID`的字符串缓冲区

返回值说明
---
实际获取到的`DeviceID`字符串长度

-----

## <a name="HAL_GetDeviceName">HAL_GetDeviceName</a>

原型
---
```
int HAL_GetDeviceName(_OU_ char device_name[DEVICE_NAME_LEN]);
```

接口说明
---
获取设备的`DeviceName`, 用于唯一标识单个设备的名字, 三元组之一, 在云端控制台注册得到并烧写到设备中

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|---------------------------------
| device_name     | char[]  | 输出    | 存放`DeviceName`的字符串缓冲区

返回值说明
---
实际获取到的`DeviceName`字符串长度

-----

## <a name="HAL_GetDeviceSecret">HAL_GetDeviceSecret</a>

原型
---
```
int HAL_GetDeviceSecret(_OU_ char device_secret[DEVICE_SECRET_LEN]);
```

接口说明
---
获取设备的`DeviceSecret`, 用于标识单个设备的密钥, 三元组之一, 在云端控制台注册得到并烧写到设备中

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-------------------------------------
| device_secret   | char[]  | 输出    | 存放`DeviceSecret`的字符串缓冲区

返回值说明
---
实际获取到的`DeviceSecret`字符串长度

-----

## <a name="HAL_GetFirmwareVersion">HAL_GetFirmwareVersion</a>

原型
---
```
int HAL_GetFirmwareVersion(_OU_ char version[FIRMWARE_VERSION_MAXLEN]);
```

接口说明
---
获取设备的固件版本字符串, 此固件版本号将会用于OTA升级的版本上报。如果设备不准备支持OTA，该函数返回空串即可。

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-------------------------------------
| version     | char[]  | 输出    | 存放`FirmwareVersion`的字符串缓冲区

返回值说明
---
实际获取到的`FirmwareVersion`字符串长度

-----

## <a name="HAL_GetModuleID">HAL_GetModuleID</a>
(在3.0.1+sp1及以后版本中不需要实现）
原型
---
```
int HAL_GetModuleID(_OU_ char mid_str[MID_STR_MAXLEN]);
```

接口说明
---
获取设备的`Module ID`, 仅用于紧密合作伙伴。该函数用于模组商上报模组型号，其它角色的用户返回空串即可。

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------
| mid_str     | char[]  | 输出    | 存放`Module ID`的字符串缓冲区

返回值说明
---
实际获取到的`Module ID`字符串长度

-----

## <a name="HAL_GetPartnerID">HAL_GetPartnerID</a>
(在3.0.1+sp1及以后版本中不需要实现）
原型
---
```
int HAL_GetPartnerID(_OU_ char pid_str[PID_STR_MAXLEN]);
```

接口说明
---
获取设备的`Partner ID`, 仅用于紧密合作伙伴。

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------
| pid_str     | char[]  | 输出    | 存放`Partner ID`的字符串缓冲区

返回值说明
---
实际获取到的`Partner ID`字符串长度

-----

## <a name="HAL_GetProductKey">HAL_GetProductKey</a>

原型
---
```
int HAL_GetProductKey(_OU_ char product_key[PRODUCT_KEY_LEN]);
```

接口说明
---
获取设备的`ProductKey`, 用于标识设备的品类, 三元组之一, 在云端控制台注册得到并烧写到设备中

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|---------------------------------
| product_key     | char[]  | 输出    | 存放`ProductKey`的字符串缓冲区

返回值说明
---
实际获取到的`ProductKey`字符串长度

-----

## <a name="HAL_GetProductSecret">HAL_GetProductSecret</a>

原型
---
```
int HAL_GetProductSecret(_OU_ char product_secret[DEVICE_SECRET_LEN]);
```

接口说明
---
获取设备的`ProductSecret`, 用于标识品类的密钥, 在云端控制台注册得到并烧写到设备中, 在一型一密的场景下将会使用到此字符串

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-------------------------------------
| product_secret  | char[]  | 输出    | 存放`ProductSecret`的字符串缓冲区

返回值说明
---
实际获取到的`ProductSecret`字符串长度

-----

## <a name="HAL_GetTimeStr">HAL_GetTimeStr</a>
(在2.3.1及以后版本中不需要实现）
原型
---
```
char *HAL_GetTimeStr(_OU_ char *buf, _IN_ int len);
```

接口说明
---
获取当前时间字符串

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------------------
| buf     | char *  | 输出    | 指向时间字符串缓冲区的指针
| len     | int     | 输入    | 字符串缓冲区的字节长度

返回值说明
---
指向时间字符串缓冲区的指针

-----

## <a name="HAL_Kv_Del">HAL_Kv_Del</a>

原型
---
```
int HAL_Kv_Del(const char *key);
```

接口说明
---
删除指定KV数据, 删除`key`对应的KV对数据, 可以通过擦除Flash或修改文件数据的方式实现持久化数据的删除

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------
| key         | const char *    | 输入    | 指向key字符串的指针
| buffer      | void *          | 输出    | 指向存放获取数据的指针
| buffer_len  | int *           | 输出    | 指向存放获取

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 删除成功
| -1  | 删除失败

-----

## <a name="HAL_Kv_Erase_All">HAL_Kv_Erase_All</a>

原型
---
```
int HAL_Kv_Erase_All(void);
```

接口说明
---
擦除所有的KV数据, 可以通过擦除Flash或修改文件数据的方式实现持久化数据的删除

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

## <a name="HAL_Kv_Get">HAL_Kv_Get</a>

原型
---
```
int HAL_Kv_Get(const char *key, void *buffer, int *buffer_len);
```

接口说明
---
获取KV数据, 获取`key`对应的KV对数据, 可以通过读取Flash或读取文件的方式实现持久化数据的读取

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------
| key         | const char *    | 输入    | 指向key字符串的指针
| buffer      | void *          | 输出    | 指向存放获取数据的指针
| buffer_len  | int *           | 输出    | 指向存放获取

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 获取成功
| -1  | 获取失败

-----

## <a name="HAL_Kv_Set">HAL_Kv_Set</a>

原型
---
```
int HAL_Kv_Set(const char *key, const void *val, int len, int sync);
```

接口说明
---
设置KV数据接口, 可通过写flash或写文件的方式实现数据持久化

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------
| key     | const char *    | 输入    | 指向key字符串的指针
| val     | const void *    | 输入    | 指向待设置数据的指针
| len     | int             | 输入    | 待设置数据的字节长度
| sync    | int             | 输入    | 0: 异步接口. 1: 同步接口

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 设置成功
| -1  | 设置失败

-----

## <a name="HAL_Malloc">HAL_Malloc</a>

原型
---
```
void *HAL_Malloc(_IN_ uint32_t size);
```

接口说明
---
申请一块堆内存

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------------------
| size    | uint32_t    | 输入    | 申请的堆内存大小

返回值说明
---
| 值      | 说明
|---------|-------------------------
| NULL    | 内存申请失败
| !NULL   | 指向堆内存首地址的指针

-----


## <a name="HAL_Printf">HAL_Printf</a>
(在3.0.1+sp1及以后版本中使用宏定义:#define HAL_Printf xxxprintf）
原型
---
```
void HAL_Printf(_IN_ const char *fmt, ...);
```

接口说明
---
打印函数, 用于向串口或其它标准输出打印日志或调试信息, 可参考C99的`printf()`函数实现

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------
| fmt     | const char *    | 输入    | 格式化字符串
| ...     | 可变类型        | 输入    | 可变参数列表

返回值说明
---
void

-----

## <a name="HAL_Random">HAL_Random</a>
HAL_Random
原型
---
```
uint32_t HAL_Random(_IN_ uint32_t region);
```

接口说明
---
随机数函数, 接受一个无符号数作为范围, 返回0到region范围内的一个随机数

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------------------------------
| region  | uint32_t    | 输入    | 用于指定随机数范围的无符号数

返回值说明
---
在指定范围的随机数

-----

## <a name="HAL_Reboot">HAL_Reboot</a>

原型
---
```
void HAL_Reboot(void);
```

接口说明
---
设备重启, 调用该接口能实现复位功能

参数说明
---
void

返回值说明
---
void

-----


## <a name="HAL_SetDeviceName">HAL_SetDeviceName</a>

原型
---
```
int HAL_SetDeviceName(_IN_ char *device_name);
```

接口说明
---
设置设备的`DeviceName`, 用于标识设备单品的名字, 三元组之一

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-------------------------------------
| device_name     | char *  | 输出    | 指向待传入`DeviceName`字符串的指针

返回值说明
---
待设置`DeviceName`字符串的长度

-----

## <a name="HAL_SetDeviceSecret">HAL_SetDeviceSecret</a>

原型
---
```
int HAL_SetDeviceSecret(_IN_ char *device_secret);
```

接口说明
---
设置设备的`DeviceSecret`, 用于标识设备单品的密钥, 三元组之一

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-----------------------------------------
| device_secret   | char *  | 输出    | 指向待传入`DeviceSecret`字符串的指针

返回值说明
---
待设置`DeviceSecret`字符串的长度

-----

## <a name="HAL_SetProductKey">HAL_SetProductKey</a>

原型
---
```
int HAL_SetProductKey(_IN_ char *product_key);
```

接口说明
---
设置设备的`ProductKey`, 用于标识设备的品类, 三元组之一

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-------------------------------------
| product_key     | char *  | 输入    | 指向待设置`ProductKey`字符串的指针

返回值说明
---
待设置`ProductKey`字符串的长度

-----

## <a name="HAL_SetProductSecret">HAL_SetProductSecret</a>

原型
---
```
int HAL_SetProductSecret(_IN_ char *product_secret);
```

接口说明
---
设置设备的`ProductSecret`, 用于标识品类的密钥, 在一型一密场景中会使用到此字符串

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-----------------------------------------
| product_secret  | char *  | 输出    | 指向待传入`ProductSecret`字符串的指针

返回值说明
---
待设置`ProductSecret`字符串的长度

-----


## <a name="HAL_SleepMs">HAL_SleepMs</a>

原型
---
```
void HAL_SleepMs(_IN_ uint32_t ms);
```

接口说明
---
睡眠函数, 使当前执行线程睡眠指定的毫秒数

参数说明
---
| 参数| 数据类型    | 方向    | 说明
|-----|-------------|---------|-------------------------
| ms  | uint32_t    | 输入    | 线程挂起的时间, 单位ms

返回值说明
---
void

-----

## <a name="HAL_Snprintf">HAL_Snprintf</a>

原型
---
```
int HAL_Snprintf(_OU_ char *str, _IN_ const int len, _IN_ const char *fmt, ...);
```

接口说明
---
打印函数, 向内存缓冲区格式化构建一个字符串, 参考C99标准库函数

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-------------------------
| str     | char *          | 输入    | 指向字符缓冲区的指针
| len     | int             | 输入    | 缓冲区的字符长度
| fmt     | const char *    | 输入    | 格式化字符串
| ...     |                | 输入    | 可变参数列表

返回值说明
---
实际写入缓冲区的字符串长度

-----

## <a name="HAL_Srandom">HAL_Srandom</a>

原型
---
```
void HAL_Srandom(_IN_ uint32_t seed);
```

接口说明
---
随机数播种函数, 使 [HAL_Random](#HAL_Random) 的返回值每个随机序列各不相同, 类似C标准库中的`srand`

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-----------------------------
| seed    | uint32_t    | 输入    | 用于产生新随机序列的种子

返回值说明
---
void

-----



## <a name="HAL_Timer_Create">HAL_Timer_Create</a>

原型
---
```
void *HAL_Timer_Create(const char *name, void (*func)(void *), void *user_data);
```

接口说明
---
创建指定名称的定时器, 同时注册用户回调函数和用户数据

参数说明
---
| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|---------------------
| name        | const char *            | 输入    | 定时器名称字符串
| func        | void (*func)(void *)    | 输入    | 用户回调函数
| user_data   | void *                  | 输入    | 指向用户数据的指针

返回值说明
---
| 值      | 说明
|---------|-----------------------------
| NULL    | 创建失败
| !NULL   | 创建成功, 返回定时器句柄

-----

## <a name="HAL_Timer_Delete">HAL_Timer_Delete</a>

原型
---
```
int HAL_Timer_Delete(void *timer);
```

接口说明
---
删除由`HAL_Timer_Create()`创建的定时器, 释放资源

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------------------------------------------
| timer   | void *  | 输入    | 定时器句柄, 此句柄由调用`HAL_Timer_Create()`时返回

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

## <a name="HAL_Timer_Start">HAL_Timer_Start</a>

原型
---
```
int HAL_Timer_Start(void *t, int ms);
```

接口说明
---
启动定时器

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------------------------------------------
| timer   | void *  | 输入    | 定时器句柄, 此句柄由调用`HAL_Timer_Create()`时返回
| ms      | int     | 输入    | 定时器定时时间, 单位ms

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

## <a name="HAL_Timer_Stop">HAL_Timer_Stop</a>

原型
---
```
int HAL_Timer_Stop(void *t);
```

接口说明
---
关闭定时器

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------------------------------------------
| timer   | void *  | 输入    | 定时器句柄, 此句柄由调用`HAL_Timer_Create()`时返回
|        |        |        |

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----


## <a name="HAL_UptimeMs">HAL_UptimeMs</a>

原型
---
```
uint64_t HAL_UptimeMs(void);
```

接口说明
---
获取设备从上电到当前时刻所经过的毫秒数

参数说明
---
void

返回值说明
---
设备从上电到当前时刻所经过的毫秒数

-----

## <a name="HAL_UTC_Get">HAL_UTC_Get</a>
(在3.0.1及之后版本中不需要实现)
原型
---
```
long long HAL_UTC_Get(void);
```

接口说明
---
获取UTC时间, 数值为从Epoch(1970年1月1日00:00:00 UTC)开始所经过的秒数单位

参数说明
---
void

返回值说明
---
单位为ms的UTC时间

-----

## <a name="HAL_UTC_Set">HAL_UTC_Set</a>
(在3.0.1及之后版本中不需要实现)
原型
---
```
void HAL_UTC_Set(long long ms);
```

接口说明
---
设置UTC时间, 设置参数为从Epoch(1970年1月1日00:00:00 UTC)开始所经过的秒数单位

参数说明
---
| 参数| 数据类型    | 方向    | 说明
|-----|-------------|---------|---------------------
| ms  | long long   | 输入    | 单位为ms的UTC时间

返回值说明
---
void

-----

## <a name="HAL_Vsnprintf">HAL_Vsnprintf</a>

原型
---
```
int HAL_Vsnprintf(_OU_ char *str, _IN_ const int len, _IN_ const char *fmt, _IN_ va_list ap);
```

接口说明
---
格式化输出字符串到指定buffer中, 可参考C标准库的`vsnprintf()`实现

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-----------------------------
| str     | char *      | 输出    | 用于存放写入字符串的buffer
| len     | const int   | 输入    | 允许写入的最大字符串长度
| fmt     | const char  | 输入    | 格式化字符串
| ap      | va_list     | 输入    | 可变参数列表

返回值说明
---
成功写入的字符串长

-----
