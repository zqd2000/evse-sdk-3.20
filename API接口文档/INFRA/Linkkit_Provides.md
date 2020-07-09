# <a name="目录">目录</a>
+ [Alink协议API详解](#Alink协议API详解)
    * [IOT_Linkkit_Open](#IOT_Linkkit_Open)
    * [IOT_Linkkit_Connect](#IOT_Linkkit_Connect)
    * [IOT_Linkkit_Yield](#IOT_Linkkit_Yield)
    * [IOT_Linkkit_Close](#IOT_Linkkit_Close)
    * [IOT_Linkkit_TriggerEvent](#IOT_Linkkit_TriggerEvent)
    * [IOT_Linkkit_Report](#IOT_Linkkit_Report)
    * [IOT_Linkkit_Query](#IOT_Linkkit_Query)
    * [IOT_RegisterCallback](#IOT_RegisterCallback)
    * [IOT_Ioctl](#IOT_Ioctl)
+ [Event列表详解](#Event列表详解)
    * [ITE_CONNECT_SUCC](#ITE_CONNECT_SUCC)
    * [ITE_DISCONNECTED](#ITE_DISCONNECTED)
    * [ITE_RAWDATA_ARRIVED](#ITE_RAWDATA_ARRIVED)
    * [ITE_SERVICE_REQUEST](#ITE_SERVICE_REQUEST)
    * [ITE_PROPERTY_SET](#ITE_PROPERTY_SET)
    * [ITE_PROPERTY_GET](#ITE_PROPERTY_GET)
    * [ITE_REPORT_REPLY](#ITE_REPORT_REPLY)
    * [ITE_TRIGGER_EVENT_REPLY](#ITE_TRIGGER_EVENT_REPLY)
    * [ITE_TIMESTAMP_REPLY](#ITE_TIMESTAMP_REPLY)
    * [ITE_TOPOLIST_REPLY](#ITE_TOPOLIST_REPLY)
    * [ITE_PERMIT_JOIN](#ITE_PERMIT_JOIN)
    * [ITE_INITIALIZE_COMPLETED](#ITE_INITIALIZE_COMPLETED)
    * [ITE_FOTA](#ITE_FOTA)
    * [ITE_COTA](#ITE_COTA)

# <a name="Alink协议API详解">Alink协议API详解</a>
> 补充说明: JSON报文中, 消息id取值范围`0~4294967295`, id是String类型的数字，如"12345"

## <a name="IOT_Linkkit_Open">IOT_Linkkit_Open</a>

原型
---
```
int IOT_Linkkit_Open(iotx_linkkit_dev_type_t dev_type, iotx_linkkit_dev_meta_info_t *meta_info);
```

接口说明
---
初始化设备资源, 在对设备进行操作之前, 必须先调用此接口. 该接口调用成功的情况下会返回设备ID, 当使用其他接口时需要以设备ID为入参, 对指定的设备进行操作

参数说明
---

| 参数        | 数据类型                        | 方向    | 说明
|-------------|---------------------------------|---------|-------------------------
| dev_type    | iotx_linkkit_dev_type_t         | 输入    | 需要创建资源的设备类型
| meta_info   | iotx_linkkit_dev_meta_info_t    | 输入    | 设备的四元组信息

返回值说明
---
| 值      | 说明
|---------|-----------------
| >= 0    | 创建设备成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOTX_LINKKIT_DEV_TYPE_MASTER,
    IOTX_LINKKIT_DEV_TYPE_SLAVE,
    IOTX_LINKKIT_DEV_TYPE_MAX
} iotx_linkkit_dev_type_t;
```

+ IOTX_LINKKIT_DEV_TYPE_MASTER: 创建的设备为主设备, 仅能创建一次
+ IOTX_LINKKIT_DEV_TYPE_SLAVE: 创建的设备为子设备

```
typedef struct {
    char product_key[PRODUCT_KEY_MAXLEN];
    char product_secret[PRODUCT_SECRET_MAXLEN];
    char device_name[DEVICE_NAME_MAXLEN];
    char device_secret[DEVICE_SECRET_MAXLEN];
} iotx_linkkit_dev_meta_info_t;
```

+ product_key: 最大长度为20字节
+ product_secret: 最大长度为64字节
+ device_name: 最大长度为32字节
+ device_secret: 最大长度为64字节

-----

## <a name="IOT_Linkkit_Connect">IOT_Linkkit_Connect</a>

原型
---
```
int IOT_Linkkit_Connect(int devid);
```

接口说明
---
对于主设备来说, 将会建立设备与云端的通信. 对于子设备来说, 将向云端注册该子设备(如果需要的话), 并添加主子设备拓扑关系

参数说明
---

| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------
| devid   | int         | 输入    | 设备ID

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_Linkkit_Yield">IOT_Linkkit_Yield</a>

原型
---
```
void IOT_Linkkit_Yield(int timeout_ms);
```

接口说明
---
若SDK占有独立线程, 该函数只将接收到的网络报文分发到用户的回调函数中, 否则表示将CPU交给SDK让其接收网络报文并将消息分发到用户的回调函数中

参数说明
---

| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-------------------------------------------------
| timeout_ms  | int         | 输入    | 单线程模式下, 每次尝试接收网络报文的超时时间

返回值说明
---
无返回值

-----

## <a name="IOT_Linkkit_Close">IOT_Linkkit_Close</a>

原型
---
```
int IOT_Linkkit_Close(int devid);
```

接口说明
---
若设备ID为主设备, 则关闭网络连接并释放Linkkit所有占用资源

参数说明
---

| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------
| devid   | int         | 输入    | 设备ID

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_Linkkit_TriggerEvent">IOT_Linkkit_TriggerEvent</a>

原型
---
```
int IOT_Linkkit_TriggerEvent(int devid, char *eventid, int eventid_len, char *payload, int payload_len);
```

接口说明
---
向云端上报设备事件

参数说明
---

| 参数            | 数据类型    | 方向    | 说明
|-----------------|-------------|---------|---------------------
| devid           | int         | 输入    | 设备ID
| eventid         | char *      | 输入    | TSL中定义的事件ID
| eventid_len     | int         | 输入    | 事件ID的长度
| payload         | char *      | 输入    | 事件Payload
| payload_len     | int         | 输入    | 事件Payload的长度

返回值说明
---
| 值      | 说明
|---------|---------
| >= 1    | 消息ID
| < 0     | 失败

-----

## <a name="IOT_Linkkit_Report">IOT_Linkkit_Report</a>

原型
---
```
int IOT_Linkkit_Report(int devid,
                        iotx_linkkit_msg_type_t msg_type,
                        unsigned char *payload,
                        int payload_len);
```

接口说明
---
向云端发送消息, 包括属性上报/设备标签信息更新上报/设备标签信息删除上报/透传数据上报/子设备登录/子设备登出

参数说明
---

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| msg_type        | iotx_linkkit_msg_type_t     | 输入    | 需要上报的消息类型
| payload         | unsigned char *             | 输入    | 消息Payload
| payload_len     | int                         | 输入    | 消息Payload的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| >= 1    | 消息ID
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    ITM_MSG_POST_PROPERTY,
    ITM_MSG_DEVICEINFO_UPDATE,
    ITM_MSG_DEVICEINFO_DELETE,
    ITM_MSG_POST_RAW_DATA,
    ITM_MSG_LOGIN,
    ITM_MSG_LOGOUT,
    ...
    ...

    IOTX_LINKKIT_MSG_MAX
} iotx_linkkit_msg_type_t;
```
+ ITM_MSG_POST_PROPERTY: 设备属性数据上报
+ ITM_MSG_DEVICEINFO_UPDATE: 设备标签更新信息上报
+ ITM_MSG_DEVICEINFO_DELETE: 设备标签删除信息上报
+ ITM_MSG_POST_RAW_DATA: 设备透传数据上报
+ ITM_MSG_LOGIN: 子设备登录
+ ITM_MSG_LOGOUT: 子设备登出
+ ITM_MSG_DELETE_TOPO: 删除子设备和网关之间的拓扑关系
+ ITM_MSG_REPORT_SUBDEV_FIRMWARE_VERSION: 上报子设备的固件版本号, 用于子设备OTA功能
+ ITM_MSG_PROPERTY_DESIRED_GET: 获取云端缓存的属性值下发, 用于高级版设备影子
+ ITM_MSG_PROPERTY_DESIRED_DELETE: 主动删除云端缓存的属性值, 用于高级版设备影子

-----

## <a name="IOT_Linkkit_Query">IOT_Linkkit_Query</a>

原型
---
```
int IOT_Linkkit_Query(int devid,
                        iotx_linkkit_msg_type_t msg_type,
                        unsigned char *payload,
                        int payload_len);
```

接口说明
---
向云端查询数据, 包括查询时间戳/查询设备的拓扑关系列表/查询FOTA升级的固件数据/查询COTA升级的Config文件数据/查询是否有可用的新固件/查询是否有可用的Config文件

参数说明
---

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| msg_type        | iotx_linkkit_msg_type_t     | 输入    | 需要上报的消息类型
| payload         | unsigned char *             | 输入    | 消息Payload
| payload_len     | int                         | 输入    | 消息Payload的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| >= 1    | 消息ID
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    ...
    ...
    ITM_MSG_QUERY_TIMESTAMP,
    ITM_MSG_QUERY_TOPOLIST,
    ITM_MSG_QUERY_FOTA_DATA,
    ITM_MSG_QUERY_COTA_DATA,
    ITM_MSG_REQUEST_COTA,
    ITM_MSG_REQUEST_FOTA_IMAGE,

    IOTX_LINKKIT_MSG_MAX
} iotx_linkkit_msg_type_t;
```
+ ITM_MSG_QUERY_TIMESTAMP: 查询时间戳
+ ITM_MSG_QUERY_TOPOLIST: 查询设备的拓扑关系列表
+ ITM_MSG_QUERY_FOTA_DATA: 查询FOTA升级的固件数据
+ ITM_MSG_QUERY_COTA_DATA: 查询COTA升级的远程配置数据
+ ITM_MSG_REQUEST_FOTA_IMAGE: 查询是否有可用的新固件
+ ITM_MSG_REQUEST_COTA: 查询是否有可用的远程配置数据

-----

## <a name="IOT_RegisterCallback">IOT_RegisterCallback</a>

原型
---
```
define IOT_RegisterCallback(evt, cb)           iotx_register_for_##evt(cb);

```

接口说明
---
该接口用于注册事件的回调函数, 当Linkkit SDK产生事件时, 会调用对应的回调函数

参数说明
---

| 参数    | 数据类型                    | 方向    | 说明
|---------|-----------------------------|---------|-------------
| evt     | iotx_ioctl_event_t          | 输入    | 事件名称
| cb      | 根据evt的不同而各有不同     | 输入    | 回调函数

-----

返回值说明
---
无返回值

事件清单
---
```
typedef enum {
    ...
    ITE_CONNECT_SUCC,
    ...
    ITE_DISCONNECTED,
    ITE_RAWDATA_ARRIVED,
    ITE_SERVICE_REQUEST,
    ITE_PROPERTY_SET,
    ITE_PROPERTY_GET,
    ITE_REPORT_REPLY,
    ITE_TRIGGER_EVENT_REPLY,
    ITE_TIMESTAMP_REPLY,
    ITE_TOPOLIST_REPLY,
    ITE_PERMIT_JOIN,
    ITE_INITIALIZE_COMPLETED,
    ITE_FOTA,
    ITE_COTA
} iotx_ioctl_event_t;
```

事件列表
---

| 事件                                                    | 回调函数原型                                                                                                                                                    | 事件触发条件说明
|---------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------
| [ITE_CONNECT_SUCC](#ITE_CONNECT_SUCC)                   | int callback(void);                                                                                                                                             | 与云端连接成功时
| [ITE_DISCONNECTED](#ITE_DISCONNECTED)                   | int callback(void);                                                                                                                                             | 与云端连接断开时
| [ITE_RAWDATA_ARRIVED](#ITE_RAWDATA_ARRIVED)             | int callback(const int devid, const unsigned char *payload, const int payload_len);                                                                             | Linkkit收到收到raw data数据时
| [ITE_SERVICE_REQUEST](#ITE_SERVICE_REQUEST)               | int callback(const int devid, const char *serviceid, const int serviceid_len, const char *request, const int request_len, char **response, int *response_len);  | Linkkit收到收到服务(同步/异步)调用请求时
| [ITE_PROPERTY_SET](#ITE_PROPERTY_SET)                   | int callback(const int devid, const char *request, const int request_len);                                                                                      | Linkkit收到收到属性设置请求时
| [ITE_PROPERTY_GET](#ITE_PROPERTY_GET)                   | int callback(const int devid, const char *request, const int request_len, char **response, int *response_len);                                                  | Linkkit收到收到属性获取的请求时
| [ITE_REPORT_REPLY](#ITE_REPORT_REPLY)                   | int callback(const int devid, const int msgid, const int code, const char *reply, const int reply_len);                                                         | Linkkit收到收到上报消息的应答时
| [ITE_TRIGGER_EVENT_REPLY](#ITE_TRIGGER_EVENT_REPLY)     | int callback(const int devid, const int msgid, const int code, const char *eventid, const int eventid_len, const char *message, const int message_len);         | Linkkit收到收到事件上报消息的应答时
| [ITE_TIMESTAMP_REPLY](#ITE_TIMESTAMP_REPLY)             | int callback(const char *timestamp);                                                                                                                            | 当Linkkit收到收到查询时间戳请求的应答时
| [ITE_TOPOLIST_REPLY](#ITE_TOPOLIST_REPLY)               | int callback(const int devid, const int msgid, const int code, const char * payload, const int payload_len);                                                    | Linkkit收到收到查询拓扑关系请求的应答时
| [ITE_PERMIT_JOIN](#ITE_PERMIT_JOIN)                     | int callback(const char * product_key, const int time);                                                                                                         | Linkkit收到允许子设备入网的请求时
| [ITE_INITIALIZE_COMPLETED](#ITE_INITIALIZE_COMPLETED)   | int callback(const int devid);                                                                                                                                  | 设备初始化完成时
| [ITE_FOTA](#ITE_FOTA)                                   | int callback(int type, const char *version);                                                                                                                    | Linkkit收到可用固件的通知时
| [ITE_COTA](#ITE_COTA)                                   | int callback(int type, const char *config_id, int config_size, const char *get_type, const char *sign, const char *sign_method, const char *url);               | Linkkit收到可用远程配置文件的通知时

## <a name="IOT_Ioctl">IOT_Ioctl</a>

原型
---
```
int IOT_Ioctl(int option, void *data);
```

接口说明
---
用于配置SDK的一些全局选项, 在使用Linkkit高级版时, 需要在`IOT_Linkkit_Connect`前使用

参数说明
---

| 参数    | 数据类型    | 方向        | 说明
|---------|-------------|-------------|-----------------------------
| option  | int         | 输入        | 需要进行的操作
| data    | void *      | 输入/输出   | option需要的输入/输出参数

返回值说明
---
| 值      | 说明
|---------|---------
| >= 0    | 成功
| < 0     | 失败

参数附加说明
---
`option`选项如下:
```
typedef enum {
    IOTX_IOCTL_SET_REGION,
    IOTX_IOCTL_GET_REGION,
    IOTX_IOCTL_SET_MQTT_DOMAIN,
    IOTX_IOCTL_SET_HTTP_DOMAIN,
    IOTX_IOCTL_SET_DYNAMIC_REGISTER,
    IOTX_IOCTL_GET_DYNAMIC_REGISTER,
    IOTX_IOCTL_RECV_PROP_REPLY,
    IOTX_IOCTL_RECV_EVENT_REPLY,
    IOTX_IOCTL_SEND_PROP_SET_REPLY,
    IOTX_IOCTL_SET_SUBDEV_SIGN,
    IOTX_IOCTL_GET_SUBDEV_LOGIN
} iotx_ioctl_option_t;
```
+ IOTX_IOCTL_SET_REGION: 设置登录服务器区域, `data`的数据类型为`int *`, 取值见`iot_export.h`中的`iotx_cloud_region_types_t`枚举量
+ IOTX_IOCTL_GET_REGION: 获取当前登录服务器区域, `data`的数据类型为`int *`
+ IOTX_IOCTL_SET_MQTT_DOMAIN: 当`IOTX_IOCTL_SET_REGION`没有需要的服务器区域时, 设置登录MQTT服务器的区域. `data`的数据类型为`char *`
+ IOTX_IOCTL_SET_HTTP_DOMAIN: 当`IOTX_IOCTL_SET_REGION`没有需要的服务器区域时, 设置登录HTTP服务器的区域. `data`的数据类型为`char *`
+ IOTX_IOCTL_SET_DYNAMIC_REGISTER: 设置是否需要使用一型一密, `data`的数据类型为`int *`. 当data的值为1时, 使用一型一密. 当data的值为0时, 不使用一型一密
+ IOTX_IOCTL_GET_DYNAMIC_REGISTER: 获取当前是否使用一型一密
+ IOTX_IOCTL_RECV_PROP_REPLY: 废弃, 与`IOTX_IOCTL_RECV_EVENT_REPLY`功能相同
+ IOTX_IOCTL_RECV_EVENT_REPLY: 控制当用户上报属性和事件时, 是否需要云端的应答消息, `data`的数据类型为`int *`. 当data的值为1时, 需要云端返回应答消息. 当data的值为0时, 不需要云端返回应答消息
+ IOTX_IOCTL_SEND_PROP_SET_REPLY: 控制当SDK收到云端的设置属性的消息时, 是否需要向云端发送应答消息, `data`的数据类型为`int *`. 当data的值为1时, SDK需要向云端发送设置属性的应答消息. 当data的值为0时, SDK不需要向云端发送设置属性的应答消息
+ IOTX_IOCTL_SET_SUBDEV_SIGN: 预留
+ IOTX_IOCTL_GET_SUBDEV_LOGIN: 预留
+ IOTX_IOCTL_QUERY_DEVID: 获取ProductKey，DeviceName对应的子设备的Devid。输入为指向iotx_linkkit_dev_meta_info_t类型数据的指针；输出为Devid，如果子设备不存在则返回-1。以linkkit_example_gateway.c为例，下面代码即可获取子设备数组中subdevArr[2]对应的devid。
    ```
    int subdev_id = 0;
    subdev_id = IOT_Ioctl(IOTX_IOCTL_QUERY_DEVID, (void *)&subdevArr[2]);
    ```

-----

# <a name="Event列表详解">Event列表详解</a>
## <a name="ITE_CONNECT_SUCC">ITE_CONNECT_SUCC</a>

原型
---
```
int callback(void);
```

接口说明
---
当Linkkit与云端连接成功时, 会触发此事件

参数说明
---
无

-----

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

## <a name="ITE_DISCONNECTED">ITE_DISCONNECTED</a>

原型
---
```
int callback(void);
```

接口说明
---
当Linkkit与云端连接断开时, 会触发此事件

参数说明
---
无

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_RAWDATA_ARRIVED">ITE_RAWDATA_ARRIVED</a>

原型
---
```
int callback(const int devid, const unsigned char *payload, const int payload_len);
```

接口说明
---
当Linkkit收到透传数据时, 会触发此事件并调用回调函数

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|---------------------
| devid           | int                     | 输入    | 设备ID
| payload         | const unsigned char *   | 输入    | 透传数据payload
| payload_len     | const int               | 输入    | payload的长度

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_SERVICE_REQUEST">ITE_SERVICE_REQUEST</a>

原型
---
```
int callback(const int devid, const char *serviceid, const int serviceid_len, const char *request, const int request_len, char **response, int *response_len);
```

接口说明
---
当Linkkit收到异步或同步的服务调用时, 会触发此事件并调用回调函数. 其中, 如果服务有输出参数需要发送回云端, 用户需要对`*response`使用`HAL_Malloc`分配一块内存, 将需要发送给云端的消息填入其中, 并将输出参数的长度填入`*response_len`中, Linkkit会负责释放这块内存. 具体操作可参考示例程序`linkkit_example_solo.c`

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|---------------------
| devid           | int             | 输入    | 设备ID
| serviceid       | const char *    | 输入    | 服务ID
| serviceid_len   | const int       | 输入    | serviceid的长度
| request         | const char *    | 输入    | 服务的输入参数
| request_len     | const int       | 输入    | 服务的输入参数长度
| response        | char **         | 输出    | 服务的输出参数
| response_len    | int *           | 输出    | 服务的输出参数长度

返回值说明
---
返回值需要注意的是, 当***response**存在的情况下, 返回0或-1会将此次服务调用的成功与否一并发送给云端

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_PROPERTY_SET">ITE_PROPERTY_SET</a>

原型
---
```
int callback(const int devid, const char *request, const int request_len);
```

接口说明
---
当Linkkit收到属性设置的请求时, 会触发此事件并调用回调函数

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|---------------------
| devid           | int             | 输入    | 设备ID
| request         | const char *    | 输入    | 属性设置的payload
| request_len     | const int       | 输入    | payload的长度

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_PROPERTY_GET">ITE_PROPERTY_GET</a>

原型
---
```
int callback(const int devid, const char *request, const int request_len, char **response, int *response_len);
```

接口说明
---
当Linkkit收到属性获取的请求时, 会触发此事件并调用回调函数. 其中, `request`会包含所有发送方需要知道的属性ID, 用户需要对`*response`使用`HAL_Malloc`分配一块内存并将所有请求的属性ID和它们的值填到`*response`中, 将`*response`的长度填到`*response_len`中, Linkkit会负责释放这块内存. 具体操作可参考示例程序`linkkit_example_solo.c`

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| devid           | int             | 输入    | 设备ID
| request         | const char *    | 输入    | 属性获取请求的payload
| request_len     | const int       | 输入    | payload的长度
| response        | char **         | 输出    | 所有被请求的属性值的集合
| response_len    | int *           | 输出    | *response的长度

返回值说明
---
返回值需要注意的是, 当***response**存在的情况下, 返回0或-1会将此次服务调用的成功与否一并发送给云端

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_REPORT_REPLY">ITE_REPORT_REPLY</a>

原型
---
```
int callback(const int devid, const int msgid, const int code, const char *reply, const int reply_len);
```

接口说明
---
当Linkkit收到属性上报/设备标签更新/设备标签删除的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------
| devid       | int             | 输入    | 设备ID
| msgid       | const int       | 输入    | 消息ID
| code        | const int       | 输入    | 云端返回的错误码
| reply       | const char *    | 输入    | 错误码的描述信息
| reply_len   | const int       | 输入    | 错误码描述信息的长度

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_TRIGGER_EVENT_REPLY">ITE_TRIGGER_EVENT_REPLY</a>

原型
---
```
int callback(const int devid, const int msgid, const int code, const char *eventid, const int eventid_len, const char *message, const int message_len);
```

接口说明
---
当Linkkit收到事件上报的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------
| devid           | int             | 输入    | 设备ID
| msgid           | const int       | 输入    | 消息ID
| code            | const int       | 输入    | 云端返回的错误码
| eventid         | const char *    | 输入    | 事件ID
| eventid_len     | const int       | 输入    | 事件ID的长度
| message         | const char *    | 输入    | 事件错误码的描述信息
| message_len     | const int       | 输入    | message的长度

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_TIMESTAMP_REPLY">ITE_TIMESTAMP_REPLY</a>

原型
---
```
int callback(const char *timestamp);
```

接口说明
---
当Linkkit收到查询时间戳的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| timestamp   | const char *    | 输入    | 时间戳字符串

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_TOPOLIST_REPLY">ITE_TOPOLIST_REPLY</a>

原型
---
```
int callback(const int devid, const int msgid, const int code, const char * payload, const int payload_len);
```

接口说明
---
当Linkkit收到查询时间戳的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|---------------------
| devid           | int             | 输入    | 设备ID
| msgid           | const int       | 输入    | 消息ID
| code            | const int       | 输入    | 云端返回的错误码
| payload         | const char *    | 输入    | 拓扑关系列表
| payload_len     | const int       | 输入    | payload的长度

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_PERMIT_JOIN">ITE_PERMIT_JOIN</a>

原型
---
```
int callback(const char * product_key, const int time);
```

接口说明
---
当Linkkit收到允许子设备入网的请求时, 会触发此事件并调用回调函数

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------------------------------------------------------
| product_key     | const char *    | 输入    | 子设备的Product Key, 如果该字段为字符串"NULL", 则允许任何子设备接入
| time            | const int       | 输入    | 允许子设备接入的时间窗口

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_INITIALIZE_COMPLETED">ITE_INITIALIZE_COMPLETED</a>

原型
---
```
int callback(const int devid);
```

接口说明
---
当使用`IOT_Linkkit_Connect`连接网络的设备初始化完成时, 会触发此事件并调用回调函数

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------
| devid   | int         | 输入    | 设备ID

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_FOTA">ITE_FOTA</a>

原型
---
```
int callback(int type, const char *version);
```

接口说明
---
当Linkkit收到可用固件的通知时, 会触发此事件并调用回调函数. 用户在收到新固件通知后, 可使用`IOT_Linkkit_Query`的`ITM_MSG_QUERY_FOTA_DATA`消息获取新固件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------------------------------------------
| type        | int             | 输入    | FOTA的消息类型, 目前只有值为`0`的一种消息, 即新固件到达
| version     | const char *    | 输入    | 可用的固件版本号

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="ITE_COTA">ITE_COTA</a>

原型
---
```
int callback(int type, const char *config_id, int config_size, const char *get_type, const char *sign, const char *sign_method, const char *url);
```

接口说明
---
当Linkkit收到可用配置文件的通知时, 会触发此事件并调用回调函数. 用户在收到新固件通知后, 可使用`IOT_Linkkit_Query`的`ITM_MSG_QUERY_COTA_DATA`消息获取新固件

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|---------------------------------------------------------------------
| type            | int             | 输入    | COTA的消息类型, 目前只有值为`0`的一种消息, 即存在可用的配置文件
| config_id       | const char *    | 输入    | 配置文件ID
| config_size     | int             | 输入    | 配置文件大小
| get_type        | const char *    | 输入    | 配置文件数据类型
| sign            | const char *    | 输入    | 配置文件的签名值
| sign_method     | const char *    | 输入    | 配置文件的签名方法
| url             | const char *    | 输入    | 配置文件的下载地址

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----
