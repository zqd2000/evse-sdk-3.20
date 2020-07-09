# <a name="目录">目录</a>
+ [HTTP上云API详解](#HTTP上云API详解)
    * [IOT_HTTP_Init](#IOT_HTTP_Init)
    * [IOT_HTTP_DeInit](#IOT_HTTP_DeInit)
    * [IOT_HTTP_DeviceNameAuth](#IOT_HTTP_DeviceNameAuth)
    * [IOT_HTTP_SendMessage](#IOT_HTTP_SendMessage)
    * [IOT_HTTP_Disconnect](#IOT_HTTP_Disconnect)

# <a name="HTTP上云API详解">HTTP上云API详解</a>
## <a name="IOT_HTTP_Init">IOT_HTTP_Init</a>

原型
---
```
void *IOT_HTTP_Init(iotx_http_param_t *pInitParams);
```

接口说明
---
HTTP模块初始化函数, 在使用HTTP的功能之前, 需要使用该函数进行初始化

参数说明
---

| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|---------------------
| pInitParams     | iotx_http_param_t *     | 输入    | HTTP模块初始化参数

返回值说明
---
| 值      | 说明
|---------|-----------------
| NULL    | 初始化失败
| 非NULL  | HTTP Context

参数附加说明
---
```
typedef struct {
    iotx_device_info_t *device_info;
    int                 keep_alive;
    int                 timeout_ms;
} iotx_http_param_t;
```
+ `device_info`: 设备信息, 包含Product_Key/ProductSecret/DeviceName和DeviceSecret
+ `keep_alive`: 选择是否采用http的keep alive模式, 即每次与云端通信完成后是否需要断开http连接
+ `timeout_ms:`: 设置等待应答消息的超时时间

-----

## <a name="IOT_HTTP_DeInit">IOT_HTTP_DeInit</a>

原型
---
```
void IOT_HTTP_DeInit(void **handle);
```

接口说明
---
HTTP反初始化函数, 断开与云端的连接并释放所有指定Context中分配的资源

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------
| handle  | void *  | 输入    | HTTP Context

返回值说明
---
无返回值

-----

## <a name="IOT_HTTP_DeviceNameAuth">IOT_HTTP_DeviceNameAuth</a>

原型
```
int IOT_HTTP_DeviceNameAuth(void *handle);
```

接口说明
---
向云端发送设备认证请求, 认证通过后才能通过HTTP与云端正常通信

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------
| handle  | void *  | 输入    | HTTP Context

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_HTTP_SendMessage">IOT_HTTP_SendMessage</a>

原型
---
```
int IOT_HTTP_SendMessage(void *handle, iotx_http_message_param_t *msg_param);
```

接口说明
---
当HTTP连接云端后, 用于向云端发送HTTP消息

参数说明
---

| 参数        | 数据类型                        | 方向    | 说明
|-------------|---------------------------------|---------|---------------------
| handle      | void *                          | 输入    | HTTP Context
| msg_param   | iotx_http_message_param_t *     | 输入    | 待发送到云端的消息

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef struct {
    char       *topic_path;
    uint32_t   request_payload_len;
    char       *request_payload;
    uint32_t   response_payload_len;
    char       *response_payload;
    uint32_t   timeout_ms;
} iotx_http_message_param_t;
```
+ `topic_path`: 待发送消息的目标资源地址

+ `request_payload_len`: 待发送消息的长度

+ `request_payload`: 待发送消息的数据

+ `response_payload_len`: 应答消息buffer长度

+ `response_payload`: 应答消息buffer

+ `timeout_ms`: 等待应答消息的超时时间

-----

## <a name="IOT_HTTP_Disconnect">IOT_HTTP_Disconnect</a>

原型
---
```
void IOT_HTTP_Disconnect(void *handle)
```

接口说明
---
该接口用于断开指定HTTP Context的连接

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-----------------
| handle  | void *  | 输入    | HTTP Context

返回值说明
---
无返回值

-----
