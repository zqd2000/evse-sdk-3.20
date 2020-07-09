# <a name="目录">目录</a>
+ [第六章 HAL说明](#第六章 HAL说明)
    * [6.1 设备端C-SDK分层](#6.1 设备端C-SDK分层)
    * [6.2 HAL层接口列表](#6.2 HAL层接口列表)
        - [全部接口列表](#全部接口列表)
        - [基础相关](#基础相关)
        - [多线程相关](#多线程相关)
        - [MQTT和HTTP通道功能相关](#MQTT和HTTP通道功能相关)
        - [CoAP通道功能相关](#CoAP通道功能相关)
        - [本地通信功能相关](#本地通信功能相关)
        - [设备信息设置与获取相关](#设备信息设置与获取相关)
        - [OTA功能相关](#OTA功能相关)
        - [本地定时任务功能相关](#本地定时任务功能相关)
        - [WIFI配网功能相关](#WIFI配网功能相关)
    * [6.3 HAL层接口详解](#6.3 HAL层接口详解)


# <a name="第六章 HAL说明">第六章 HAL说明</a>

## <a name="6.1 设备端C-SDK分层">6.1 设备端C-SDK分层</a>

        +---------------------------+
        |                           |
        |   C-SDK Example Program   |
        |                           |
        +---------------------------+
        |                           |
        |   C-SDK Interface Layer   |
        |                           |
        |     IOT_XXX_YYY() APIs    |
        |                           |
        +---------------------------+
        |                           |
        |   C-SDK Core Implements   |
        |   : =>                    |
        |   : You SHOULD NOT Focus  |
        |   : on this unless        |
        |   : you're debugging SDK  |
        |                           |
        +---------------------------+
        |                           |
        |  Hardware Abstract Layer  |
        |                           |
        |     HAL_XXX_YYY() APIs    |
        |                           |
        |  : You MUST Implement     |
        |  : this part for your     |
        |  : target device first    |
        +---------------------------+

设备端C-SDK是分为三层的, 如上图

+ 最底层称为"硬件平台抽象层", 也简称`HAL层`, 对应上图的 `Hardware Abstract Layer`
    - 这里是抽象不同的嵌入式目标板上操作系统对我们SDK的支撑函数
    - 举例来说, 包括网络收发, TLS/DTLS通道建立和读写, 内存申请释放, 互斥量加锁解锁等
    - **注意: 在任何跨平台移植时, 实现这部分是需要完成的第一步工作**
    - **注意: 阿里的SDK里, 并不含有多平台的HAL层实现, 但我们提供了Linux桌面OS(Ubuntu16.04)上的参考实现, 移植时可以作为参考**

+ 中间层称为"SDK内核实现层", 对应上图的 `Link Kit Core Implements`
    - 这里是C-SDK的核心实现部分, 它基于HAL层接口完成了MQTT/CoAP通道等的功能封装
    - 举例来说, 包括MQTT的连接建立, 报文收发, CoAP的连接建立, 报文收发, OTA的固件状态查询, OTA的固件下载等
    - **注意: 如果HAL层实现的好, 这一层在跨平台移植时, 理想情况下不需要做任何修改**

+ 最上层称为"SDK接口声明层", 对应上图的 `Link Kit Interface Layer`
    - 这里没有实现, 只有一系列C函数的原型声明, 也就是SDK跨平台移植完成之后, 可以用于编写业务逻辑, 和阿里云服务器通信的API
    - 举例来说, 怎么去使用这些API做业务逻辑, 我们在`examples`目录提供了丰富的示例程序, 并且只要填入了设备信息, 就可以在Linux主机上运行体验

以下按照从下到上的顺序, 逐个对每个层次做更加详细的说明

V2.3.0及以前版本
---
+ 所有HAL层函数的声明都在 `include/iot_import.h` 这个头文件中列出
+ 各功能点引入的HAL层接口依赖在`include/imports/iot_import_*.h`中列出
+ 这些`include/imports`目录下的子文件, 都被`include/iot_import.h`包含
+ 这个部分的函数声明, 对应在`src/ref-impl/hal/os/ubuntu/`有提供一份`Ubuntu`桌面系统上的参考实现, 会被编译成`output/release/lib/libiot_hal.a`

## <a name="6.2 HAL层接口列表">6.2 HAL层接口列表</a>
### <a name="全部接口列表">全部接口列表</a>
以下命令可以列出所有跨平台移植时需要实现的HAL层接口

    include$ grep -ro "HAL_[_A-Za-z0-9]*(" *|awk -F':' '{ print $NF }'|awk '{ print $NF }'|sed 's!(!!g'|sort -u|awk '{ printf("%03d  %s\n", NR, $0); }'

    001  HAL_Aes128_Cbc_Decrypt
    002  HAL_Aes128_Cbc_Encrypt
    003  HAL_Aes128_Cfb_Decrypt
    004  HAL_Aes128_Cfb_Encrypt
    005  HAL_Aes128_Destroy
    006  HAL_Aes128_Init
    007  HAL_Awss_Close_Monitor
    008  HAL_Awss_Connect_Ap
    009  HAL_Awss_Get_Channelscan_Interval_Ms
    010  HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms
    011  HAL_Awss_Get_Conn_Encrypt_Type
    013  HAL_Awss_Get_Timeout_Interval_Ms
    014  HAL_Awss_Open_Monitor
    015  HAL_Awss_Switch_Channel
    016  HAL_Config_Read
    017  HAL_Config_Write
    018  HAL_DTLSSession_create
    019  HAL_DTLSSession_free
    020  HAL_DTLSSession_read
    021  HAL_DTLSSession_write
    022  HAL_Firmware_Persistence_Start
    023  HAL_Firmware_Persistence_Stop
    024  HAL_Firmware_Persistence_Write
    025  HAL_Free
    026  HAL_GetChipID
    027  HAL_GetDeviceID(在2.3.1及以后版本中不需要实现）
    028  HAL_GetDeviceName
    029  HAL_GetDeviceSecret
    030  HAL_GetFirmwareVersion
    031  HAL_GetModuleID
    032  HAL_GetPartnerID
    033  HAL_GetProductKey
    034  HAL_GetProductSecret
    035  HAL_GetTimeStr(在2.3.1及以后版本中不需要实现）
    036  HAL_Kv_Del
    037  HAL_Kv_Erase_All
    038  HAL_Kv_Get
    039  HAL_Kv_Set
    040  HAL_Malloc
    041  HAL_MutexCreate
    042  HAL_MutexDestroy
    043  HAL_MutexLock
    044  HAL_MutexUnlock
    045  HAL_Printf
    046  HAL_Random
    047  HAL_Reboot
    048  HAL_RF433_Get_Rssi_Dbm
    049  HAL_SemaphoreCreate
    050  HAL_SemaphoreDestroy
    051  HAL_SemaphorePost
    052  HAL_SemaphoreWait
    053  HAL_SetDeviceName
    054  HAL_SetDeviceSecret
    055  HAL_SetProductKey
    056  HAL_SetProductSecret
    057  HAL_SleepMs
    058  HAL_Snprintf
    059  HAL_Srandom
    060  HAL_SSL_Destroy
    061  HAL_SSL_Establish
    062  HAL_SSL_Read
    063  HAL_SSL_Write
    064  HAL_Sys_Net_Is_Ready
    065  HAL_Sys_reboot(在2.3.0及以后版本中不需要实现)
    066  HAL_TCP_Destroy
    067  HAL_TCP_Establish
    068  HAL_TCP_Read
    069  HAL_TCP_Write
    070  HAL_ThreadCreate
    071  HAL_ThreadDelete
    072  HAL_ThreadDetach
    073  HAL_Timer_Create
    074  HAL_Timer_Delete
    075  HAL_Timer_Start
    076  HAL_Timer_Stop
    077  HAL_UDP_bindtodevice
    078  HAL_UDP_close
    079  HAL_UDP_close_without_connect
    080  HAL_UDP_connect
    081  HAL_UDP_create
    082  HAL_UDP_create_without_connect
    083  HAL_UDP_joinmulticast
    084  HAL_UDP_read
    085  HAL_UDP_readTimeout
    086  HAL_UDP_recv
    087  HAL_UDP_recvfrom
    088  HAL_UDP_send
    089  HAL_UDP_sendto
    090  HAL_UDP_write
    091  HAL_UptimeMs
    092  HAL_UTC_Get
    093  HAL_UTC_Set
    094  HAL_Vsnprintf
    095  HAL_Wifi_Enable_Mgmt_Frame_Filter
    096  HAL_Wifi_Get_Ap_Info
    097  HAL_Wifi_Get_IP
    098  HAL_Wifi_Get_Mac
    099  HAL_Wifi_Get_Os_Version
    100  HAL_Wifi_Get_Rssi_Dbm
    101  HAL_Wifi_Low_Power
    102  HAL_Wifi_Scan
    103  HAL_Wifi_Send_80211_Raw_Frame

对这些函数做实现的时候, 可以参考`src/ref-impl/hal/os/ubuntu`下和`src/ref-impl/hal/os/win7`下已经写好的示例, 这些示例在`Ubuntu16.04`主机和`Win7`主机上被完善的编写和测试过

    src/ref-impl/hal$ tree -A
    .
    +-- CMakeLists.txt
    +-- iot.mk
    +-- iotx_hal_internal.h
    +-- os
    |   +-- macos
    |   |   +-- HAL_Crypt_MacOS.c
    |   |   +-- HAL_OS_MacOS.c
    |   |   +-- HAL_TCP_MacOS.c
    |   |   +-- HAL_UDP_MacOS.c
    |   +-- ubuntu
    |   |   +-- base64.c
    |   |   +-- base64.h
    |   |   +-- cJSON.c
    |   |   +-- cJSON.h
    |   |   +-- HAL_Crypt_Linux.c
    |   |   +-- HAL_OS_linux.c
    |   |   +-- HAL_TCP_linux.c
    |   |   +-- HAL_UDP_linux.c
    |   |   +-- kv.c
    |   |   +-- kv.h
    |   +-- win7
    |       +-- HAL_OS_win7.c
    |       +-- HAL_TCP_win7.c
    +-- ssl
        +-- itls
        |   +-- HAL_TLS_itls.c
        +-- mbedtls
        |   +-- HAL_DTLS_mbedtls.c
        |   +-- HAL_TLS_mbedtls.c
        +-- openssl
            +-- HAL_TLS_openssl.c

以下是这些函数的一些简要说明表格, 若需要获取更多函数的详细信息, 请访问章节[HAL层接口详解](#HAL层接口详解), 或者查阅代码中的注释

### <a name="基础相关">基础相关</a>
**以下函数为必选实现, 无论使用SDK中的什么功能, 都需要用户对接**

| 函数名                                  | 说明
|-----------------------------------------|-----------------------------------------------------------------------------
| [HAL_Malloc](#HAL_Malloc)               | 申请一片堆上内存
| [HAL_Free](#HAL_Free)                   | 释放一片堆上内存
| [HAL_SleepMs](#HAL_SleepMs)             | 睡眠函数, 使当前执行线程睡眠指定的毫秒数
| [HAL_Snprintf](#HAL_Snprintf)           | 打印函数, 向内存缓冲区格式化构建一个字符串, 参考C99标准库函数`snprintf`
| [HAL_Printf](#HAL_Printf)               | 打印函数, 用于向串口或其它标准输出打印日志或调试信息
| [HAL_Vsnprintf](#HAL_Vsnprintf)         | 字符串打印函数, 将`va_list`类型的变量, 打印到指定目标字符串
| [HAL_UptimeMs](#HAL_UptimeMs)           | 时钟函数, 获取本设备从加电以来到目前时间点已经过去的毫秒数
| [HAL_Kv_Set](#HAL_Kv_Set)               | 写入指定KV数据
| [HAL_Kv_Get](#HAL_Kv_Get)               | 读取指定KV数据
| [HAL_Kv_Del](#HAL_Kv_Del)               | 删除指定KV数据
| [HAL_Kv_Erase_All](#HAL_Kv_Erase_All)   | 擦除所有的KV数据

### <a name="多线程相关">多线程相关</a>
**以下函数为可选实现, 如果希望SDK提供的接口能够被多线程并发调用, 则需要用户对接**

| 函数名                                          | 说明
|-------------------------------------------------|---------------------------------------------------------------------
| [HAL_MutexCreate](#HAL_MutexCreate)             | 创建一个互斥量, 用于同步控制, 对于仅支持单线程应用, 可实现为空函数
| [HAL_MutexDestroy](#HAL_MutexDestroy)           | 销毁一个互斥量, 用于同步控制, 对于仅支持单线程应用, 可实现为空函数
| [HAL_MutexLock](#HAL_MutexLock)                 | 加锁一个互斥量, 用于同步控制, 对于仅支持单线程应用, 可实现为空函数
| [HAL_MutexUnlock](#HAL_MutexUnlock)             | 解锁一个互斥量, 用于同步控制, 对于仅支持单线程应用, 可实现为空函数
| [HAL_ThreadCreate](#HAL_ThreadCreate)           | 按照指定入参创建一个线程, 对于仅支持单线程应用, 可实现为空函数
| [HAL_ThreadDelete](#HAL_ThreadDelete)           | 杀死指定的线程, 对于仅支持单线程应用, 可实现为空函数
| [HAL_ThreadDetach](#HAL_ThreadDetach)           | 设置指定的线程为`Detach`状态, 对于仅支持单线程应用, 可实现为空函数
| [HAL_SemaphoreCreate](#HAL_SemaphoreCreate)     | 创建一个计数信号量, 对于仅支持单线程应用, 可实现为空函数
| [HAL_SemaphoreDestroy](#HAL_SemaphoreDestroy)   | 销毁一个计数信号量, 对于仅支持单线程应用, 可实现为空函数
| [HAL_SemaphorePost](#HAL_SemaphorePost)         | 在指定的计数信号量上做自增操作, 解除其它线程的等待, 对于仅支持单线程应用, 可实现为空函数
| [HAL_SemaphoreWait](#HAL_SemaphoreWait)         | 在指定的计数信号量上等待并做自减操作, 对于仅支持单线程应用, 可实现为空函数

### <a name="MQTT和HTTP通道功能相关">MQTT和HTTP通道功能相关</a>
**以下函数为可选实现, 如果希望SDK提供MQTT通道功能或者HTTP通道功能, 则需要用户对接**

| 函数名                                      | 说明
|---------------------------------------------|-------------------------------------------------------------------------
| [HAL_SSL_Destroy](#HAL_SSL_Destroy)         | 销毁一个TLS连接, 用于MQTT功能, HTTPS功能
| [HAL_SSL_Establish](#HAL_SSL_Establish)     | 建立一个TLS连接, 用于MQTT功能, HTTPS功能
| [HAL_SSL_Read](#HAL_SSL_Read)               | 从一个TLS连接中读数据, 用于MQTT功能, HTTPS功能
| [HAL_SSL_Write](#HAL_SSL_Write)             | 向一个TLS连接中写数据, 用于MQTT功能, HTTPS功能
| [HAL_TCP_Destroy](#HAL_TCP_Destroy)         | 销毁一个TLS连接, 用于MQTT功能, HTTPS功能
| [HAL_TCP_Establish](#HAL_TCP_Establish)     | 建立一个TCP连接, 包含了域名解析的动作和TCP连接的建立
| [HAL_TCP_Read](#HAL_TCP_Read)               | 在指定时间内, 从TCP连接读取流数据, 并返回读到的字节数
| [HAL_TCP_Write](#HAL_TCP_Write)             | 在指定时间内, 向TCP连接发送流数据, 并返回发送的字节数
| [HAL_Random](#HAL_Random)                   | 随机数函数, 接受一个无符号数作为范围, 返回0到该数值范围内的随机无符号数
| [HAL_Srandom](#HAL_Srandom)                 | 随机数播种函数, 使 [HAL_Random](#HAL_Random) 的返回值每个执行序列各不相同, 类似`srand`

### <a name="CoAP通道功能相关">CoAP通道功能相关</a>
**以下函数为可选实现, 如果希望SDK提供CoAP通道功能, 则需要用户对接**

| 函数名                                              | 说明
|-----------------------------------------------------|-----------------------------------------------------------------
| [HAL_DTLSSession_create](#HAL_DTLSSession_create)   | 初始化DTLS资源并建立一个DTLS会话, 用于CoAP功能
| [HAL_DTLSSession_free](#HAL_DTLSSession_free)       | 销毁一个DTLS会话并释放DTLS资源, 用于CoAP功能
| [HAL_DTLSSession_read](#HAL_DTLSSession_read)       | 从DTLS连接中读数据, 用于CoAP功能
| [HAL_DTLSSession_write](#HAL_DTLSSession_write)     | 向DTLS连接中写数据, 用于CoAP功能
| [HAL_Aes128_Cbc_Decrypt](#HAL_Aes128_Cbc_Decrypt)   | AES128解密, CBC模式, 用于CoAP报文加解密
| [HAL_Aes128_Cbc_Encrypt](#HAL_Aes128_Cbc_Encrypt)   | AES128加密, CBC模式, 用于CoAP报文加解密
| [HAL_Aes128_Cfb_Decrypt](#HAL_Aes128_Cfb_Decrypt)   | AES128解密, CFB模式, 用于CoAP报文加解密
| [HAL_Aes128_Cfb_Encrypt](#HAL_Aes128_Cfb_Encrypt)   | AES128加密, CFB模式, 用于CoAP报文加解密
| [HAL_Aes128_Destroy](#HAL_Aes128_Destroy)           | AES128反初始化
| [HAL_Aes128_Init](#HAL_Aes128_Init)                 | AES128初始化
| [HAL_UDP_close](#HAL_UDP_close)                     | 关闭一个UDP socket
| [HAL_UDP_create](#HAL_UDP_create)                   | 创建一个UDP socket
| [HAL_UDP_read](#HAL_UDP_read)                       | 阻塞的从一个UDP socket中读取数据包, 并返回读到的字节数
| [HAL_UDP_readTimeout](#HAL_UDP_readTimeout)         | 在指定时间内, 从一个UDP socket中读取数据包, 返回读到的字节数
| [HAL_UDP_write](#HAL_UDP_write)                     | 阻塞的向一个UDP socket中发送数据包, 并返回发送的字节数

### <a name="本地通信功能相关">本地通信功能相关</a>
**以下函数为可选实现, 如果希望SDK提供本地通信功能, 则需要用户对接**

| 函数名                                                              | 说明
|---------------------------------------------------------------------|-------------------------------------------------
| [HAL_UDP_create_without_connect](#HAL_UDP_create_without_connect)   | 创建一个本地UDP socket, 但不发起任何网络交互
| [HAL_UDP_close_without_connect](#HAL_UDP_close_without_connect)     | 销毁指定的UDP socket, 回收资源
| [HAL_UDP_joinmulticast](#HAL_UDP_joinmulticast)                     | 在指定的UDP socket上发送加入组播组的请求
| [HAL_UDP_sendto](#HAL_UDP_sendto)                                   | 在指定的UDP socket上发送指定缓冲区的指定长度, 阻塞时间不超过指定时长, 且指定长度若发送完需提前返回
| [HAL_UDP_recvfrom](#HAL_UDP_recvfrom)                               | 从指定的UDP句柄接收指定长度数据到缓冲区, 阻塞时间不超过指定时长, 且指定长度若接收完需提前返回, 源地址保存在出参中

### <a name="设备信息设置与获取相关">设备信息设置与获取相关</a>
**以下函数为必选实现, 无论使用SDK中的什么功能, 都需要用户对接**

| 函数名                                              | 说明
|-----------------------------------------------------|-----------------------------------------------------------------
| [HAL_GetChipID](#HAL_GetChipID)                     | 获取芯片ID
| [HAL_GetDeviceID](#HAL_GetDeviceID)                 | 获取设备ID  (在2.3.1及以后版本中不需要实现）
| [HAL_GetFirmwareVersion](#HAL_GetFirmwareVersion)     | 获取固件版本号, 必须实现
| [HAL_GetModuleID](#HAL_GetModuleID)                 | 获取模组ID, 用于紧密合作伙伴, 一般客户只需要在此可实现为空函数
| [HAL_GetPartnerID](#HAL_GetPartnerID)               | 获取合作伙伴ID, 用于紧密合作伙伴, 一般客户只需要在此可实现为空函数
| [HAL_GetDeviceName](#HAL_GetDeviceName)             | 获取DeviceName, 三元组获取函数之一, 必须实现
| [HAL_GetDeviceSecret](#HAL_GetDeviceSecret)         | 获取DeviceSecret, 三元组获取函数之一, 必须实现
| [HAL_GetProductKey](#HAL_GetProductKey)             | 获取ProductKey, 三元组获取函数之一, 必须实现
| [HAL_GetProductSecret](#HAL_GetProductSecret)       | 获取ProductSecret, 三元组获取函数之一, 必须实现
| [HAL_SetDeviceName](#HAL_SetDeviceName)             | 设置DeviceName, 三元组配置函数之一, 必须实现
| [HAL_SetDeviceSecret](#HAL_SetDeviceSecret)         | 设置DeviceSecret, 三元组配置函数之一, 必须实现
| [HAL_SetProductKey](#HAL_SetProductKey)             | 设置ProductKey, 三元组配置函数之一, 必须实现
| [HAL_SetProductSecret](#HAL_SetProductSecret)       | 设置ProductSecret, 三元组配置函数之一, 必须实现

### <a name="OTA功能相关">OTA功能相关</a>
**以下函数为可选实现, 如果希望SDK提供OTA功能, 则需要用户对接**

| 函数名                                                              | 说明
|---------------------------------------------------------------------|-----------------------------------------
| [HAL_Firmware_Persistence_Start](#HAL_Firmware_Persistence_Start)   | 固件持久化开始, 包含OTA功能时必须实现
| [HAL_Firmware_Persistence_Stop](#HAL_Firmware_Persistence_Stop)     | 固件持久化结束, 包含OTA功能时必须实现
| [HAL_Firmware_Persistence_Write](#HAL_Firmware_Persistence_Write)   | 固件持久化写入, 包含OTA功能时必须实现

更多OTA相关功能说明可查看[OTA服务](https://living.aliyun.com/doc#ysuxe6.html)

### <a name="本地定时任务功能相关">本地定时任务功能相关</a>
**以下函数为可选实现, 如果希望SDK提供本地定时任务例程, 则需要用户对接**

| 函数名                          | 说明
|---------------------------------|-------------------------
| [HAL_UTC_Set](#HAL_UTC_Set)     | 设置UTC时间, 单位ms
| [HAL_UTC_Get](#HAL_UTC_Get)     | 获取UTC时间, 单位ms

### <a name="WIFI配网功能相关">WIFI配网功能相关</a>
**以下函数为可选实现, 如果希望SDK提供WiFi配网功能, 则需要用户对接**

| 函数名                                                  | 说明
|---------------------------------------------------------|-------------------------------------------------------------
| HAL_Awss_Close_Monitor                                  | 设置Wi-Fi网卡离开监听(Monitor)模式, 并开始以站点(Station)模式工作
| HAL_Awss_Connect_Ap                                     | 要求Wi-Fi网卡连接指定热点(Access Point)的函数
| HAL_Awss_Get_Channelscan_Interval_Ms                    | 获取在每个信道(`channel`)上扫描的时间长度, 单位是毫秒
| HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms   | 获取配网服务(`AWSS`)超时时长到达之后, 去连接默认SSID时的超时时长, 单位是毫秒
| HAL_Awss_Get_Timeout_Interval_Ms                        | 获取配网服务(`AWSS`)的超时时间长度, 单位是毫秒
| HAL_Awss_Open_Monitor                                   | 设置Wi-Fi网卡工作在监听(Monitor)模式, 并在收到802.11帧的时候调用被传入的回调函数
| HAL_Awss_Switch_Channel                                 | 设置Wi-Fi网卡切换到指定的信道(channel)上
| HAL_Config_Read                                         | 在设备的持久化外部存储器比如Flash上, 从配置区域起始位置读取数据到指定的内存缓冲区中
| HAL_Config_Write                                        | 在设备的持久化外部存储器比如Flash上, 把指定的内存缓冲区向配置区域起始位置写入
| HAL_RF433_Get_Rssi_Dbm                                  | 获取RF433的接收信号强度(`RSSI`)
| HAL_Sys_Net_Is_Ready                                    | 检查系统网络是否可用
| HAL_Wifi_Enable_Mgmt_Frame_Filter                       | 在站点(Station)模式下使能或禁用对管理帧的过滤
| HAL_Wifi_Get_Ap_Info                                    | 获取所连接的热点(Access Point)的信息
| HAL_Wifi_Get_IP                                         | 获取Wi-Fi网口的IP地址, 点分十进制格式保存在字符串数组出参, 二进制格式则作为返回值, 并以网络字节序(大端)表达
| HAL_Wifi_Get_Mac                                        | 获取Wi-Fi网口的MAC地址, 格式应当是"XX:XX:XX:XX:XX:XX"
| HAL_Wifi_Get_Os_Version                                 | 获取Wi-Fi模块上的操作系统版本字符串
| HAL_Wifi_Get_Rssi_Dbm                                   | 获取Wi-Fi的接收信号强度(`RSSI`)
| HAL_Wifi_Low_Power                                      | 使WiFi模组进入省电模式, 并持续一段时间
| HAL_Wifi_Scan                                           | 启动一次WiFi的空中扫描, 该API是一个阻塞操作, 所有的AP列表收集完成后, 通过回调函数告知C-SDK
| HAL_Wifi_Send_80211_Raw_Frame                           | 在当前信道(channel)上以基本数据速率(1Mbps)发送裸的802.11帧(raw 802.11 frame)

## <a name="6.3 HAL层接口详解">6.3 HAL层接口详解</a>

+ [基础功能相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/Basic_Requires)
+ [多线程相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/MultiThread_Requires)
+ [MQTT上云相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/MQTT_Requires)
+ [CoAP上云相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/CoAP_Requires)
+ [OTA固件升级相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/OTA_Requires)
+ [HTTP2流式传输相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/HTTP2_Requires)
+ [WiFi配网相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/Awss_Requires)
+ [本地通信相关HAL](http://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/HAL/Alcs_Requires)
