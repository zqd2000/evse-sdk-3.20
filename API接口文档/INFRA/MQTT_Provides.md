# <a name="目录">目录</a>
+ [MQTT上云API详解](#MQTT上云API详解)
    * [IOT_MQTT_Construct](#IOT_MQTT_Construct)
    * [IOT_MQTT_Destroy](#IOT_MQTT_Destroy)
    * [IOT_MQTT_Yield](#IOT_MQTT_Yield)
    * [IOT_MQTT_CheckStateNormal](#IOT_MQTT_CheckStateNormal)
    * [IOT_MQTT_Subscribe](#IOT_MQTT_Subscribe)
    * [IOT_MQTT_Subscribe_Sync](#IOT_MQTT_Subscribe_Sync)
    * [IOT_MQTT_Unsubscribe](#IOT_MQTT_Unsubscribe)
    * [IOT_MQTT_Publish](#IOT_MQTT_Publish)
    * [IOT_MQTT_Publish_Simple](#IOT_MQTT_Publish_Simple)

# <a name="MQTT上云API详解">MQTT上云API详解</a>

## <a name="IOT_MQTT_Construct">IOT_MQTT_Construct</a>

原型
---
```
void *IOT_MQTT_Construct(iotx_mqtt_param_t *pInitParams)
```

接口说明
---
与云端建立MQTT连接, 入参`pInitParams`为`NULL`时将会使用默认参数建连。

参数说明
---

| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|-----------------
| pInitParams     | iotx_mqtt_param_t *     | 输入     | MQTT初始化参数,填写NULL将以默认参数建连

返回值说明
---
| 值      | 说明
|---------|-------------
| NULL    | 失败
| 非NULL  | MQTT句柄

参数附加说明
---
```
typedef struct {
    uint16_t                   port;
    const char                 *host;
    const char                 *client_id;
    const char                 *username;
    const char                 *password;
    const char                 *pub_key;
    const char                 *customize_info;
    uint8_t                    clean_session;
    uint32_t                   request_timeout_ms;
    uint32_t                   keepalive_interval_ms;
    uint32_t                   write_buf_size;
    uint32_t                   read_buf_size;
    iotx_mqtt_event_handle_t    handle_event;
} iotx_mqtt_param_t, *iotx_mqtt_param_pt;
```

+ `port`: 云端服务器端口
+ `host`: 云端服务器地址
+ `client_id`: MQTT客户端ID
+ `username`: 登录MQTT服务器用户名
+ `password`: 登录MQTT服务器密码
+ `pub_key`: MQTT连接加密方式及密钥
+ `clean_session`: 选择是否使用MQTT协议的clean session特性
+ `request_timeout_ms`: MQTT消息发送的超时时间
+ `keepalive_interval_ms`: MQTT心跳超时时间
+ `write_buf_size`: MQTT消息发送buffer最大长度
+ `read_buf_size`: MQTT消息接收buffer最大长度
+ `handle_event`: 用户回调函数, 用与接收MQTT模块的事件信息
+ `customize_info`: 用户自定义上报信息，是以逗号为分隔符kv字符串，如用户的厂商信息，模组信息自定义字符串为"pid=123456,mid=abcd";

**`pInitParams`结构体的成员配置为0或NULL时将使用内部默认参数**
-----

## <a name="IOT_MQTT_Destroy">IOT_MQTT_Destroy</a>

原型
---
```
int IOT_MQTT_Destroy(void **phandle);
```

接口说明
---
销毁指定MQTT连接并释放资源

参数说明
---

| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-------------
| phandle     | void **     | 输入    | MQTT句柄,可为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_MQTT_Yield">IOT_MQTT_Yield</a>

原型
---
```
int IOT_MQTT_Yield(void *handle, int timeout_ms);
```

接口说明
---
用于接收网络报文并将消息分发到用户的回调函数中

参数说明
---

| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-------------------------
| handle      | void *  | 输入    | MQTT句柄,可为NULL
| timeout_ms  | int     | 输入    | 尝试接收报文的超时时间

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功

-----

## <a name="IOT_MQTT_CheckStateNormal">IOT_MQTT_CheckStateNormal</a>

原型
---
```
int IOT_MQTT_CheckStateNormal(void *handle);
```

接口说明
---
获取当前MQTT连接状态

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | MQTT句柄,可为NULL

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 未连接
| 1   | 已连接

-----

## <a name="IOT_MQTT_Subscribe">IOT_MQTT_Subscribe</a>

原型
---
```
int IOT_MQTT_Subscribe(void *handle,
                        const char *topic_filter,
                        iotx_mqtt_qos_t qos,
                        iotx_mqtt_event_handle_func_fpt topic_handle_func,
                        void *pcontext);
```

接口说明
---
向云端订阅指定的MQTT Topic

参数说明
---

| 参数                | 数据类型                            | 方向    | 说明
|---------------------|-------------------------------------|---------|-------------------------------------
| handle              | void *                              | 输入    | MQTT句柄,可为NULL
| topic_filter        | const char *                        | 输入    | 需要订阅的topic
| qos                 | iotx_mqtt_qos_t                     | 输入    | 采用的QoS策略
| topic_handle_func   | iotx_mqtt_event_handle_func_fpt     | 输入    | 用于接收MQTT消息的回调函数
| pcontext            | void *                              | 输入    | 用户Context, 会通过回调函数送回

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_MQTT_Subscribe_Sync">IOT_MQTT_Subscribe_Sync</a>

原型
---
```
int IOT_MQTT_Subscribe_Sync(void *handle,
                            const char *topic_filter,
                            iotx_mqtt_qos_t qos,
                            iotx_mqtt_event_handle_func_fpt topic_handle_func,
                            void *pcontext,
                            int timeout_ms);
```

接口说明
---
向云端订阅指定的MQTT Topic, 该接口为同步接口

参数说明
---

| 参数                | 数据类型                            | 方向    | 说明
|---------------------|-------------------------------------|---------|-------------------------------------
| handle              | void *                              | 输入    | MQTT句柄,可为NULL
| topic_filter        | const char *                        | 输入    | 需要订阅的topic
| qos                 | iotx_mqtt_qos_t                     | 输入    | 采用的QoS策略
| topic_handle_func   | iotx_mqtt_event_handle_func_fpt     | 输入    | 用于接收MQTT消息的回调函数
| pcontext            | void *                              | 输入    | 用户Context, 会通过回调函数送回
| timeout_ms          | int                                 | 输入    | 该同步接口的超时时间

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_MQTT_Unsubscribe">IOT_MQTT_Unsubscribe</a>

原型
---
```
int IOT_MQTT_Unsubscribe(void *handle, const char *topic_filter);
```

接口说明
---
向云端取消订阅指定的topic

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------
| handle          | void *          | 输入    | MQTT句柄,可为NULL
| topic_filter    | const char *    | 输入    | 需要取消订阅的topic

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_MQTT_Publish">IOT_MQTT_Publish</a>

原型
---
```
int IOT_MQTT_Publish(void *handle, const char *topic_name, iotx_mqtt_topic_info_pt topic_msg);
```

接口说明
---
向指定topic推送消息

参数说明
---

| 参数        | 数据类型                    | 方向    | 说明
|-------------|-----------------------------|---------|-----------------------------
| handle      | void *                      | 输入    | MQTT句柄,可为NULL
| topic_name  | const char *                | 输入    | 接收此推送消息的目标topic
| topic_msg   | iotx_mqtt_topic_info_pt     | 输入    | 需要推送的消息

返回值说明
---
| 值      | 说明
|---------|---------
| > 0     | 成功(消息是QoS1时, 返回值就是这个上报报文的MQTT消息ID, 对应协议里的`messageId`)
| 0       | 成功(消息是QoS0时)
| < 0     | 失败

-----

## <a name="IOT_MQTT_Publish_Simple">IOT_MQTT_Publish_Simple</a>

原型
---
```
int IOT_MQTT_Publish_Simple(void *handle, const char *topic_name, int qos, void *data, int len)
```

接口说明
---
向指定topic推送消息

参数说明
---

| 参数        | 数据类型                    | 方向    | 说明
|-------------|-----------------------------|---------|-----------------------------
| handle      | void *                      | 输入    | MQTT句柄,可为NULL
| topic_name  | const char *                | 输入    | 接收此推送消息的目标topic
| qos         | int                         | 输入    | 采用的QoS策略
| data        | void *                      | 输入    | 需要发送的数据
| len         | int                         | 输入    | 数据长度
返回值说明
---
| 值      | 说明
|---------|---------
| > 0     | 成功(消息是QoS1时, 返回值就是这个上报报文的MQTT消息ID, 对应协议里的`messageId`)
| 0       | 成功(消息是QoS0时)
| < 0     | 失败

-----
