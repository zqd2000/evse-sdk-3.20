# <a name="目录">目录</a>
+ [MQTT相关HAL接口详解](#MQTT相关HAL接口详解)
    * [HAL_SSL_Destroy](#HAL_SSL_Destroy)
    * [HAL_SSL_Establish](#HAL_SSL_Establish)
    * [HAL_SSL_Read](#HAL_SSL_Read)
    * [HAL_SSL_Write](#HAL_SSL_Write)
    * [HAL_TCP_Destroy](#HAL_TCP_Destroy)
    * [HAL_TCP_Establish](#HAL_TCP_Establish)
    * [HAL_TCP_Read](#HAL_TCP_Read)
    * [HAL_TCP_Write](#HAL_TCP_Write)

# <a name="MQTT相关HAL接口详解">MQTT相关HAL接口详解</a>

## <a name="HAL_SSL_Destroy">HAL_SSL_Destroy</a>

原型
---
```
int32_t HAL_SSL_Destroy(_IN_ uintptr_t handle);
```

接口说明
---
销毁由参数`handle`指定的TLS连接

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-----------------
| handle  | uintptr_t   | 输入    | TLS连接句柄

返回值说明
---
| 值      | 说明
|---------|-------------
| < 0     | 操作失败
| = 0     | 操作成功

-----

## <a name="HAL_SSL_Establish">HAL_SSL_Establish</a>

原型
---
```
uintptr_t HAL_SSL_Establish(
            _IN_ const char *host,
            _IN_ uint16_t port,
            _IN_ const char *ca_crt,
            _IN_ size_t ca_crt_len);
```

接口说明
---
根据指定的服务器网络地址, 服务器端口号和证书文件建立TLS连接, 返回对应的连接句柄

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------
| host        | const char  | 输入    | 指定的TLS服务器网络地址
| port        | uint16_t    | 输入    | 指定的TLS服务器端口
| ca_crt      | const char  | 输入    | 指向PEM编码的X.509证书的指针
| ca_crt_len  | size_t      | 输入    | 证书字节长度

返回值说明
---
| 值      | 说明
|---------|-----------------------------
| NULL    | 创建失败
| !NULL   | 创建成功, 返回TLS连接句柄

-----

## <a name="HAL_SSL_Read">HAL_SSL_Read</a>

原型
---
```
int32_t HAL_SSL_Read(_IN_ uintptr_t handle, _OU_ char *buf, _OU_ int len, _IN_ int timeout_ms);
```

接口说明
---
从指定的TLS连接中读取数据, 此接口为同步接口, 如果在超时时间内读取到参数`len`指定长度的数据则立即返回, 否则在超时时间到时才解除阻塞返回

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-----------------------------
| handle      | uintptr_t   | 输入    | TLS连接句柄
| buf         | char *      | 输出    | 指向数据接收缓冲区的指针
| len         | int         | 输入    | 数据接收缓冲区的字节大小
| timeout_ms  | int         | 输入    | 超时时间

返回值说明
---
| 值      | 说明
|---------|-------------------------------------
| -2      | TLS连接发生错误
| -1      | TLS连接被远程设备关闭
| 0       | TLS读超时, 且没有接收到任何数据
| > 0     | TLS读取到的字节数, TLS读取成功

-----

## <a name="HAL_SSL_Write">HAL_SSL_Write</a>

原型
---
```
int32_t HAL_SSL_Write(_IN_ uintptr_t handle, _IN_ const char *buf, _IN_ int len, _IN_ int timeout_ms);
```

接口说明
---
向指定的TLS连接中写入数据, 此接口为同步接口, 如果在超时时间内写入了参数`len`指定长度的数据则立即返回, 否则在超时时间到时才解除阻塞返回

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-----------------------------
| handle      | uintptr_t   | 输入    | TLS连接句柄
| buf         | char *      | 输入    | 指向数据发送缓冲区的指针
| len         | int         | 输入    | 数据发送缓冲区的字节大小
| timeout_ms  | int         | 输入    | 超时时间

返回值说明
---
| 值      | 说明
|---------|---------------------------------
| < 0     | TLS连接发生错误
| 0       | TLS写超时, 且没有写入任何数据
| > 0     | TLS写入的字节数, TLS写入成功

-----


## <a name="HAL_TCP_Destroy">HAL_TCP_Destroy</a>

原型
---
```
int32_t HAL_TCP_Destroy(_IN_ uintptr_t fd);
```

接口说明
---
销毁由参数`fd`指定的TCP连接, 释放资源

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-----------------
| fd      | uintptr_t   | 输入    | TCP连接句柄

返回值说明
---
| 值      | 说明
|---------|-------------
| < 0     | 操作失败
| = 0     | 操作成功

-----

## <a name="HAL_TCP_Establish">HAL_TCP_Establish</a>

原型
---
```
uintptr_t HAL_TCP_Establish(_IN_ const char *host, _IN_  uint16_t port);
```

接口说明
---
根据指定的服务器网络地址和端口号建立TCP连接, 并返回对应连接句柄

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------
| host    | const char *    | 输入    | 指定TCP服务器的网络地址
| port    | uint16_t        | 输入    | 指定TCP服务器的端口号

返回值说明
---
| 值                  | 说明
|---------------------|-----------------------------------------
| (uintptr_t)(-1)     | TCP连接建立失败
| 其它值(也包括0)     | TCP连接建立成功, 返回对应的连接句柄

-----

## <a name="HAL_TCP_Read">HAL_TCP_Read</a>

原型
---
```
int32_t HAL_TCP_Read(_IN_ uintptr_t fd, _OU_ char *buf, _IN_ uint32_t len, _IN_ uint32_t timeout_ms);
```

接口说明
---
从指定的TCP连接中读取数据, 此接口为同步接口, 如果在超时时间内读取到参数`len`指定长度的数据则立即返回, 否则在超时时间到时才解除阻塞返回

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-----------------------------
| fd          | uintptr_t   | 输入    | TCP连接句柄
| buf         | char *      | 输出    | 指向数据接收缓冲区的指针
| len         | int         | 输入    | 数据接收缓冲区的字节大小
| timeout_ms  | int         | 输入    | 超时时间

返回值说明
---
| 值      | 说明
|---------|-------------------------------------
| -2      | TCP连接发生错误
| -1      | TCP连接被远程设备关闭
| 0       | TCP读超时, 且没有接收到任何数据
| > 0     | TCP读取成功, 返回读取到的字节数

-----

## <a name="HAL_TCP_Write">HAL_TCP_Write</a>

原型
---
```
int32_t HAL_TCP_Write(_IN_ uintptr_t fd, _IN_ const char *buf, _IN_ uint32_t len, _IN_ uint32_t timeout_ms);
```

接口说明
---
从指定的TCP连接中写入数据, 此接口为同步接口, 如果在超时时间内写入了参数`len`指定长度的数据则立即返回, 否则在超时时间到时才解除阻塞返回

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-----------------------------
| fd          | uintptr_t   | 输入    | TCP连接句柄
| buf         | char *      | 输入    | 指向数据发送缓冲区的指针
| len         | int         | 输入    | 数据发送缓冲区的字节大小
| timeout_ms  | int         | 输入    | 超时时间

返回值说明
---
| 值      | 说明
|---------|---------------------------------
| < 0     | TCP连接发生错误
| 0       | TCP写超时, 且没有写入任何数据
| > 0     | TCP入成功, 返回TCP写入的字节数

-----
