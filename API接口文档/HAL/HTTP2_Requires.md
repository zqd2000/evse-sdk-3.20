# <a name="目录">目录</a>
+ [HTTP2相关HAL接口详解](#HTTP2相关HAL接口详解)
    * [HAL_SSL_Destroy](#HAL_SSL_Destroy)
    * [HAL_SSL_Establish](#HAL_SSL_Establish)
    * [HAL_SSL_Read](#HAL_SSL_Read)
    * [HAL_SSL_Write](#HAL_SSL_Write)
    * [HAL_TCP_Destroy](#HAL_TCP_Destroy)
    * [HAL_TCP_Establish](#HAL_TCP_Establish)
    * [HAL_TCP_Read](#HAL_TCP_Read)
    * [HAL_TCP_Write](#HAL_TCP_Write)
    * [HAL_Fopen](#HAL_Fopen)
    * [HAL_Fread](#HAL_Fread)
    * [HAL_Fwrite](#HAL_Fwrite)
    * [HAL_Fseek](#HAL_Fseek)
    * [HAL_Ftell](#HAL_Ftell)
    * [HAL_Fclose](#HAL_Fclose)

# <a name="HTTP2相关HAL接口详解">HTTP2相关HAL接口详解</a>

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
            _IN_ uint32_t ca_crt_len);
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
| ca_crt_len  | uint32_t    | 输入    | 证书字节长度

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
| 值              | 说明
|-----------------|-----------------------------------------
| (uint_ptr)(-1)  | TCP连接建立失败
| 其它值(包括0)   | TCP连接建立成功, 返回对应的连接句柄

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

## <a name="HAL_Fopen">HAL_Fopen</a>

原型
---
```
void *HAL_Fopen(const char *path, const char *mode)
```

接口说明
---
指定文件路径及模式打开一个文件，返回文件流

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------------------
| path    | char *          | 输入    | 文件路径
| mode    | const char *    | 输入    | 打开文件的方式，与c标准fopen的参数兼容


返回值说明
---
| 值      | 说明
|---------|---------------------
| NULL    | 打开失败
| 非空    | 成功，返回文件流

-----
## <a name="HAL_Fread">HAL_Fread</a>

原型
---
```
uint32_t HAL_Fread(void * buff,uint32_t size, uint32_t count, void *stream)
```

接口说明
---
从文件流中读数据，最多读取count个项，每个项size个字节

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-----------------
| buff    | void *      | 输入    | 接收缓存
| size    | uint32_t    | 输入    | 数据块字节数
| count   | uint32_t    | 输入    | 数据块数量
| stream  | void *      | 输入    | 文件流
返回值说明
---
| 值          | 说明
|-------------|-------------
| == count    | 成功
| != count    | 操作失败

-----

## <a name="HAL_Fwrite">HAL_Fwrite</a>

原型
---
```
uint32_t HAL_Fwrite(const void * ptr, uint32_t size, uint32_t count, void * stream)
```

接口说明
---
从文件流中读数据，最多读取count个项，每个项size个字节

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------
| ptr     | const void *    | 输入    | 写入数据指针
| size    | uint32_t        | 输入    | 数据块字节数
| count   | uint32_t        | 输入    | 数据块数量
| stream  | void *          | 输入    | 文件流
返回值说明
---
| 值          | 说明
|-------------|-------------
| == count    | 成功
| != count    | 操作失败

-----

## <a name="HAL_Fseek">HAL_Fseek</a>

原型
---
```
int HAL_Fseek(void *stream,long offset,int framewhere)
```

接口说明
---
设置文件指针stream的位置

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|-------------------------------------------------
| stream      | void *      | 输入    | 文件流
| offset      | long        | 输入    | 偏移offset（指针偏移量）个字节的位置
| framewhere  | int         | 输入    | 偏移起始位置,0:文件头；1，当前位置；2:文件尾部


返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 成功
| -1  | 操作失败

-----


## <a name="HAL_Ftell">HAL_Ftell</a>

原型
---
```
long HAL_Ftell(void *stream)
```

接口说明
---
得到文件位置指针当前位置相对于文件首的偏移字节数

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------
| stream  | void *      | 输入    | 文件流


返回值说明
---
| 值      | 说明
|---------|---------------------
| >=0     | 成功,当前偏移量
| -1      | 操作失败

-----


## <a name="HAL_Fclose">HAL_Fclose</a>

原型
---
```
int HAL_Fclose(void *stream)
```

接口说明
---
关闭指定文件流

参数说明
---
| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|---------
| stream  | void *      | 输入    | 文件流


返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 成功
| -1  | 操作失败

-----
