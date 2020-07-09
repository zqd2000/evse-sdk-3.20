# <a name="目录">目录</a>
+ [OTA固件下载相关HAL接口详解](#OTA固件下载相关HAL接口详解)
    * [HAL_Firmware_Persistence_Start](#HAL_Firmware_Persistence_Start)
    * [HAL_Firmware_Persistence_Stop](#HAL_Firmware_Persistence_Stop)
    * [HAL_Firmware_Persistence_Write](#HAL_Firmware_Persistence_Write)

# <a name="OTA固件下载相关HAL接口详解">OTA固件下载相关HAL接口详解</a>

## <a name="HAL_Firmware_Persistence_Start">HAL_Firmware_Persistence_Start</a>

原型
---
```
void HAL_Firmware_Persistence_Start(void);
```

接口说明
---
固件持久化功能开始

参数说明
---
void

返回值说明
---
void

-----

## <a name="HAL_Firmware_Persistence_Stop">HAL_Firmware_Persistence_Stop</a>

原型
---
```
int HAL_Firmware_Persistence_Stop(void);
```

接口说明
---
固件持久化功能结束

参数说明
---
void

返回值说明
---
void

-----

## <a name="HAL_Firmware_Persistence_Write">HAL_Firmware_Persistence_Write</a>

原型
---
```
int HAL_Firmware_Persistence_Write(_IN_ char *buffer, _IN_ uint32_t length);
```

接口说明
---
固件持久化写入固件

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-------------------------
| buffer  | char *      | 输入    | 指向写入缓冲区的指针
| length  | uint32_t    | 输入    | 写入的字节长度

返回值说明
---
实际写入的字节长度

-----

