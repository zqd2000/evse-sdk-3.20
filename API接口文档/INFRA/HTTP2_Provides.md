# <a name="目录">目录</a>
+ [HTTP2流式传输API详解](#HTTP2流式传输API详解)
    * [IOT_HTTP2_Connect](#IOT_HTTP2_Connect)
    * [IOT_HTTP2_Stream_Open](#IOT_HTTP2_Stream_Open)
    * [IOT_HTTP2_Stream_Send](#IOT_HTTP2_Stream_Send)
    * [IOT_HTTP2_Stream_Query](#IOT_HTTP2_Stream_Query)
    * [IOT_HTTP2_Stream_Close](#IOT_HTTP2_Stream_Close)
    * [IOT_HTTP2_Stream_UploadFile](#IOT_HTTP2_Stream_UploadFile)
    * [IOT_HTTP2_Disconnect](#IOT_HTTP2_Disconnect)


# <a name="HTTP2流式传输API详解">HTTP2流式传输API详解</a>

## <a name="IOT_HTTP2_Connect">IOT_HTTP2_Connect</a>

原型
---
```
void *IOT_HTTP2_Connect(device_conn_info_t *conn_info, http2_stream_cb_t *user_cb)
```

接口说明
---
使用conn_info中指定的参数向IOT平台建立HTTP2连接

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| conn_info       | device_conn_info_t *  | 输入     | 建连参数
| user_cb         | http2_stream_cb_t *   | 输入     | 用户注册事件回调函数


返回值说明
---
| 值      | 说明
|---------|---------
| 非NULL  | 成功
| NULL    | 失败

参数附加说明
---
```
typedef struct {
    char  *product_key;
    char  *device_name;
    char  *device_secret;
    char  *url;
    int   port;
} device_conn_info_t;
```

+ `product_key`: 三元组信息,产品KEY值
+ `device_name`: 三元组信息,设备名
+ `device_secret`: 三元组信息,设备密钥
+ `url`: 云端服务器地址
+ `port`: 云端服务器端口

```
typedef struct {
    on_stream_header_callback       on_stream_header_cb;
    on_stream_chunk_recv_callback   on_stream_chunk_recv_cb;
    on_stream_close_callback        on_stream_close_cb;
    on_stream_frame_send_callback   on_stream_frame_send_cb;
    on_stream_frame_recv_callback   on_stream_frame_recv_cb;
    on_reconnect_callback           on_reconnect_cb;
    on_disconnect_callback          on_disconnect_cb;
} http2_stream_cb_t;
```
+ `on_stream_header_cb`: 收到下行header回调函数
+ `on_stream_chunk_recv_cb`: 收到下行数据回调函数
+ `on_stream_close_cb`: 流关闭回调函数
+ `on_stream_frame_send_cb`: 帧发送回完成调函数
+ `on_stream_frame_recv_cb`: 帧接收回调函数
+ `on_reconnect_cb`: 重新连接调函数
+ `on_disconnect_cb`: 断开连接回调函数
-----

## <a name="IOT_HTTP2_Stream_Open">IOT_HTTP2_Stream_Open</a>

原型
---
```
int IOT_HTTP2_Stream_Open(void *handle, stream_data_info_t *info, header_ext_info_t *header)
```

接口说明
---
基于handle指向连接及带入参数打开一个流操作通道, 成功后用户可基于此通道进行流上传或下载操作

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄
| info            | stream_data_info_t *  | 输入/输出 | 流操作参数
| header          | header_ext_info_t *   | 输入     | 用户额外定制的头文件,可以为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

参数附加说明
---
```
typedef struct {
    char                *stream;
    uint32_t            stream_len;
    uint32_t            send_len;
    uint32_t            packet_len;
    const char          *identify;
    int                 h2_stream_id;
    char                *channel_id;
    void                *user_data;
} stream_data_info_t;
```

+ `stream`: 入参,当前流数据指针,需要指向当前需要发送的数据段,对上行发送有效
+ `stream_len`:入参,整个流数据长度,对上行发送有效
+ `send_len`: 出参,已发送长度,对上行发送有效
+ `packet_len`: 入参,单次发送长度,对上行发送有效
+ `identify`: 入参,服务端流标识
+ `h2_stream_id`: 出参,本次发送对应的http2 stream_id
+ `channel_id`: 出参,open返回的业务端通道id
+ `user_data`:  入参,带给回调函数的用户数据，可用于区分回调归属
```
typedef struct {
    http2_header      *nva;
    int               num;
} header_ext_info_t;
```

+ `nva`: 用户header集
+ `num`: 用户header集个数

-----

## <a name="IOT_HTTP2_Stream_Send">IOT_HTTP2_Stream_Send</a>

原型
---
```
int IOT_HTTP2_Stream_Send(void *handle, stream_data_info_t *info, header_ext_info_t *header);
```

接口说明
---
向指定channed id发送数据, 一个完整的流数据一般为一个header帧+多个data帧

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄
| info            | stream_data_info_t *  | 输入/输出 | 流操作参数
| header          | header_ext_info_t *   | 输入     | 用户额外定制的头文件,可以为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

参数附加说明
---
```
typedef struct {
    char                *stream;
    uint32_t            stream_len;
    uint32_t            send_len;
    uint32_t            packet_len;
    const char          *identify;
    int                 h2_stream_id;
    char                *channel_id;
} stream_data_info_t;
```

+ `stream`: 入参,当前流数据指针,需要指向当前需要发送的数据段,对上行发送有效
+ `stream_len`:入参,整个流数据长度,对上行发送有效
+ `send_len`: 出参,已发送长度,对上行发送有效
+ `packet_len`: 入参,单次发送长度,对上行发送有效
+ `identify`: 入参,服务端流标识
+ `h2_stream_id`: 出参,本次发送对应的http2 stream_id
+ `channel_id`: 出参,open返回的业务端通道id

```
typedef struct {
    http2_header      *nva;
    int               num;
} header_ext_info_t;
```

+ `nva`: 用户header集
+ `num`: 用户header集个数

-----

## <a name="IOT_HTTP2_Stream_Query">IOT_HTTP2_Stream_Query</a>

原型
---
```
int IOT_HTTP2_Stream_Query(void *handle, stream_data_info_t *info, header_ext_info_t *header)
```

接口说明
---
向指定channed id请求下行数据,类似数据订阅接口,下行数据通过on_stream_chunk_recv_cb通知用户

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄
| info            | stream_data_info_t *  | 输入/输出 | 流操作参数
| header          | header_ext_info_t *   | 输入     | 用户额外定制的头文件,可以为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

参数附加说明
---
```
typedef struct {
    char                *stream;
    uint32_t            stream_len;
    uint32_t            send_len;
    uint32_t            packet_len;
    const char          *identify;
    int                 h2_stream_id;
    char                *channel_id;
} stream_data_info_t;
```

+ `stream`: 入参,当前流数据指针,对本函数无效
+ `stream_len`:入参,整个流数据长度,对本函数无效
+ `send_len`: 出参,已发送长度,对本函数无效
+ `packet_len`: 入参,单次发送长度,对本函数无效
+ `identify`: 入参,服务端流标识
+ `h2_stream_id`: 出参,本次发送分配的http2 stream id
+ `channel_id`: 入参,业务通道id

```
typedef struct {
    http2_header      *nva;
    int               num;
} header_ext_info_t;
```

+ `nva`: 用户header集
+ `num`: 用户header集个数

-----

## <a name="IOT_HTTP2_Stream_Close">IOT_HTTP2_Stream_Close</a>

原型
---
```
int IOT_HTTP2_Stream_Close(void *handle, stream_data_info_t *info)
```

接口说明
---
关闭业务流

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄
| info            | stream_data_info_t *  | 输入/输出 | 流操作参数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

参数附加说明
---
```
typedef struct {
    char                *stream;
    uint32_t            stream_len;
    uint32_t            send_len;
    uint32_t            packet_len;
    const char          *identify;
    int                 h2_stream_id;
    char                *channel_id;
} stream_data_info_t;
```

+ `stream`: 入参,当前流数据指针,对本函数无效
+ `stream_len`:入参,整个流数据长度,对本函数无效
+ `send_len`: 出参,已发送长度,对本函数无效
+ `packet_len`: 入参,单次发送长度,对本函数无效
+ `identify`: 入参,服务端流标识
+ `h2_stream_id`: h2 stream id,对本函数无效
+ `channel_id`: 入参,业务通道id

-----

## <a name="IOT_HTTP2_Stream_UploadFile">IOT_HTTP2_Stream_UploadFile</a>

原型
---
```
int IOT_HTTP2_Stream_UploadFile(void *handle,
                                const char *filename,
                                const char *identify,
                                upload_file_result_cb_t cb,
                                http2_file_upload_opt_t *opt,
                                void *user_data);
```

接口说明
---
向云端指定流通道异步发送文件,需要使能FEATURE_FS_ENABLE宏才能使用此功能

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄，由调用`IOT_HTTP2_Connect`接口时返回
| filename       | const char *           | 输入     | 文件名，文件名中只能包含`[0-9][a-z][A-Z]`以及`_.`这些限定字符
| identify        | const char *          | 输入     | 服务端流通道标识，固定使用字符串`"c/iot/sys/thing/file/upload"`
| cb              | upload_file_result_cb | 输入     | 发件发送状态回调函数
| opt             | http2_file_upload_opt_t * | 输入 | 配置选项结构体，目前只提供了文件覆盖选项`UPLOAD_FILE_OPT_BIT_OVERWRITE`
| user_data       | void *                | 输入     | 带给回调函数的用户数据

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

参数附加说明
---
**回调函数原型**：
```
typedef void (* upload_file_result_cb)(const char *path, int result, void *user_data);
```
**result取值范围**:
```
typedef enum {
    UPLOAD_FILE_NOT_EXIST     = -9,
    UPLOAD_FILE_READ_FAILED   = -8,
    UPLOAD_STREAM_OPEN_FAILED = -7,
    UPLOAD_STREAM_SEND_FAILED = -6,
    UPLOAD_MALLOC_FAILED      = -5,
    UPLOAD_NULL_POINT         = -2,
    UPLOAD_ERROR_COMMON       = -1,
    UPLOAD_SUCCESS            = 0,
} http2_file_upload_result_t;
```

**配置选项结构体**
```
typedef struct {
    uint32_t opt_bit_map;
} http2_file_upload_opt_t;
```
**配置选项位定义**
```
/* bit define of file override option */
#define UPLOAD_FILE_OPT_BIT_OVERWRITE       (0x00000001)
```

-----

## <a name="IOT_HTTP2_Disconnect">IOT_HTTP2_Disconnect</a>

原型
---
```
int IOT_HTTP2_Disconnect(void *handle)
```

接口说明
---
断开http2连接

该接口在SDK基础版或高级版中都需要用户显式调用

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-----------------------|---------|---------------------------------------------------------------------
| handle          | void *                | 输入     | 连接句柄

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 非0     | 失败

-----
