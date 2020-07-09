# <a name="目录">目录</a>
+ [WiFi配网相关HAL接口详解](#WiFi配网相关HAL接口详解)
    * [HAL_Aes128_Cbc_Decrypt](#HAL_Aes128_Cbc_Decrypt)
    * [HAL_Aes128_Cbc_Encrypt](#HAL_Aes128_Cbc_Encrypt)
    * [HAL_Aes128_Cfb_Decrypt](#HAL_Aes128_Cfb_Decrypt)
    * [HAL_Aes128_Cfb_Encrypt](#HAL_Aes128_Cfb_Encrypt)
    * [HAL_Aes128_Destroy](#HAL_Aes128_Destroy)
    * [HAL_Aes128_Init](#HAL_Aes128_Init)
    * [HAL_Awss_Close_Monitor](#HAL_Awss_Close_Monitor)
    * [HAL_Awss_Connect_Ap](#HAL_Awss_Connect_Ap)
    * [HAL_Awss_Get_Channelscan_Interval_Ms](#HAL_Awss_Get_Channelscan_Interval_Ms)
    * [HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms](#HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms)
    * [HAL_Awss_Get_Timeout_Interval_Ms](#HAL_Awss_Get_Timeout_Interval_Ms)
    * [HAL_Awss_Open_Monitor](#HAL_Awss_Open_Monitor)
    * [HAL_Awss_Switch_Channel](#HAL_Awss_Switch_Channel)
    * [HAL_RF433_Get_Rssi_Dbm](#HAL_RF433_Get_Rssi_Dbm)
    * [HAL_Sys_Net_Is_Ready](#HAL_Sys_Net_Is_Ready)
    * [HAL_Wifi_Enable_Mgmt_Frame_Filter](#HAL_Wifi_Enable_Mgmt_Frame_Filter)
    * [HAL_Wifi_Get_Ap_Info](#HAL_Wifi_Get_Ap_Info)
    * [HAL_Wifi_Get_IP](#HAL_Wifi_Get_IP)
    * [HAL_Wifi_Get_Mac](#HAL_Wifi_Get_Mac)
    * [HAL_Wifi_Low_Power](#HAL_Wifi_Low_Power)
    * [HAL_Wifi_Scan](#HAL_Wifi_Scan)
    * [HAL_Wifi_Send_80211_Raw_Frame](#HAL_Wifi_Send_80211_Raw_Frame)
    * [HAL_Awss_Open_Ap](#HAL_Awss_Open_Ap)
    * [HAL_Awss_Close_Ap](#HAL_Awss_Close_Ap)

# <a name="WiFi配网相关HAL接口详解">WiFi配网相关HAL接口详解</a>

## <a name="HAL_Aes128_Cbc_Decrypt">HAL_Aes128_Cbc_Decrypt</a>

原型
---
```
typedef void *p_HAL_Aes128_t;

int HAL_Aes128_Cbc_Decrypt(
            _IN_ p_HAL_Aes128_t aes,
            _IN_ const void *src,
            _IN_ size_t blockNum,
            _OU_ void *dst);
```

接口说明
---
以`AES-CBC-128`的加解密模式, 用`HAL_Aes128_Init()`被调用时传入的密钥, 解密从`src`位置起长度为`blockNum`块数的密文, 并把明文结果存放到`dst`起始的内存缓冲区中

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------------------------------------------------------------------------------------------------------
| aes         | void *          | 输入    | 这是一个句柄, 是用户调用`HAL_Aes128_Init()`成功时所得到的返回值, 之后需要作为必选的入参传给所有AES加解密相关的HAL接口
| src         | const void *    | 输入    | 指定被解密的源数据的缓冲区首地址, 也就是AES密文的起始地址
| blockNum    | size_t          | 输入    | 指定被解密的源数据的缓冲区长度, 以16字节为一个Block, 此参数表达密文总长度是多少个Block, 或者说是16字节的多少倍
| dst         | void *          | 输出    | 指定被解密的目的数据的缓冲区首地址, 也就是AES解密后, 存放明文的首地址

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 解密成功
| -1  | 解密失败

-----

## <a name="HAL_Aes128_Cbc_Encrypt">HAL_Aes128_Cbc_Encrypt</a>

原型
---
```
int HAL_Aes128_Cbc_Encrypt(
            _IN_ p_HAL_Aes128_t aes,
            _IN_ const void *src,
            _IN_ size_t blockNum,
            _OU_ void *dst);
```

接口说明
---
以`AES-CBC-128`的加解密模式, 用`HAL_Aes128_Init()`被调用时传入的密钥, 加密从`src`位置起长度为`blockNum`块数的明文, 并把密文结果存放到`dst`起始的内存缓冲区中

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------------------------------------------------------------------------------------------------------
| aes         | void *          | 输入    | 这是一个句柄, 是用户调用`HAL_Aes128_Init()`成功时所得到的返回值, 之后需要作为必选的入参传给所有AES加解密相关的HAL接口
| src         | const void *    | 输入    | 指定被加密的源数据的缓冲区首地址, 也就是明文的起始地址
| blockNum    | size_t          | 输入    | 指定被加密的源数据的缓冲区长度, 以16字节为一个Block, 此参数表达明文总长度是多少个Block, 或者说是16字节的多少倍
| dst         | void *          | 输出    | 指定被加密的目的数据的缓冲区首地址, 也就是AES加密后, 存放AES密文的首地址

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 加密成功
| -1  | 加密失败

-----

## <a name="HAL_Aes128_Cfb_Decrypt">HAL_Aes128_Cfb_Decrypt</a>

原型
---
```
int HAL_Aes128_Cfb_Decrypt(
            _IN_ p_HAL_Aes128_t aes,
            _IN_ const void *src,
            _IN_ size_t length,
            _OU_ void *dst);
```

接口说明
---
CFB模式的AES128解密接口函数, 使用此接口前必须先调用`HAL_Aes128_Init()`建立AES上下文数据结构体

参数`length`为分组数量(AES128一个分组的长度为128bits, 也就是16bytes), 而非字节数

用户在实现此函数时无需考虑padding问题, 因为SDK在调用此接口前已完成padding处理

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------------------------------------------
| aes         | void *          | 输入    | 调用`HAL_Aes128_Init()`时返回的上下文结构体指针
| src         | const void *    | 输入    | 指向密文数据缓冲区的指针
| blockNum    | size_t          | 输入    | 密文数据的分组数量, AES128一个分组长度为16bytes
| dst         | void *          | 输出    | 指向密文数据缓冲区的指针

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 解密成功
| -1  | 解密失败

-----

## <a name="HAL_Aes128_Cfb_Encrypt">HAL_Aes128_Cfb_Encrypt</a>

原型
---
```
int HAL_Aes128_Cfb_Encrypt(
            _IN_ p_HAL_Aes128_t aes,
            _IN_ const void *src,
            _IN_ size_t length,
            _OU_ void *dst);
```

接口说明
---
CFB模式的AES128加密接口函数, 使用此接口前必须先调用`HAL_Aes128_Init()`建立AES上下文数据结构体

参数`length`为分组数量(AES128一个分组的长度为128bits, 也就是16bytes), 而非字节数

用户在实现此函数时无需考虑padding问题, 因为SDK在调用此接口前已完成padding处理

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------------------------------
| aes     | p_HAL_Aes128_t  | 输入    | 调用`HAL_Aes128_Init()`时返回的上下文结构体指针
| src     | const void *    | 输入    | 指向明文数据缓冲区的指针
| length  | size_t          | 输入    | 明文数据的分组数量, AES128一个分组长度为16bytes
| dst     | void *          | 输出    | 指向密文数据缓冲区的指针

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 加密成功
| -1  | 加密失败

-----

## <a name="HAL_Aes128_Destroy">HAL_Aes128_Destroy</a>

原型
---
```
int HAL_Aes128_Destroy(_IN_ p_HAL_Aes128_t aes);
```

接口说明
---
销毁AES加解密算法的上下文结构体, 释放内存资源

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-------------------------------------------------------------
| aes     | p_HAL_Aes128_t  | 输入    | 此参数应调用`HAL_Aes128_Init()`时返回的上下文结构体指针

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

## <a name="HAL_Aes128_Init">HAL_Aes128_Init</a>

原型
---
```
p_HAL_Aes128_t HAL_Aes128_Init(
            _IN_ const uint8_t *key,
            _IN_ const uint8_t *iv,
            _IN_ AES_DIR_t dir);
```

接口说明
---
初始化AES加解密算法的上下文结构体, 并根据`dir`参数完成AES算法的初始化. 用户可自定义结构体类型, 但结构体中应包含key, iv等上下文数据

参数说明
---
| 参数    | 数据类型            | 方向    | 说明
|---------|---------------------|---------|---------------------------------------------------------------------------------------------
| key     | const uint8_t *     | 输入    | AES秘钥数组首地址, 秘钥数组长度必须>=16bytes
| iv      | const uint8_t *     | 输入    | AES初始向量数组首地址, 初始向量数组的长度必须>=16bytes
| dir     | AES_DIR_t           | 输入    | 指定AES算法用途</br>HAL_AES_ENCRYPTION: 表示用于加密</br>HAL_AES_DECRYPTION: 表示用于解密
```
typedef enum {
    HAL_AES_ENCRYPTION = 0,     // 用于加密
    HAL_AES_DECRYPTION = 1,     // 用于解密
} AES_DIR_t;
```

返回值说明
---
指向所初始化的AES加解密上下文结构体的指针. `p_HAL_Aes128_t`的类型定义如下所示:
```
typedef void *p_HAL_Aes128_t;
```

-----

## <a name="HAL_Awss_Close_Monitor">HAL_Awss_Close_Monitor</a>

原型
---
```
void HAL_Awss_Close_Monitor(void);
```

接口说明
---
设置Wi-Fi网卡离开监听(Monitor)模式, 并开始以站点(Station)模式工作，并不再以Sniffer抓包

参数说明
---
void

返回值说明
---
void

-----

## <a name="HAL_Awss_Connect_Ap">HAL_Awss_Connect_Ap</a>

原型
---
```
int HAL_Awss_Connect_Ap(
            _IN_ uint32_t connection_timeout_ms,
            _IN_ char ssid[HAL_MAX_SSID_LEN],
            _IN_ char passwd[HAL_MAX_PASSWD_LEN],
            _IN_OPT_ enum AWSS_AUTH_TYPE auth,
            _IN_OPT_ enum AWSS_ENC_TYPE encry,
            _IN_OPT_ uint8_t bssid[ETH_ALEN],
            _IN_OPT_ uint8_t channel);

```

接口说明
---
要求Wi-Fi网卡连接指定热点(Access Point)的函数，bssid指定特定AP，另外bssid也可能为空或无效值（全0或全0xff）

参数说明
---
| 参数                    | 数据类型    | 方向    | 说明
|-------------------------|-------------|---------|---------------------------------------------
| connection_timeout_ms   | uint32_t    | 输入    | 连接AP的超时时间
| ssid                    | char        | 输入    | 目的AP的SSID
| passwd                  | char        | 输入    | 目的AP的PASSWORD
| auth                    | enum        | 输入    | 目的AP的加密方式, HAL可以忽略
| encry                   | enum        | 输入    | 目的AP的认证方式, HAL可以忽略
| bssid                   | uint8_t     | 输入    | 目的AP的BSSID, 该字段可能为NULL或设置为全0
| channel                 | uint8_t     | 输入    | 目的AP的信道, 该字段可以忽略

返回值说明
---
| 值      | 说明
|---------|-----------------------------------------------------
| `0`     | 连接AP和DHCP成功
| `-1`    | 连接AP和DHCP失败
| `-2`    | 连接指定的SSID超过可容忍的时长仍未成功, 返回失败
| `-3`    | 连接AP时明确被告知身份认证失败
| `-4`    | 连接指定的SSID成功, 但未能成功获取到IP地址
| `-5`    | 无法发现SSID参数所指定的热点

-----

## <a name="HAL_Awss_Get_Channelscan_Interval_Ms">HAL_Awss_Get_Channelscan_Interval_Ms</a>

原型
---
```
int HAL_Awss_Get_Channelscan_Interval_Ms(void);
```

接口说明
---
获取在每个信道(`channel`)上扫描的时间长度, 单位是毫秒，建议200ms~400ms,默认250ms

参数说明
---
void

返回值说明
---
时间长度, 单位是毫秒

-----

## <a name="HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms">HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms</a>

原型
---
```
int HAL_Awss_Get_Connect_Default_Ssid_Timeout_Interval_Ms(void);
```

接口说明
---
获取配网服务(`AWSS`)超时时长到达之后, 去连接默认SSID时的超时时长, 单位是毫秒（该接口已经废弃，不再使用，不用对接）

参数说明
---
void

返回值说明
---
时时长, 单位是毫秒

-----

## <a name="HAL_Awss_Get_Timeout_Interval_Ms">HAL_Awss_Get_Timeout_Interval_Ms</a>

原型
---
```
int HAL_Awss_Get_Timeout_Interval_Ms(void);
```

接口说明
---
获取配网服务(`AWSS`)的超时时间长度, 单位是毫秒，建议60s或60000ms

参数说明
---
void

返回值说明
---
超时时长, 单位是毫秒

-----

## <a name="HAL_Awss_Open_Monitor">HAL_Awss_Open_Monitor</a>

原型
---
```
void HAL_Awss_Open_Monitor(_IN_ awss_recv_80211_frame_cb_t cb);
```

接口说明
---
设置Wi-Fi网卡工作在监听(Monitor)模式, 并在收到802.11帧的时候调用被传入的回调函数

参数说明
---
| 参数    | 数据类型                    | 方向    | 说明
|---------|-----------------------------|---------|---------------------------------------------
| cb      | awss_recv_80211_frame_cb_t  | 输入    | 回调函数指针, 当WiFi接收到帧时会调用此函数

```
/**
 * @brief   802.11帧的处理函数, 可以将802.11 Frame传递给这个函数
 *
 * @param[in] buf @n 80211 frame buffer, or pointer to struct ht40_ctrl
 * @param[in] length @n 80211 frame buffer length
 * @param[in] link_type @n AWSS_LINK_TYPE_NONE for most rtos HAL,
 *              and for linux HAL, do the following step to check
 *              which header type the driver supported.
 * @param[in] with_fcs @n 80211 frame buffer include fcs(4 byte) or not
 * @param[in] rssi @n rssi of packet, range of `[-127, -1]`
 */
typedef int (*awss_recv_80211_frame_cb_t)(char *buf, int length,
        enum AWSS_LINK_TYPE link_type, int with_fcs, signed char rssi);
```

返回值说明
---
void

-----

## <a name="HAL_Awss_Switch_Channel">HAL_Awss_Switch_Channel</a>

原型
---
```
void HAL_Awss_Switch_Channel(
            _IN_ char primary_channel,
            _IN_OPT_ char secondary_channel,
            _IN_OPT_ uint8_t bssid[ETH_ALEN]);
```

接口说明
---
设置Wi-Fi网卡切换到指定的信道(channel)上

参数说明
---
| 参数                | 数据类型    | 方向    | 说明
|---------------------|-------------|---------|-------------------------------------------------------------------------
| primary_channel     | char        | 输入    | 首选信道
| secondary_channel   | char        | 输入    | 辅助信道(信道带宽为40MHz时才会使用, 信道宽度为20MHz是可以忽略该参数)
| bssid               | uint8_t     | 输入    | 次参数已废弃, 可以忽略

返回值说明
---
void

-----


## <a name="HAL_RF433_Get_Rssi_Dbm">HAL_RF433_Get_Rssi_Dbm</a>

原型
---
```
int HAL_RF433_Get_Rssi_Dbm(void);
```

接口说明
---
获取RF433的接收信号强度(`RSSI`)(该API已经废弃，不再使用，不用对接)

参数说明
---
void

返回值说明
---
信号强度数值, 单位是dBm

-----


## <a name="HAL_Sys_Net_Is_Ready">HAL_Sys_Net_Is_Ready</a>

原型
---
```
int HAL_Sys_Net_Is_Ready(void);
```

接口说明
---
检查系统网络是否可用（设备是否已经成功获得IP地址并且当前IP地址可用）

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 网络不可用
| 1   | 网络可用

-----


## <a name="HAL_Wifi_Enable_Mgmt_Frame_Filter">HAL_Wifi_Enable_Mgmt_Frame_Filter</a>

原型
---
```
int HAL_Wifi_Enable_Mgmt_Frame_Filter(
            _IN_ uint32_t filter_mask,
            _IN_OPT_ uint8_t vendor_oui[3],
            _IN_ awss_wifi_mgmt_frame_cb_t callback);
```

接口说明
---
 在站点(Station)模式下使能或禁用对特定管理帧的过滤（只接受包含特定OUI的管理帧）

参数说明
---
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|-----------------------------------------------------------------------------
| filter_mask     | uint32_t                    | 输入    | 帧过滤参数
| vendor_oui      | uint8_t                     | 输入    | WiFi联盟分配的厂商OUI, 如果OUI为NULL, 表示不对OUI过滤, 反之要根据OUI过滤
| callback        | awss_wifi_mgmt_frame_cb_t   | 输入    | 用于接收802.11帧或者信息元素(IE)的回调函数

返回值说明
---
| 值      | 说明
|---------|-------------
| = 0     | 发送成功
| = -1    | 发送失败
| = -2    | 不支持

-----

## <a name="HAL_Wifi_Get_Ap_Info">HAL_Wifi_Get_Ap_Info</a>

原型
---
```
int HAL_Wifi_Get_Ap_Info(
            _OU_ char ssid[HAL_MAX_SSID_LEN],
            _OU_ char passwd[HAL_MAX_PASSWD_LEN],
            _OU_ uint8_t bssid[ETH_ALEN]);
```

接口说明
---
获取所连接的热点(Access Point)的信息

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------------------------------------------------------------------
| ssid    | char        | 输出    | AP的SSID, 该参数可能为NULL
| passwd  | char        | 输出    | AP的Password, 该参数为NULL
| bssid   | uint8_t     | 输出    | AP的BSSID, 该参数可能为NULL，如果bssid不对将导致零配设备发现失败

返回值说明
---
| 值      | 说明
|---------|-------------
| = 0     | 操作成功
| = -1    | 操作失败

-----

## <a name="HAL_Wifi_Get_IP">HAL_Wifi_Get_IP</a>

原型
---
```
uint32_t HAL_Wifi_Get_IP(_OU_ char ip_str[HAL_IP_LEN], _IN_ const char *ifname);
```

接口说明
---
获取Wi-Fi网口的IP地址, 点分十进制格式保存在字符串数组出参, 二进制格式则作为返回值, 并以网络字节序(大端)表达

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|---------------------------------------------------------------------------------
| ip_str  | char[]          | 输出    | 存放点分十进制格式的IP地址字符串的数组
| ifname  | const char*     | 输入    | 指定Wi-Fi网络接口的名字（如果只有一个网口，可以忽略此参数，该参数可能为NULL）

返回值说明
---
二进制形式的IP地址, 以网络字节序(大端)组织

-----

## <a name="HAL_Wifi_Get_Mac">HAL_Wifi_Get_Mac</a>

原型
---
```
char *HAL_Wifi_Get_Mac(_OU_ char mac_str[HAL_MAC_LEN]);
```

接口说明
---
获取Wi-Fi网口的MAC地址, 格式应当是"XX:XX:XX:XX:XX:XX"

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-------------------------------------
| mac_str     | char        | 输出    | 指向缓冲区数组起始位置的字符指针

返回值说明
---
指向缓冲区数组起始位置的字符指针

-----

## <a name="HAL_Wifi_Low_Power">HAL_Wifi_Low_Power</a>

原型
---
```
int HAL_Wifi_Low_Power(_IN_ int timeout_ms);
```

接口说明
---
使WiFi模组进入省电模式, 并持续一段时间（该API未用，可以暂时不用对接）

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------------------------------
| timeout_ms  | int         | 输入    | 指定在多长时间内, WiFi模组都处于省电模式, 单位是毫秒

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 设置成功
| -1  | 设置失败

-----

## <a name="HAL_Wifi_Scan">HAL_Wifi_Scan</a>

原型
---
```
int HAL_Wifi_Scan(awss_wifi_scan_result_cb_t cb);
```

接口说明
---
启动一次WiFi的空中扫描, 该API是一个阻塞操作, 扫描没有完成不能结束. 所有的AP列表收集完成后, 一个一个通过回调函数告知AWSS，最好不要限制AP的数量，否则可能导致中文GBK编码的SSID热点配网失败

参数说明
---
| 参数    | 数据类型                    | 方向    | 说明
|---------|-----------------------------|---------|---------------------
| cb      | awss_wifi_scan_result_cb_t  | 输入    | 扫描通知回调函数

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 扫描正常结束
| -1  | 其他情况

-----

## <a name="HAL_Wifi_Send_80211_Raw_Frame">HAL_Wifi_Send_80211_Raw_Frame</a>

原型
---
```
int HAL_Wifi_Send_80211_Raw_Frame(_IN_ enum HAL_Awss_Frame_Type type,
                                  _IN_ uint8_t *buffer, _IN_ int len);

```

接口说明
---
在当前信道(channel)上以基本数据速率(1Mbps)发送裸的802.11帧(raw 802.11 frame)

参数说明
---
| 参数    | 数据类型                    | 方向    | 说明
|---------|-----------------------------|---------|---------------------------------------------------------------------------------
| type    | enum HAL_Awss_Frame_Type    | 输入    | 查看`HAL_Awss_Frame_Type_t`定义, 目前只支持`FRAME_BEACON`和`FRAME_PROBE_REQ`
| buffer  | uint8_t *                   | 输入    | 80211裸数据帧, 包括完整的MAC头和FCS域
| len     | int                         | 输入    | 80211裸帧字节长度

```
/* 80211帧类型定义 */
typedef enum HAL_Awss_Frame_Type {
    FRAME_ACTION,
    FRAME_BEACON,
    FRAME_PROBE_REQ,
    FRAME_PROBE_RESPONSE,
    FRAME_DATA
} HAL_Awss_Frame_Type_t;
```

返回值说明
---
| 值      | 说明
|---------|-------------
| = 0     | 发送成功
| = -1    | 发送失败

-----

## <a name="HAL_Awss_Open_Ap">HAL_Awss_Open_Ap</a>

原型
---
```
int HAL_Awss_Open_Ap(const char *ssid, const char *passwd, int beacon_interval, int hide);
```

接口说明
---
开启设备热点（SoftAP模式）

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|---------------------|-----------------|---------|-------------------------------------
| ssid            | const char *    | 输入    | 热点的ssid字符
| passwd          | const char *    | 输入    | 热点的passwd字符
| beacon_interval | int             | 输入    | 热点的Beacon广播周期（广播间隔）
| hide                | int             | 输入    | 0, 非隐藏, 其它值：隐藏；
返回值说明
---
| 值  | 说明
|-----|-------------------------------------
| 0   | success
| -1  | unsupported
| -2  | failure with system error
| -3  | failure with no memory
| -4  | failure with invalid parameters
-----

## <a name="HAL_Awss_Close_Ap">HAL_Awss_Close_Ap</a>

原型
---
```
int HAL_Awss_Close_Ap(void);
```

接口说明
---
关闭设备热点

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | success
| -1  | unsupported
| -2  | failure
-----
