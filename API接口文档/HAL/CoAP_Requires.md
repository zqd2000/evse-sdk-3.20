# <a name="目录">目录</a>
+ [CoAP上云相关HAL接口详解](#CoAP上云相关HAL接口详解)
    * [HAL_DTLSSession_create](#HAL_DTLSSession_create)
    * [HAL_DTLSSession_free](#HAL_DTLSSession_free)
    * [HAL_DTLSSession_read](#HAL_DTLSSession_read)
    * [HAL_DTLSSession_write](#HAL_DTLSSession_write)
    * [HAL_UDP_close_without_connect](#HAL_UDP_close_without_connect)
    * [HAL_UDP_create](#HAL_UDP_create)
    * [HAL_UDP_create_without_connect](#HAL_UDP_create_without_connect)
    * [HAL_UDP_joinmulticast](#HAL_UDP_joinmulticast)
    * [HAL_UDP_readTimeout](#HAL_UDP_readTimeout)
    * [HAL_UDP_recvfrom](#HAL_UDP_recvfrom)
    * [HAL_UDP_send](#HAL_UDP_send)
    * [HAL_UDP_write](#HAL_UDP_write)

# <a name="CoAP上云相关HAL接口详解">CoAP上云相关HAL接口详解</a>
## <a name="HAL_DTLSSession_create">HAL_DTLSSession_create</a>

原型
---
```
DTLSContext *HAL_DTLSSession_create(_IN_ coap_dtls_options_t  *p_options);
```

接口说明
---
根据参数`p_options`指定的证书, 服务器地址和端口建立DTLS连接, 并返回DTLS会话句柄

参数说明
---
| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------------------------------
| p_options   | coap_dtls_options_t *   | 输入    | 指向`coap_dtls_options_t`结构体类型选项数据的指针

```
typedef struct {
    unsigned char             *p_ca_cert_pem;       // 指向PEM编码的X.509证书的指针
    char                      *p_host;              // 指向DTLS服务器网络地址的指针
    unsigned short             port;                // DTLS服务器端口
} coap_dtls_options_t;
```

返回值说明
---
DTLS会话句柄

-----

## <a name="HAL_DTLSSession_free">HAL_DTLSSession_free</a>

原型
---
```
unsigned int HAL_DTLSSession_free(_IN_ DTLSContext *context);
```

接口说明
---
销毁由参数`context`指定的DTLS会话, 释放资源

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| context     | DTLSContext *   | 输入    | DTLS会话句柄

返回值说明
---
| 值      | 说明
|---------|-----------------------------
| 0       | 操作成功
| > 0     | [操作错误码](#DTLS错误码)

DTLS错误码:

```
define DTLS_ERROR_BASE                 (1<<24)
define DTLS_INVALID_PARAM              (DTLS_ERROR_BASE | 1)       // 无效参数
define DTLS_INVALID_CA_CERTIFICATE     (DTLS_ERROR_BASE | 2)       // 无效证书
define DTLS_HANDSHAKE_IN_PROGRESS      (DTLS_ERROR_BASE | 3)       // 正在握手
define DTLS_HANDSHAKE_FAILED           (DTLS_ERROR_BASE | 4)       // 握手失败
define DTLS_FATAL_ALERT_MESSAGE        (DTLS_ERROR_BASE | 5)       // 致命警告消息
define DTLS_PEER_CLOSE_NOTIFY          (DTLS_ERROR_BASE | 6)       // 对方打开连接
define DTLS_SESSION_CREATE_FAILED      (DTLS_ERROR_BASE | 7)       // 会话创建失败
define DTLS_READ_DATA_FAILED           (DTLS_ERROR_BASE | 8)       // 数据读取失败
```

-----

## <a name="HAL_DTLSSession_read">HAL_DTLSSession_read</a>

原型
---
```
unsigned int HAL_DTLSSession_read(_IN_ DTLSContext       *context,
                                  _OUT_ unsigned char     *p_data,
                                  _OUT_ unsigned int      *p_datalen,
                                  _IN_ unsigned int      timeout_ms);
```

接口说明
---
从指定DTLS连接中读取数据, 此接口为同步接口, 在超前前读取到数据则立即返回, 否则在超时时间到时才解除阻塞并返回

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-----------------------------
| context     | DTLSContext *       | 输入    | DTLS会话句柄
| p_data      | unsigned char *     | 输出    | 指向接收缓冲区的指针
| p_datalen   | unsigned int *      | 输出    | 指向接收数据长度变量的指针
| timeout_ms  | unsigned int        | 输入    | 超时时间

返回值说明
---
| 值      | 说明
|---------|-----------------------------
| 0       | 操作成功
| > 0     | [操作错误码](#DTLS错误码)

-----

## <a name="HAL_DTLSSession_write">HAL_DTLSSession_write</a>

原型
---
```
unsigned int HAL_DTLSSession_write(_IN_ DTLSContext          *context,
                                   _IN_ const unsigned char  *p_data,
                                   _IN_ unsigned int         *p_datalen);
```

接口说明
---
向指定DTLS连接写入数据

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-----------------------------------------------------
| context     | DTLSContext *       | 输入    | DTLS会话句柄
| p_data      | unsigned char *     | 输入    | 指向发送数据缓冲区的指针
| p_datalen   | unsigned int *      | 输入/输出| 指向发送数据长度变量的指针, 用于指定发送字节长度,出参时代表实际写入长度

返回值说明
---
| 值      | 说明
|---------|-----------------------------
| 0       | 操作成功
| > 0     | [操作错误码](#DTLS错误码)

-----

## <a name="HAL_UDP_close_without_connect">HAL_UDP_close_without_connect</a>

原型
---
```
int HAL_UDP_close_without_connect(_IN_ intptr_t sockfd)
```

接口说明
---
销毁sockfd指定的UDP socket，释放资源

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------
| sockfd  | intptr_t        | 输入    | UDP socket句柄

返回值说明
---
| 值      | 说明
|---------|-------------
| < 0     | 操作失败
| = 0     | 操作成功

-----

## <a name="HAL_UDP_create">HAL_UDP_create</a>

原型
---
```
intptr_t HAL_UDP_create(_IN_ char *host, _IN_ unsigned short port);
```

接口说明
---
建立指定目的地址和目的端口的UDP连接

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------
| host    | const char *    | 输入    | UDP目的地址
| port    | unsigned short  | 输入    | UDP目的端口

返回值说明
---
| 值      | 说明
|---------|-------------------------------------
| < 0     | 创建失败
| >= 0    | 创建成功, 返回值为UDP socket句柄

-----

## <a name="HAL_UDP_create_without_connect">HAL_UDP_create_without_connect</a>

原型
---
```
intptr_t HAL_UDP_create_without_connect(_IN_ const char *host, _IN_ unsigned short port)
```

接口说明
---
建立指定目的地址和目的端口的UDP连接

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------
| host    | const char *    | 输入    | UDP目的地址
| port    | unsigned short  | 输入    | UDP目的端口

返回值说明
---
| 值      | 说明
|---------|-------------------------------------
| < 0     | 创建失败
| >= 0    | 创建成功, 返回值为UDP socket句柄

-----

## <a name="HAL_UDP_joinmulticast">HAL_UDP_joinmulticast</a>

原型
---
```
int HAL_UDP_joinmulticast(_IN_ intptr_t sockfd,
                          _IN_ char *p_group);
```

接口说明
---
加入组播或广播组

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-------------------------------------
| sockfd      | intptr_t    | 输入    | 指定用来发送组播请求的UDP socket
| p_group     | char *      | 输入    | 指定要加入的组播组名称


返回值说明
---
| 值      | 说明
|---------|---------------------
| < 0     | 操作失败
| = 0     | 操作成功

-----

## <a name="HAL_UDP_readTimeout">HAL_UDP_readTimeout</a>

原型
---
```
int HAL_UDP_readTimeout(
            _IN_ intptr_t p_socket,
            _OU_ unsigned char *p_data,
            _IN_ unsigned int datalen,
            _IN_ unsigned int timeout_ms);
```

接口说明
---
从指定的UDP句柄读取指定长度数据到缓冲区, 阻塞时间不超过指定时长, 若读取到指定长度数据完需立即返回, 调用该接口之前需要调用HAL_UDP_connect()设置好源地址和端口


参数说明
---
| 参数        | 数据类型         | 方向    | 说明
|-------------|----------------|---------|-------------------------------------
| p_socket    | intptr_t       | 输入    | 指定用来发送组播请求的UDP socket
| p_data      | unsigned char *| 输出    | 指向数据接收缓冲区的指针
| datalen     | unsigned int   | 输入    | 指定读数据长度
|timeout_ms   | unsigned int   | 输入    | 读超时时间

返回值说明
---
| 值      | 说明
|---------|---------------------
| < 0     | 接收过程中出现错误或异常
| = 0     | 在指定的`timeout_ms`时间内, 没有接收到任何数据
| > 0     | 在指定的`timeout_ms`时间内, 实际接收到的数据字节数

-----

## <a name="HAL_UDP_recvfrom">HAL_UDP_recvfrom</a>

原型
---
```
int HAL_UDP_recvfrom(_IN_ intptr_t sockfd,
                 _IN_ NetworkAddr *p_remote,
                 _OU_ unsigned char *p_data,
                 _IN_ unsigned int datalen,
                 _IN_ unsigned int timeout_ms);
```

接口说明
---
从指定的UDP句柄接收指定长度数据到缓冲区, 阻塞时间不超过指定时长, 且指定长度若接收完需提前返回, 调用该接口之前需要调用HAL_UDP_connect()设置好源地址和端口

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-----------------------------
| sockfd      | intptr_t            | 输入    | UDP socket句柄
| p_remote    | NetworkAddr *       | 输入    | 指定的url及端口号
| p_data      | unsigned char *     | 输出    | 指向数据接收缓冲区的指针
| datalen     | unsigned int        | 输入    | 接收缓冲区的字节大小
| timeout_ms  | unsigned int        | 输入    | 阻塞的超时时间, 单位ms

返回值说明
---
| 值      | 说明
|---------|-----------------------------------------------------
| < 0     | 接收过程中出现错误或异常
| = 0     | 在指定的`timeout_ms`时间内, 没有接收到任何数据
| > 0     | 在指定的`timeout_ms`时间内, 实际接收到的数据字节数

-----


## <a name="HAL_UDP_send">HAL_UDP_send</a>

原型
---
```
int HAL_UDP_sendto(_IN_ intptr_t          sockfd,
                   _IN_ const NetworkAddr *p_remote,
                   _IN_ const unsigned char *p_data,
                   _IN_ unsigned int datalen,
                   _IN_ unsigned int timeout_ms);
```

接口说明
---
向指定的UDP句柄发送指定缓冲区的指定长度, 阻塞时间不超过指定时长, 且指定长度若发送完需提前返回, 调用该接口之前需要调用HAL_UDP_connect()设置好目的地址和端口

参数说明
---
| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-------------------------
| sockfd      | intptr_t                | 输入    | UDP socket句柄
| p_data      | const unsigned char *   | 输入    | 指数据发送缓冲区的指针
| datalen     | unsigned int            | 输入    | 待发送数据的字节长度
| timeout_ms  | unsigned int            | 输入    | 阻塞的超时时间, 单位ms

返回值说明
---
| 值      | 说明
|---------|-----------------------------------------------------
| < 0     | 发送过程中出现错误或异常
| = 0     | 在指定的`timeout_ms`时间内, 没有任何数据发送成功
| > 0     | 在指定的`timeout_ms`时间内, 实际发送的数据字节数

-----


## <a name="HAL_UDP_write">HAL_UDP_write</a>

原型
---
```
int HAL_UDP_write(
            _IN_ intptr_t p_socket,
            _IN_ const unsigned char *p_data,
            _IN_ unsigned int datalen);
```

接口说明
---
向指定UDP句柄写入指定字节长度的数据

参数说明
---
| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------
| p_socket    | intptr_t                | 输入    | 用于标识连接的描述符
| p_data      | const unsigned char *   | 输入    | 指向数据发送缓冲区的指针
| datalen     | unsigned int            | 输入    | 待写入数据的字节长度

返回值说明
---
| 值      | 说明
|---------|---------------------
| < 0     | UDP连接发生错误
| = 0     | EOF, 文件已结束
| > 0     | 实际写入的字节数

-----
