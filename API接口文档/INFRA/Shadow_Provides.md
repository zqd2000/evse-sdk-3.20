# <a name="目录">目录</a>
+ [设备影子API接口详解](#设备影子API接口详解)
    * [IOT_Shadow_Construct](#IOT_Shadow_Construct)
    * [IOT_Shadow_Destroy](#IOT_Shadow_Destroy)
    * [IOT_Shadow_Yield](#IOT_Shadow_Yield)
    * [IOT_Shadow_RegisterAttribute](#IOT_Shadow_RegisterAttribute)
    * [IOT_Shadow_DeleteAttribute](#IOT_Shadow_DeleteAttribute)
    * [IOT_Shadow_PushFormat_Init](#IOT_Shadow_PushFormat_Init)
    * [IOT_Shadow_PushFormat_Add](#IOT_Shadow_PushFormat_Add)
    * [IOT_Shadow_PushFormat_Finalize](#IOT_Shadow_PushFormat_Finalize)
    * [IOT_Shadow_Push](#IOT_Shadow_Push)
    * [IOT_Shadow_Push_Async](#IOT_Shadow_Push_Async)
    * [IOT_Shadow_Pull](#IOT_Shadow_Pull)

# <a name="设备影子API接口详解">设备影子API接口详解</a>

## <a name="IOT_Shadow_Construct">IOT_Shadow_Construct</a>

原型
---
```
void *IOT_Shadow_Construct(iotx_shadow_para_pt pparams);
```

接口说明
---
连接云端并创建设备影子

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-------------------------
| pparams     | iotx_shadow_para_pt     | 输入    | shadow模块初始化参数

返回值说明
---
| 值      | 说明
|---------|-------------
| NULL    | 失败
| 非NULL  | shadow句柄

-----

## <a name="IOT_Shadow_Destroy">IOT_Shadow_Destroy</a>

原型
---
```
iotx_err_t IOT_Shadow_Destroy(void *handle);
```

接口说明
---
断开网络连接, 销毁shadow模块所有资源

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | shadow句柄

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_Yield">IOT_Shadow_Yield</a>

原型
---
```
void IOT_Shadow_Yield(void *handle, uint32_t timeout_ms);
```

接口说明
---
从网络上获取报文, 需要用户周期性调用

参数说明
---

| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------
| handle      | void *      | 输入    | shadow句柄
| timeout     | uint32_t    | 输入    | 尝试从网络上获取报文的超时时间

返回值说明
---
无返回值

-----

## <a name="IOT_Shadow_RegisterAttribute">IOT_Shadow_RegisterAttribute</a>

原型
---
```
iotx_err_t IOT_Shadow_RegisterAttribute(void *handle, iotx_shadow_attr_pt pattr);
```

接口说明
---
该接口用于注册TSL中特定属性ID的回调函数, 当收到对该属性的操作时, 触发相关的回调函数

参数说明
---

| 参数    | 数据类型                | 方向    | 说明
|---------|-------------------------|---------|-----------------------------
| handle  | void *                  | 输入    | shadow句柄
| pattr   | iotx_shadow_attr_pt     | 输入    | 需要注册的属性的相关信息

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_DeleteAttribute">IOT_Shadow_DeleteAttribute</a>

原型
---
```
iotx_err_t IOT_Shadow_DeleteAttribute(void *handle, iotx_shadow_attr_pt pattr);
```

接口说明
---
该接口用于删除设备影子中的属性

参数说明
---

| 参数    | 数据类型                | 方向    | 说明
|---------|-------------------------|---------|-----------------------------
| handle  | void *                  | 输入    | shadow句柄
| pattr   | iotx_shadow_attr_pt     | 输入    | 需要删除的属性的相关信息

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_PushFormat_Init">IOT_Shadow_PushFormat_Init</a>

原型
---
```
iotx_err_t IOT_Shadow_PushFormat_Init(void *pshadow,
                                      format_data_pt pformat,
                                      char *buf,
                                      uint16_t size);
```

接口说明
---
在上报影子相关信息前, 初始化消息句柄

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------
| handle      | void *          | 输入    | shadow句柄
| pformat     | format_data_pt  | 输入    | 需要初始化的消息句柄
| buf         | char *          | 输入    | 用于存放消息的buffer
| size        | uint16_t        | 输入    | `buf`的长度

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_PushFormat_Add">IOT_Shadow_PushFormat_Add</a>

原型
---
```
iotx_err_t IOT_Shadow_PushFormat_Add(void *pshadow,
                                     format_data_pt pformat,
                                     iotx_shadow_attr_pt pattr)
```

接口说明
---
在使用`IOT_Shadow_PushFormat_Init`初始化消息句柄后, 向消息句柄中添加需要上报的设备影子信息

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------
| pshadow     | void *                  | 输入    | shadow句柄
| pformat     | format_data_pt          | 输入    | 需要初始化的消息句柄
| pattr       | iotx_shadow_attr_pt     | 输入    | 需要加入消息句柄的影子信息

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_PushFormat_Finalize">IOT_Shadow_PushFormat_Finalize</a>

原型
---
```
iotx_err_t IOT_Shadow_PushFormat_Finalize(void *pshadow, format_data_pt pformat);
```

接口说明
---
当需要添加到消息句柄的影子信息添加完成后, 调用此函数封装消息句柄, 生成最终上报消息

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------
| pshadow     | void *          | 输入    | shadow句柄
| pformat     | format_data_pt  | 输入    | 需要完成封装的消息句柄

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_Push">IOT_Shadow_Push</a>

原型
---
```
iotx_err_t IOT_Shadow_Push(void *handle, char *data, uint32_t data_len, uint16_t timeout_s);
```

接口说明
---
该接口为同步接口, 用于向云端发送消息操作设备影子

参数说明
---

| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------
| handle      | void *      | 输入    | shadow句柄
| data        | char *      | 输入    | 需要向云端发送的消息Payload
| data_len    | uint32_t    | 输入    | `data`的长度

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----

## <a name="IOT_Shadow_Push_Async">IOT_Shadow_Push_Async</a>

原型
---
```
int IOT_Shadow_Push_Async(void *handle,
                            char *data,
                            size_t data_len,
                            uint16_t timeout_s,
                            iotx_push_cb_fpt cb_fpt,
                            void *pcontext);
```

接口说明
---
该接口为异步接口, 用于向云端发送消息操作设备影子

参数说明
---

| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|---------------------------------------------------------
| handle      | void *              | 输入    | shadow句柄
| data        | char *              | 输入    | 需要向云端发送的消息Payload
| data_len    | uint32_t            | 输入    | `data`的长度
| timeout_s   | uint16_t            | 输入    | 等待消息应答的超时时间
| cb_fpt      | iotx_push_cb_fpt    | 输入    | 当收到消息应答时触发的回调函数
| pcontext    | void *              | 输入    | 用户Context, 当收到消息应答时通过回调函数送回给用户

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="IOT_Shadow_Pull">IOT_Shadow_Pull</a>

原型
---
```
iotx_err_t IOT_Shadow_Pull(void *handle);
```

接口说明
---
该接口用于从云端获取设备影子

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | shadow句柄

返回值说明
---
详见`include/exports/iot_export_errno.h`

-----
