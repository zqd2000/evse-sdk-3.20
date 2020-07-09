# <a name="目录">目录</a>
+ [第七章 API说明](#第七章 API说明)
    * [7.1 API接口列表](#7.1 API接口列表)
        - [基础API](#基础API)
        - [MQTT功能API](#MQTT功能API)
        - [OTA功能API](#OTA功能API)
        - [CoAP功能API](#CoAP功能API)
        - [HTTP功能API](#HTTP功能API)
        - [设备影子API](#设备影子API)
        - [物模型管理API](#物模型管理API)
    * [7.2 API接口清单](#7.2 API接口清单)
        - [基础版API清单](#基础版API清单)
    * [7.3 基础版API接口详解](#7.3 基础版API接口详解)
        - [IOT_OpenLog](#IOT_OpenLog)
        - [IOT_CloseLog](#IOT_CloseLog)
        - [IOT_SetLogLevel](#IOT_SetLogLevel)
        - [IOT_DumpMemoryStats](#IOT_DumpMemoryStats)
        - [IOT_SetupConnInfo](#IOT_SetupConnInfo)
        - [IOT_Ioctl](#IOT_Ioctl)
        - [IOT_CoAP_Init](#IOT_CoAP_Init)
        - [IOT_CoAP_Deinit](#IOT_CoAP_Deinit)
        - [IOT_CoAP_DeviceNameAuth](#IOT_CoAP_DeviceNameAuth)
        - [IOT_CoAP_Yield](#IOT_CoAP_Yield)
        - [IOT_CoAP_SendMessage](#IOT_CoAP_SendMessage)
        - [IOT_CoAP_GetMessagePayload](#IOT_CoAP_GetMessagePayload)
        - [IOT_CoAP_GetMessageCode](#IOT_CoAP_GetMessageCode)
        - [IOT_HTTP_Init](#IOT_HTTP_Init)
        - [IOT_HTTP_DeInit](#IOT_HTTP_DeInit)
        - [IOT_HTTP_DeviceNameAuth](#IOT_HTTP_DeviceNameAuth)
        - [IOT_HTTP_SendMessage](#IOT_HTTP_SendMessage)
        - [IOT_HTTP_Disconnect](#IOT_HTTP_Disconnect)
        - [IOT_MQTT_Construct](#IOT_MQTT_Construct)
        - [IOT_MQTT_Destroy](#IOT_MQTT_Destroy)
        - [IOT_MQTT_Yield](#IOT_MQTT_Yield)
        - [IOT_MQTT_LogPost](#IOT_MQTT_LogPost)
        - [IOT_MQTT_CheckStateNormal](#IOT_MQTT_CheckStateNormal)
        - [IOT_MQTT_Subscribe](#IOT_MQTT_Subscribe)
        - [IOT_MQTT_Subscribe_Sync](#IOT_MQTT_Subscribe_Sync)
        - [IOT_MQTT_Unsubscribe](#IOT_MQTT_Unsubscribe)
        - [IOT_MQTT_Publish](#IOT_MQTT_Publish)
        - [IOT_OTA_Init](#IOT_OTA_Init)
        - [IOT_OTA_Deinit](#IOT_OTA_Deinit)
        - [IOT_OTA_ReportVersion](#IOT_OTA_ReportVersion)
        - [IOT_OTA_ReportProgress](#IOT_OTA_ReportProgress)
        - [IOT_OTA_IsFetching](#IOT_OTA_IsFetching)
        - [IOT_OTA_IsFetchFinish](#IOT_OTA_IsFetchFinish)
        - [IOT_OTA_FetchYield](#IOT_OTA_FetchYield)
        - [IOT_OTA_Ioctl](#IOT_OTA_Ioctl)
        - [IOT_OTA_GetLastError](#IOT_OTA_GetLastError)
        - [IOT_Shadow_Construct](#IOT_Shadow_Construct)
        - [IOT_Shadow_Destroy](#IOT_Shadow_Destroy)
        - [IOT_Shadow_Yield](#IOT_Shadow_Yield)
        - [IOT_Shadow_RegisterAttribute](#IOT_Shadow_RegisterAttribute)
        - [IOT_Shadow_DeleteAttribute](#IOT_Shadow_DeleteAttribute)
        - [IOT_Shadow_PushFormat_Init](#IOT_Shadow_PushFormat_Init)
        - [IOT_Shadow_PushFormat_Add](#IOT_Shadow_PushFormat_Add)
        - [IOT_Shadow_PushFormat_Finalize](#IOT_Shadow_PushFormat_Finalize)
        - [IOT_Shadow_Push](#IOT_Shadow_Push)
        - [IOT_Shadow_Push_Async](#IOT_Shadow_Push_Async)
        - [IOT_Shadow_Pull](#IOT_Shadow_Pull)
        - [IOT_Gateway_Generate_Message_ID](#IOT_Gateway_Generate_Message_ID)
        - [IOT_Gateway_Construct](#IOT_Gateway_Construct)
        - [IOT_Gateway_Destroy](#IOT_Gateway_Destroy)
        - [IOT_Subdevice_Register](#IOT_Subdevice_Register)
        - [IOT_Subdevice_Unregister](#IOT_Subdevice_Unregister)
        - [IOT_Subdevice_Login](#IOT_Subdevice_Login)
        - [IOT_Subdevice_Logout](#IOT_Subdevice_Logout)
        - [IOT_Gateway_Get_TOPO](#IOT_Gateway_Get_TOPO)
        - [IOT_Gateway_Get_Config](#IOT_Gateway_Get_Config)
        - [IOT_Gateway_Publish_Found_List](#IOT_Gateway_Publish_Found_List)
        - [IOT_Gateway_Yield](#IOT_Gateway_Yield)
        - [IOT_Gateway_Subscribe](#IOT_Gateway_Subscribe)
        - [IOT_Gateway_Unsubscribe](#IOT_Gateway_Unsubscribe)
        - [IOT_Gateway_Publish](#IOT_Gateway_Publish)
        - [IOT_Gateway_RRPC_Register](#IOT_Gateway_RRPC_Register)
        - [IOT_Gateway_RRPC_Response](#IOT_Gateway_RRPC_Response)
    * [7.3 高级版(新版)API接口详解](#7.3 高级版(新版)API接口详解)
        - [IOT_Linkkit_Open](#IOT_Linkkit_Open)
        - [IOT_Linkkit_Connect](#IOT_Linkkit_Connect)
        - [IOT_Linkkit_Yield](#IOT_Linkkit_Yield)
        - [IOT_Linkkit_Close](#IOT_Linkkit_Close)
        - [IOT_Linkkit_TriggerEvent](#IOT_Linkkit_TriggerEvent)
        - [IOT_Linkkit_Report](#IOT_Linkkit_Report)
        - [IOT_Linkkit_Query](#IOT_Linkkit_Query)
        - [IOT_RegisterCallback](#IOT_RegisterCallback)
        - [ITE_CONNECT_SUCC事件](#ITE_CONNECT_SUCC事件)
        - [ITE_DISCONNECTED事件](#ITE_DISCONNECTED事件)
        - [ITE_RAWDATA_ARRIVED事件](#ITE_RAWDATA_ARRIVED事件)
        - [ITE_SERVICE_REQUEST事件](#ITE_SERVICE_REQUEST事件)
        - [ITE_PROPERTY_SET事件](#ITE_PROPERTY_SET事件)
        - [ITE_PROPERTY_GET事件](#ITE_PROPERTY_GET事件)
        - [ITE_REPORT_REPLY事件](#ITE_REPORT_REPLY事件)
        - [ITE_TRIGGER_EVENT_REPLY事件](#ITE_TRIGGER_EVENT_REPLY事件)
        - [ITE_TIMESTAMP_REPLY事件](#ITE_TIMESTAMP_REPLY事件)
        - [ITE_TOPOLIST_REPLY事件](#ITE_TOPOLIST_REPLY事件)
        - [ITE_PERMIT_JOIN事件](#ITE_PERMIT_JOIN事件)
        - [ITE_INITIALIZE_COMPLETED事件](#ITE_INITIALIZE_COMPLETED事件)
        - [ITE_FOTA事件](#ITE_FOTA事件)
        - [ITE_COTA事件](#ITE_COTA事件)
        - [IOT_Ioctl](#IOT_Ioctl)
    * [7.4 高级版(旧版)单品API详解](#7.4 高级版(旧版)单品API详解)
        - [linkkit_answer_service](#linkkit_answer_service)
        - [linkkit_cota_init](#linkkit_cota_init)
        - [linkkit_dispatch](#linkkit_dispatch)
        - [linkkit_end](#linkkit_end)
        - [linkkit_fota_init](#linkkit_fota_init)
        - [linkkit_get_value](#linkkit_get_value)
        - [linkkit_invoke_cota_get_config](#linkkit_invoke_cota_get_config)
        - [linkkit_invoke_cota_service](#linkkit_invoke_cota_service)
        - [linkkit_invoke_fota_service](#linkkit_invoke_fota_service)
        - [linkkit_invoke_raw_service](#linkkit_invoke_raw_service)
        - [linkkit_is_end](#linkkit_is_end)
        - [linkkit_is_try_leave](#linkkit_is_try_leave)
        - [linkkit_post_property](#linkkit_post_property)
        - [linkkit_set_opt](#linkkit_set_opt)
        - [linkkit_set_tsl](#linkkit_set_tsl)
        - [linkkit_set_value](#linkkit_set_value)
        - [linkkit_start](#linkkit_start)
        - [linkkit_trigger_event](#linkkit_trigger_event)
        - [linkkit_trigger_extended_info_operate](#linkkit_trigger_extended_info_operate)
        - [linkkit_try_leave](#linkkit_try_leave)
        - [linkkit_yield](#linkkit_yield)
    * [7.5 高级版(旧版)网关API详解](#7.5 高级版(旧版)网关API详解)
        - [linkkit_gateway_delete_extinfos](#linkkit_gateway_delete_extinfos)
        - [linkkit_gateway_exit](#linkkit_gateway_exit)
        - [linkkit_gateway_fota_init](#linkkit_gateway_fota_init)
        - [linkkit_gateway_get_default_params](#linkkit_gateway_get_default_params)
        - [linkkit_gateway_get_devinfo](#linkkit_gateway_get_devinfo)
        - [linkkit_gateway_get_num_devices](#linkkit_gateway_get_num_devices)
        - [linkkit_gateway_init](#linkkit_gateway_init)
        - [linkkit_gateway_invoke_fota_service](#linkkit_gateway_invoke_fota_service)
        - [linkkit_gateway_post_extinfos](#linkkit_gateway_post_extinfos)
        - [linkkit_gateway_post_property_json](#linkkit_gateway_post_property_json)
        - [linkkit_gateway_post_property_json_sync](#linkkit_gateway_post_property_json_sync)
        - [linkkit_gateway_post_rawdata](#linkkit_gateway_post_rawdata)
        - [linkkit_gateway_set_event_callback](#linkkit_gateway_set_event_callback)
        - [linkkit_gateway_setopt](#linkkit_gateway_setopt)
        - [linkkit_gateway_start](#linkkit_gateway_start)
        - [linkkit_gateway_stop](#linkkit_gateway_stop)
        - [linkkit_gateway_subdev_create](#linkkit_gateway_subdev_create)
        - [linkkit_gateway_subdev_destroy](#linkkit_gateway_subdev_destroy)
        - [linkkit_gateway_subdev_login](#linkkit_gateway_subdev_login)
        - [linkkit_gateway_subdev_logout](#linkkit_gateway_subdev_logout)
        - [linkkit_gateway_subdev_register](#linkkit_gateway_subdev_register)
        - [linkkit_gateway_subdev_unregister](#linkkit_gateway_subdev_unregister)
        - [linkkit_gateway_trigger_event_json](#linkkit_gateway_trigger_event_json)
        - [linkkit_gateway_trigger_event_json_sync](#linkkit_gateway_trigger_event_json_sync)


# <a name="第七章 API说明">第七章 API说明</a>

> 本节说明 C-SDK 向客户提供的功能和对应的API, 用于让客户编写业务逻辑. 另外模组商/芯片商封装AT命令时, 也是基于这些API的
>
>> 更加准确详细和权威的描述, 以代码 `include/iot_export.h`, 以及 `include/exports/*.h` 中的注释为准
>>
>> 如何使用这些API编写应用逻辑, 以代码 `examples/*/*.c` 的示例程序为准

## <a name="7.1 API接口列表">7.1 API接口列表</a>

### <a name="基础API">基础API</a>

| 函数名                                          | 说明
|-------------------------------------------------|---------------------------------------------------------------------
| [IOT_OpenLog](#IOT_OpenLog)                     | 开始打印日志信息(log), 接受一个const char *为入参, 表示模块名字
| [IOT_CloseLog](#IOT_CloseLog)                   | 停止打印日志信息(log), 入参为空
| [IOT_SetLogLevel](#IOT_SetLogLevel)             | 设置打印的日志等级, 接受入参从1到5, 数字越大, 打印越详细
| [IOT_DumpMemoryStats](#IOT_DumpMemoryStats)     | 调试函数, 打印内存的使用统计情况, 入参为1-5, 数字越大, 打印越详细
| [IOT_Ioctl](#IOT_Ioctl)                         | 设置SDK运行时可配置选项, 详情见API注释

用户可通过`IOT_Ioctl()`配置是否使用一型一密功能详细内容第五章

### <a name="MQTT功能API">MQTT功能API</a>

| 函数名                                                      | 说明
|-------------------------------------------------------------|---------------------------------------------------------
| [IOT_SetupConnInfo](#IOT_SetupConnInfo)                     | MQTT连接前的准备, 基于`DeviceName + DeviceSecret + ProductKey`产生MQTT连接的用户名和密码等
| [IOT_MQTT_CheckStateNormal](#IOT_MQTT_CheckStateNormal)     | MQTT连接后, 调用此函数检查长连接是否正常
| [IOT_MQTT_Construct](#IOT_MQTT_Construct)                   | MQTT实例的构造函数, 入参为`iotx_mqtt_param_t`结构体, 连接MQTT服务器, 并返回被创建句柄
| [IOT_MQTT_Destroy](#IOT_MQTT_Destroy)                       | MQTT实例的摧毁函数, 入参为 [IOT_MQTT_Construct](#IOT_MQTT_Construct) 创建的句柄
| [IOT_MQTT_Publish](#IOT_MQTT_Publish)                       | MQTT会话阶段, 组织一个完整的`MQTT Publish`报文, 向服务端发送消息发布报文
| [IOT_MQTT_Subscribe](#IOT_MQTT_Subscribe)                   | MQTT会话阶段, 组织一个完整的`MQTT Subscribe`报文, 向服务端发送订阅请求
| [IOT_MQTT_Unsubscribe](#IOT_MQTT_Unsubscribe)               | MQTT会话阶段, 组织一个完整的`MQTT UnSubscribe`报文, 向服务端发送取消订阅请求
| [IOT_MQTT_Yield](#IOT_MQTT_Yield)                           | MQTT会话阶段, MQTT主循环函数, 内含了心跳的维持, 服务器下行报文的收取等

> 现对照 `examples/mqtt/mqtt-example.c` 例程分步骤讲解如何使用这几个API实现MQTT上云功能

1. 初始化阶段, 如果用户需要配置使用海外站点或者使用动态注册功能, 可先使用`IOT_Ioctl()`完成配置
---
```
    /* Choose Login Server */
    int domain_type = IOTX_CLOUD_DOMAIN_SH;
    IOT_Ioctl(IOTX_IOCTL_SET_DOMAIN, (void *)&domain_type);

    /* Choose Login  Method */
    int dynamic_register = 0;
    IOT_Ioctl(IOTX_IOCTL_SET_DYNAMIC_REGISTER, (void *)&dynamic_register);
```

2. MQTT会话建立前的准备, 导入设备三元组, 初始化连接信息
---
```
    iotx_conn_info_pt pconn_info;

    HAL_GetProductKey(__product_key);
    HAL_GetDeviceName(__device_name);
    HAL_GetDeviceSecret(__device_secret);

    /* Device AUTH */
    if (0 != IOT_SetupConnInfo(__product_key, __device_name, __device_secret, (void **)&pconn_info)) {
        EXAMPLE_TRACE("AUTH request failed!");
        rc = -1;
        goto do_exit;
    }
```
3. 配置MQTT参数, 构建MQTT连接会话, 与云端服务器建立连接
---
```
    void *pclient;
    iotx_mqtt_param_t mqtt_params;

    /* Initialize MQTT parameter */
    memset(&mqtt_params, 0x0, sizeof(mqtt_params));

    mqtt_params.port = pconn_info->port;
    mqtt_params.host = pconn_info->host_name;
    mqtt_params.client_id = pconn_info->client_id;
    mqtt_params.username = pconn_info->username;
    mqtt_params.password = pconn_info->password;
    mqtt_params.pub_key = pconn_info->pub_key;

    mqtt_params.request_timeout_ms = 2000;
    mqtt_params.clean_session = 0;
    mqtt_params.keepalive_interval_ms = 60000;
    mqtt_params.pread_buf = msg_readbuf;
    mqtt_params.read_buf_size = MQTT_MSGLEN;
    mqtt_params.pwrite_buf = msg_buf;
    mqtt_params.write_buf_size = MQTT_MSGLEN;

    mqtt_params.handle_event.h_fp = event_handle;
    mqtt_params.handle_event.pcontext = NULL;

    /* Construct a MQTT client with specify parameter */
    pclient = IOT_MQTT_Construct(&mqtt_params);
    if (NULL == pclient) {
        EXAMPLE_TRACE("MQTT construct failed");
        rc = -1;
        goto do_exit;
    }
```

4. MQTT会话建立成功后, 用户便可以根据业务需要对指定Topic进行发布, 订阅或取消订阅了
---
```
    #define TOPIC_DATA              "/"PRODUCT_KEY"/"DEVICE_NAME"/data"
    iotx_mqtt_topic_info_t topic_msg;

    /* Initialize topic information */
    memset(&topic_msg, 0x0, sizeof(iotx_mqtt_topic_info_t));
    strcpy(msg_pub, "update: hello! start!");

    topic_msg.qos = IOTX_MQTT_QOS1;
    topic_msg.retain = 0;
    topic_msg.dup = 0;
    topic_msg.payload = (void *)msg_pub;
    topic_msg.payload_len = strlen(msg_pub);

    /* 发布指定的Topic */
    rc = IOT_MQTT_Publish(pclient, TOPIC_UPDATE, &topic_msg);
    if (rc < 0) {
        IOT_MQTT_Destroy(&pclient);
        EXAMPLE_TRACE("error occur when publish");
        rc = -1;
        goto do_exit;
    }

    /* 订阅指定的Topic, 同时注册对应回调函数用于处理云端发布的消息 */
    rc = IOT_MQTT_Subscribe(pclient, TOPIC_DATA, IOTX_MQTT_QOS1, _demo_message_arrive, NULL);
    if (rc < 0) {
        IOT_MQTT_Destroy(&pclient);
        EXAMPLE_TRACE("IOT_MQTT_Subscribe() failed, rc = %d", rc);
        rc = -1;
        goto do_exit;
    }

    /* 取消订阅指定的Topic */
    IOT_MQTT_Unsubscribe(pclient, TOPIC_DATA);
```

5. 用户会发现每一个向服务器的上行操作(包括发布, 订阅和取消订阅等行为)后都会紧接一个`IOT_MQTT_Yield()`, 此函数主要用于处理服务器下行报文的收取和解析, 同时内含了心跳的维持. 在while()循环中必须包含次函数
---

6. 最终用户可以通过`IOT_MQTT_Destroy()`结束会话
---
```
    IOT_MQTT_Destroy(&pclient);
```

### <a name="OTA功能API">OTA功能API</a>

| 函数名                                              | 说明
|-----------------------------------------------------|-----------------------------------------------------------------
| [IOT_OTA_Init](#IOT_OTA_Init)                       | OTA实例的构造函数, 创建一个OTA会话的句柄并返回
| [IOT_OTA_Deinit](#IOT_OTA_Deinit)                   | OTA实例的摧毁函数, 销毁所有相关的数据结构
| [IOT_OTA_Ioctl](#IOT_OTA_Ioctl)                     | OTA实例的输入输出函数, 根据不同的命令字可以设置OTA会话的属性, 或者获取OTA会话的状态
| [IOT_OTA_GetLastError](#IOT_OTA_GetLastError)       | OTA会话阶段, 若某个 IOT_OTA_XXX() 函数返回错误, 调用此接口可获得最近一次的详细错误码
| [IOT_OTA_ReportVersion](#IOT_OTA_ReportVersion)     | OTA会话阶段, 向服务端汇报当前的固件版本号
| [IOT_OTA_FetchYield](#IOT_OTA_FetchYield)           | OTA下载阶段, 在指定的`timeout`时间内, 从固件服务器下载一段固件内容, 保存在入参buffer中
| [IOT_OTA_IsFetchFinish](#IOT_OTA_IsFetchFinish)     | OTA下载阶段, 判断迭代调用 [IOT_OTA_FetchYield](#IOT_OTA_FetchYield) 是否已经下载完所有的固件内容
| [IOT_OTA_IsFetching](#IOT_OTA_IsFetching)           | OTA下载阶段, 判断固件下载是否仍在进行中, 尚未完成全部固件内容的下载
| [IOT_OTA_ReportProgress](#IOT_OTA_ReportProgress)   | 可选API, OTA下载阶段, 调用此函数向服务端汇报已经下载了全部固件内容的百分之多少

更多OTA相关功能说明可查看[OTA服务](https://living.aliyun.com/doc#ysuxe6.html)页面

### <a name="CoAP功能API">CoAP功能API</a>

| 函数名                                                      | 说明
|-------------------------------------------------------------|---------------------------------------------------------
| [IOT_CoAP_Init](#IOT_CoAP_Init)                             | CoAP实例的构造函数, 入参为`iotx_coap_config_t`结构体, 返回创建的CoAP会话句柄
| [IOT_CoAP_Deinit](#IOT_CoAP_Deinit)                         | CoAP实例的摧毁函数, 入参为 [IOT_CoAP_Init](#IOT_CoAP_Init) 所创建的句柄
| [IOT_CoAP_DeviceNameAuth](#IOT_CoAP_DeviceNameAuth)         | 基于控制台申请的`DeviceName`, `DeviceSecret`, `ProductKey`做设备认证
| [IOT_CoAP_GetMessageCode](#IOT_CoAP_GetMessageCode)         | CoAP会话阶段, 从服务器的`CoAP Response`报文中获取`Respond Code`
| [IOT_CoAP_GetMessagePayload](#IOT_CoAP_GetMessagePayload)   | CoAP会话阶段, 从服务器的`CoAP Response`报文中获取报文负载
| [IOT_CoAP_SendMessage](#IOT_CoAP_SendMessage)               | CoAP会话阶段, 连接已成功建立后调用, 组织一个完整的CoAP报文向服务器发送
| [IOT_CoAP_Yield](#IOT_CoAP_Yield)                           | CoAP会话阶段, 连接已成功建立后调用, 检查和收取服务器对`CoAP Request`的回复报文

### <a name="HTTP功能API">HTTP功能API</a>

| 函数名                                                  | 说明
|---------------------------------------------------------|-------------------------------------------------------------
| [IOT_HTTP_Init](#IOT_HTTP_Init)                         | Https实例的构造函数, 创建一个HTTP会话的句柄并返回
| [IOT_HTTP_DeInit](#IOT_HTTP_DeInit)                     | Https实例的摧毁函数, 销毁所有相关的数据结构
| [IOT_HTTP_DeviceNameAuth](#IOT_HTTP_DeviceNameAuth)     | 基于控制台申请的`DeviceName`, `DeviceSecret`, `ProductKey`做设备认证
| [IOT_HTTP_SendMessage](#IOT_HTTP_SendMessage)           | Https会话阶段, 组织一个完整的HTTP报文向服务器发送,并同步获取HTTP回复报文
| [IOT_HTTP_Disconnect](#IOT_HTTP_Disconnect)             | Https会话阶段, 关闭HTTP层面的连接, 但是仍然保持TLS层面的连接

### <a name="设备影子API">设备影子API</a>

| 函数名                                                              | 说明
|---------------------------------------------------------------------|-------------------------------------------------
| [IOT_Shadow_Construct](#IOT_Shadow_Construct)                       | 建立一个设备影子的MQTT连接, 并返回被创建的会话句柄
| [IOT_Shadow_Destroy](#IOT_Shadow_Destroy)                           | 摧毁一个设备影子的MQTT连接, 销毁所有相关的数据结构, 释放内存, 断开连接
| [IOT_Shadow_Pull](#IOT_Shadow_Pull)                                 | 把服务器端被缓存的JSON数据下拉到本地, 更新本地的数据属性
| [IOT_Shadow_Push](#IOT_Shadow_Push)                                 | 把本地的数据属性上推到服务器缓存的JSON数据, 更新服务端的数据属性
| [IOT_Shadow_Push_Async](#IOT_Shadow_Push_Async)                     | 和 [IOT_Shadow_Push](#IOT_Shadow_Push) 接口类似, 但是异步的, 上推后便返回, 不等待服务端回应
| [IOT_Shadow_PushFormat_Add](#IOT_Shadow_PushFormat_Add)             | 向已创建的数据类型格式中增添成员属性
| [IOT_Shadow_PushFormat_Finalize](#IOT_Shadow_PushFormat_Finalize)   | 完成一个数据类型格式的构造过程
| [IOT_Shadow_PushFormat_Init](#IOT_Shadow_PushFormat_Init)           | 开始一个数据类型格式的构造过程
| [IOT_Shadow_RegisterAttribute](#IOT_Shadow_RegisterAttribute)       | 创建一个数据类型注册到服务端, 注册时需要`*PushFormat*()`接口创建的数据类型格式
| [IOT_Shadow_DeleteAttribute](#IOT_Shadow_DeleteAttribute)           | 删除一个已被成功注册的数据属性
| [IOT_Shadow_Yield](#IOT_Shadow_Yield)                               | MQTT的主循环函数, 调用后接受服务端的下推消息, 更新本地的数据属性

### <a name="物模型管理API">物模型管理API</a>
> 物模型管理功能是指SDK能够使能IoT设备接受云端控制台或者手机公版app的控制, 进行属性/事件/服务维度的设置和监控, 在本文的其它地方, 有时也称为"高级版"

| 函数名                                                  | 说明
|---------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------
| [IOT_Linkkit_Open](#IOT_Linkkit_Open)                   | 创建本地资源, 在进行网络报文交互之前, 必须先调用此接口, 得到一个会话的句柄
| [IOT_Linkkit_Connect](#IOT_Linkkit_Connect)             | 对主设备/网关来说, 将会建立设备与云端的通信. 对于子设备来说, 将向云端注册该子设备(若需要), 并添加主子设备拓扑关系
| [IOT_Linkkit_Yield](#IOT_Linkkit_Yield)                 | 若SDK占有独立线程, 该函数内容为空, 否则表示将CPU交给SDK让其接收网络报文并将消息分发到用户的回调函数中
| [IOT_Linkkit_Close](#IOT_Linkkit_Close)                 | 若入参中的会话句柄为主设备/网关, 则关闭网络连接并释放SDK为该会话所占用的所有资源
| [IOT_Linkkit_TriggerEvent](#IOT_Linkkit_TriggerEvent)   | 向云端发送**事件报文**, 如错误码, 异常告警等
| [IOT_Linkkit_Report](#IOT_Linkkit_Report)               | 向云端发送**没有云端业务数据下发的上行报文**, 包括属性值/设备标签/二进制透传数据/子设备管理等各种报文
| [IOT_Linkkit_Query](#IOT_Linkkit_Query)                 | 向云端发送**存在云端业务数据下发的查询报文**, 包括OTA状态查询/OTA固件下载/子设备拓扑查询/NTP时间查询等各种报文

| 函数名                                          | 说明
|-------------------------------------------------|---------------------------------------------------------------------------------------------
| [IOT_RegisterCallback](#IOT_RegisterCallback)   | 对SDK注册事件回调函数, 如云端连接成功/失败, 有属性设置/服务请求到达, 子设备管理报文答复等
| [IOT_Ioctl](#IOT_Ioctl)                         | 对SDK进行各种参数运行时设置和获取, 以及运行状态的信息获取等, 实参可以是任何数据类型

## <a name="7.2 API接口清单">7.2 API接口清单</a>
如下列出当前SDK代码提供的所有面向用户的API函数:

### <a name="基础版API清单">基础版API清单</a>

    $ cd include
    $ grep -o "IOT_[A-Z][_a-zA-Z]*[^_]\> *(" iot_export.h exports/*.h|sed 's!.*:\(.*\)(!\1!'|cat -n

     1  IOT_RegisterCallback
     2  IOT_SetLogLevel
     3  IOT_DumpMemoryStats
     4  IOT_SetupConnInfo
     5  IOT_Ioctl
     6  IOT_CoAP_Init
     7  IOT_CoAP_Deinit
     8  IOT_CoAP_DeviceNameAuth
     9  IOT_CoAP_Yield
    10  IOT_CoAP_SendMessage
    11  IOT_CoAP_GetMessagePayload
    12  IOT_CoAP_GetMessageCode
    13  IOT_OpenLog
    14  IOT_CloseLog
    15  IOT_SetLogLevel
    16  IOT_HTTP_Init
    17  IOT_HTTP_DeInit
    18  IOT_HTTP_DeviceNameAuth
    19  IOT_HTTP_SendMessage
    20  IOT_HTTP_Disconnect
    21  IOT_Linkkit_Open
    22  IOT_Linkkit_Connect
    23  IOT_Linkkit_Yield
    24  IOT_Linkkit_Close
    25  IOT_Linkkit_Report
    26  IOT_Linkkit_Query
    27  IOT_Linkkit_TriggerEvent
    28  IOT_MQTT_Construct
    29  IOT_MQTT_Destroy
    30  IOT_MQTT_Yield
    31  IOT_MQTT_LogPost
    32  IOT_MQTT_CheckStateNormal
    33  IOT_MQTT_Subscribe
    34  IOT_MQTT_Subscribe_Sync
    35  IOT_MQTT_Unsubscribe
    36  IOT_MQTT_Publish
    37  IOT_MQTT_Publish_Simple
    38  IOT_OTA_Init
    39  IOT_OTA_Deinit
    40  IOT_OTA_ReportVersion
    41  IOT_OTA_ReportProgress
    42  IOT_OTA_IsFetching
    43  IOT_OTA_IsFetchFinish
    44  IOT_OTA_FetchYield
    45  IOT_OTA_Ioctl
    46  IOT_OTA_GetLastError
    47  IOT_Shadow_Construct
    48  IOT_Shadow_Destroy
    49  IOT_Shadow_Yield
    50  IOT_Shadow_RegisterAttribute
    51  IOT_Shadow_DeleteAttribute
    52  IOT_Shadow_PushFormat_Init
    53  IOT_Shadow_PushFormat_Add
    54  IOT_Shadow_PushFormat_Finalize
    55  IOT_Shadow_Push
    56  IOT_Shadow_Push_Async
    57  IOT_Shadow_Pull

## <a name="7.3 基础版API接口详解">7.3 基础版API接口详解</a>
### <a name="IOT_OpenLog">IOT_OpenLog</a>

原型
---
```
void IOT_OpenLog(const char *ident);
```

接口说明
---
日志系统的初始化函数, 本接口被调用后, SDK才有可能向终端打印日志文本, 但打印的文本详细程度还是由 `IOT_SetLogLevel()` 确定, 默认情况下, 无日志输出

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------------------------------
| ident   | const char *    | 输入    | 日志的标识符字符串, 例如: `IOT_OpenLog("linkkit")`

返回值说明
---
无返回值

-----

### <a name="IOT_CloseLog">IOT_CloseLog</a>

原型
---
```
void IOT_CloseLog(void);
```

接口说明
---
日志系统的销毁函数, 本接口被调用后, SDK停止向终端打印任何日志文本, 但之后可以由调用 `IOT_OpenLog()` 接口重新使能日志输出

关闭和重新使能日志系统之后, 需要重新调用 `IOT_SetLogLevel()` 接口设置日志级别, 否则日志系统虽然使能了, 也不会输出文本

参数说明
---
无参数

返回值说明
---
无返回值

-----

### <a name="IOT_SetLogLevel">IOT_SetLogLevel</a>

原型
---
```
void IOT_SetLogLevel(IOT_LogLevel level);
```

接口说明
---
日志系统的日志级别配置函数, 本接口用于设置SDK的日志显示级别, 需要在 `IOT_OpenLog()` 后被调用

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|---------------------
| level   | IOT_LogLevel    | 输入    | 需要显示的日志级别

返回值说明
---
无返回值

参数附加说明
---
```
typedef enum _IOT_LogLevel {
    IOT_LOG_EMERG = 0,
    IOT_LOG_CRIT,
    IOT_LOG_ERROR,
    IOT_LOG_WARNING,
    IOT_LOG_INFO,
    IOT_LOG_DEBUG,
} IOT_LogLevel;
```

-----

### <a name="IOT_DumpMemoryStats">IOT_DumpMemoryStats</a>

原型
---
```
void IOT_DumpMemoryStats(IOT_LogLevel level);
```

接口说明
---
该接口可显示出SDK各模块的内存使用情况, 当WITH_MEM_STATS=1时起效, 显示级别设置得越高, 显示的信息越多

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|---------------------
| level   | IOT_LogLevel    | 输入    | 需要显示的日志级别

返回值说明
---
无返回值

-----

### <a name="IOT_SetupConnInfo">IOT_SetupConnInfo</a>

原型
---
```
int IOT_SetupConnInfo(const char *product_key,
                        const char *device_name,
                        const char *device_secret,
                        void **info_ptr);
```

接口说明
---
在连接云端之前, 需要做一些认证流程, 如一型一密获取DeviceSecret或者根据当前所选认证模式向云端进行认证

该接口在SDK基础版中需要在连接云端之前由用户显式调用. 而在高级版中SDK会自动进行调用, 不需要用户显式调用

参数说明
---
| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------------------------------------------------------
| product_key     | const char *    | 输入    | 设备三元组的ProductKey
| device_name     | const char *    | 输入    | 设备三元组的DeviceName
| device_secret   | const char *    | 输入    | 设备三元组的DeviceSecret
| info_ptr        | void **         | 输出    | 该void**数据类型为iotx_conn_info_t, 在认证流程通过后, 会得到云端的相关信息, 用于建立与云端连接时使用

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
    uint16_t        port;
    char            host_name[HOST_ADDRESS_LEN + 1];
    char            client_id[CLIENT_ID_LEN + 1];
    char            username[USER_NAME_LEN + 1];
    char            password[PASSWORD_LEN + 1];
    const char     *pub_key;
} iotx_conn_info_t, *iotx_conn_info_pt;
```

-----
### <a name="IOT_Ioctl">IOT_Ioctl</a>

原型
---
```
int IOT_Ioctl(int option, void *data);
```
接口说明
---
在SDK连接云端之前, 用户可用此接口进行SDK部分参数的配置或获取, 如连接的region, 是否使用一型一密等

该接口在基础版和高级版中均适用, 需要注意的是, 该接口需要在SDK建立网络连接之前调用. 关于一型一密的

参数说明
---

| 参数    | 数据类型                | 方向        | 说明
|---------|-------------------------|-------------|-----------------------------------------------------
| option  | iotx_ioctl_option_t     | 输入        | 选择需要配置或获取的参数
| data    | void *                  | 输入/输出   | 在配置或获取参数时需要的buffer, 依据`option`而定

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOTX_IOCTL_SET_DOMAIN,              /* value(int*): iotx_cloud_domain_types_t */
    IOTX_IOCTL_GET_DOMAIN,              /* value(int*) */
    IOTX_IOCTL_SET_DYNAMIC_REGISTER,    /* value(int*): 0 - Disable Dynamic Register, 1 - Enable Dynamic Register */
    IOTX_IOCTL_GET_DYNAMIC_REGISTER     /* value(int*) */
} iotx_ioctl_option_t;
```
+ `IOTX_IOCTL_SET_DOMAIN`: 设置需要访问的的region, `data`为`int *`类型, 取值如下:
    - IOTX_CLOUD_DOMAIN_SH, 华东2(上海)
    - IOTX_CLOUD_DOMAIN_SG, 新加坡
    - IOTX_CLOUD_DOMAIN_JP, 日本(东京)
    - IOTX_CLOUD_DOMAIN_US, 美国(硅谷)
    - IOTX_CLOUD_DOMAIN_GER, 德国(法兰克福)

+ `IOTX_IOCTL_GET_DOMAIN`: 获取当前的region, `data`为`int *`类型

+ `IOTX_IOCTL_SET_DYNAMIC_REGISTER`: 设置是否需要直连设备动态注册(一型一密), `data`为`int *`类型, 取值如下:
    - 0, 不使用直连设备动态注册
    - 1, 使用直连设备动态注册

+ `IOTX_IOCTL_GET_DYNAMIC_REGISTER`: 获取当前设备注册方式, `data`为`int *`类型

-----

### <a name="IOT_CoAP_Init">IOT_CoAP_Init</a>

原型
---
```
iotx_coap_context_t *IOT_CoAP_Init(iotx_coap_config_t *p_config);
```

接口说明
---
CoAP模块初始化函数, 在使用CoAP的功能之前, 需要使用该函数进行初始化

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|---------------------
| p_config    | iotx_coap_config_t *    | 输入    | CoAP模块初始化参数

返回值说明
---
|数据类型                | 说明
|-------------------------|-------------------------
| iotx_coap_context_t *   | CoAP当前实例的Context

参数附加说明
---
```
typedef struct {
    char                  *p_url;
    int                   wait_time_ms;
    iotx_device_info_t    *p_devinfo;
    iotx_event_handle_t   event_handle; /* not supported now */
} iotx_coap_config_t;
```
+ `p_url`: 需要连接的云端服务器地址
    - 使用DTLS: `coaps://%s.iot-as-coap.cn-shanghai.aliyuncs.com:5684`, `%s` 为ProductKey
    - 使用PSK: `coap-psk://%s.iot-as-coap.cn-shanghai.aliyuncs.com:5683`, `%s` 为ProductKey

+ `wait_time_ms`: CoAP收发消息的超时时间

+ `p_devinfo`: 设备信息, 包含 Product_Key/ProductSecret/DeviceName 和 DeviceSecret

-----

### <a name="IOT_CoAP_Deinit">IOT_CoAP_Deinit</a>

原型
---
```
void IOT_CoAP_Deinit(iotx_coap_context_t **pp_context);
```

接口说明
---
CoAP反初始化函数, 断开与云端的连接并释放所有指定Context中分配的资源

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------
| pp_context  | iotx_coap_context_t **  | 输入    | 需要反初始化的CoAP Context

返回值说明
---
无返回值

-----

### <a name="IOT_CoAP_DeviceNameAuth">IOT_CoAP_DeviceNameAuth</a>

原型
---
```
int IOT_CoAP_DeviceNameAuth(iotx_coap_context_t *p_context)
```

接口说明
---
向云端发送设备认证请求, 认证通过后才能通过CoAP与云端正常通信

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------
| pp_context  | iotx_coap_context_t **  | 输入    | CoAP Context

返回值说明
---
| 值  | 说明
|-----|---------------------
| 0   | 成功
| -1  | 输入参数非法
| -2  | 内存不足
| -4  | 认证失败
| -8  | CoAP消息发送失败

-----

### <a name="IOT_CoAP_Yield">IOT_CoAP_Yield</a>

原型
---
```
int IOT_CoAP_Yield(iotx_coap_context_t *p_context)
```

接口说明
---
当CoAP连接云端后, 用于尝试从网络上接收报文

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------
| p_context   | iotx_coap_context_t *   | 输入    | CoAP Context

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_CoAP_SendMessage">IOT_CoAP_SendMessage</a>

原型
---
```
int IOT_CoAP_SendMessage(iotx_coap_context_t *p_context, char *p_path, iotx_message_t *p_message);
```

接口说明
---
当CoAP连接云端后, 用于向云端发送CoAP消息

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-------------------------
| p_context   | iotx_coap_context_t *   | 输入    | CoAP Context
| p_path      | char *                  | 输入    | 发送消息的目标资源地址
| p_message   | iotx_message_t *        | 输入    | 待发送消息

返回值说明
---

| 值  | 说明
|-----|-----------------------------
| 0   | 成功
| -1  | 输入参数非法
| -5  | 设备尚未认证成功
| -7  | 待发送消息的payload过长

-----

参数附加说明
---
```
typedef struct {
    unsigned char            *p_payload;
    unsigned short           payload_len;
    iotx_content_type_t      content_type;
    iotx_msg_type_t          msg_type;
    void                     *user_data;
    iotx_response_callback_t resp_callback;
} iotx_message_t;
```

+ `p_payload`: 需要发送的数据内容
+ `payload_len`: 需要发送的数据长度
+ `content_type`: 数据的格式
+ `iotx_msg_type_t`: CoAP消息类型(是否需要Confirmx消息)
+ `user_data`: 用户数据, 在收到应答后, 会送回给用户
+ `resp_callback`: 用户注册的回调函数, 当收到该消息的应答时被调用

### <a name="IOT_CoAP_GetMessagePayload">IOT_CoAP_GetMessagePayload</a>

原型
---
```
int IOT_CoAP_GetMessagePayload(void *p_message, unsigned char **pp_payload, int *p_len);
```

接口说明
---
当用户通 [#IOT_CoAP_SendMessage](#IOT_CoAP_SendMessage) 送消息并收到应答时, 用该接口可获取CoAP消息中的Payload部分

参数说明
---

| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-------------------------------------------------
| p_message   | void *              | 输入    | CoAP应答消息句柄, 在应答消息的回调函数中可获得
| pp_payload  | unsigned char **    | 输出    | 用于存放从`p_message`中获取的消息Payload
| p_len       | int *               | 输出    | `pp_payload`的长度

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 成功
| -1  | 输入参数非法
| -2  | 内存不足

-----

### <a name="IOT_CoAP_GetMessageCode">IOT_CoAP_GetMessageCode</a>

原型
---
```
int IOT_CoAP_GetMessageCode(void *p_message, iotx_coap_resp_code_t *p_resp_code);
```

接口说明
---
当用户通 [#IOT_CoAP_SendMessage](#IOT_CoAP_SendMessage) 送消息并收到应答时, 用该接口可获取CoAP消息中的Code(错误码)部分

参数说明
---

| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-------------------------------------------------
| p_message   | void *              | 输入    | CoAP应答消息句柄, 在应答消息的回调函数中可获得
| pp_payload  | unsigned char **    | 输出    | 用于存放从`p_message`中获取的消息Code

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 成功
| -1  | 输入参数非法

参数附加说明
---
```
typedef enum {
    IOTX_COAP_RESP_CODE_CONTENT        = 0x45, /* Mapping to 2.05, Content*/
    IOTX_COAP_RESP_CODE_BAD_REQUEST    = 0x80, /* Mapping to 4.00, Bad Request*/
    IOTX_COAP_RESP_CODE_UNAUTHORIZED   = 0x81, /* Mapping to 4.01, Token is invalid or expire*/
    IOTX_COAP_RESP_CODE_NOT_FOUND      = 0x84, /* Mapping to 4.04, Path or uri is not found*/
    IOTX_COAP_RESP_CODE_URL_TOO_LONG   = 0x8E, /* Mapping to 4.14, The request url is too long*/
    IOTX_COAP_RESP_CODE_INTERNAL_SERVER_ERROR = 0xA0,/* Mapping to 5.00, Internal server error*/

} iotx_coap_resp_code_t;
```

以上错误码可参考CoAP协议

-----

### <a name="IOT_HTTP_Init">IOT_HTTP_Init</a>

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

### <a name="IOT_HTTP_DeInit">IOT_HTTP_DeInit</a>

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

### <a name="IOT_HTTP_DeviceNameAuth">IOT_HTTP_DeviceNameAuth</a>

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

### <a name="IOT_HTTP_SendMessage">IOT_HTTP_SendMessage</a>

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

### <a name="IOT_HTTP_Disconnect">IOT_HTTP_Disconnect</a>

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

### <a name="IOT_MQTT_Construct">IOT_MQTT_Construct</a>

原型
---
```
void *IOT_MQTT_Construct(iotx_mqtt_param_t *pInitParams)
```

接口说明
---
与云端建立MQTT连接, 在调用该接口连接云端前应先使用 [#IOT_SetupConnInfo](#IOT_SetupConnInfo) 向云端进行设备认证, 得到连接云端所需参数

参数说明
---

| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|-----------------
| pInitParams     | iotx_mqtt_param_t *     | 输入    | MQTT初始化参数

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
    uint8_t                    clean_session;
    uint32_t                   request_timeout_ms;
    uint32_t                   keepalive_interval_ms;
    char                       *pwrite_buf;
    uint32_t                   write_buf_size;
    char                       *pread_buf;
    uint32_t                   read_buf_size;
    iotx_mqtt_event_handle_t    handle_event;
} iotx_mqtt_param_t, *iotx_mqtt_param_pt;
```

+ `port`: 云端服务器端口, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `host`: 云端服务器地址, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `client_id`: MQTT客户端ID, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `username`: 登录MQTT服务器用户名, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `password`: 登录MQTT服务器密码, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `pub_key`: MQTT连接加密方式及密钥, 可通 [IOT_SetupConnInfo](#IOT_SetupConnInfo) 输出参数得到
+ `clean_session`: 选择是否使用MQTT协议的clean session特性
+ `request_timeout_ms`: MQTT消息发送的超时时间
+ `keepalive_interval_ms`: MQTT心跳超时时间
+ `pwrite_buf`: MQTT消息发送buffer
+ `write_buf_size`: MQTT消息发送buffer最大长度
+ `pread_buf`: MQTT消息接收buffer
+ `read_buf_size`: MQTT消息接收buffer最大长度
+ `handle_event`: 用户回调函数, 用与接收MQTT模块的事件信息

-----

### <a name="IOT_MQTT_Destroy">IOT_MQTT_Destroy</a>

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
| phandle     | void **     | 输入    | MQTT句柄

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_MQTT_Yield">IOT_MQTT_Yield</a>

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
| handle      | void *  | 输入    | MQTT句柄
| timeout_ms  | int     | 输入    | 尝试接收报文的超时时间

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功

-----

### <a name="IOT_MQTT_LogPost">IOT_MQTT_LogPost</a>

原型
---
```
int IOT_MQTT_LogPost(void *pHandle, const char *level, const char *module, const char *msg);
```

接口说明
---
上报重要日志到云端保存

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------------------------------------------
| pHandle     | void *          | 输入    | MQTT句柄
| level       | const char *    | 输入    | 日志级别信息, 由用户自定义填写, 在云端控制台可见
| module      | const char *    | 输入    | 使用该日志接口的模块名, 由用户自定义填写, 在云端控制台可见
| msg         | const char *    | 输入    | 需要上传的日志信息

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_MQTT_CheckStateNormal">IOT_MQTT_CheckStateNormal</a>

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
| handle  | void *  | 输入    | MQTT句柄

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 未连接
| 1   | 已连接

-----

### <a name="IOT_MQTT_Subscribe">IOT_MQTT_Subscribe</a>

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
| handle              | void *                              | 输入    | MQTT句柄
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

### <a name="IOT_MQTT_Subscribe_Sync">IOT_MQTT_Subscribe_Sync</a>

原型
---
```
int IOT_MQTT_Subscribe_Sync(void *handle,
                            const char *topic_filter,
                            iotx_mqtt_qos_t qos,
                            iotx_mqtt_event_handle_func_fpt topic_handle_func,
                            void *pcontext,
                            int timeout_ms,
                            int do_yield);
```

接口说明
---
向云端订阅指定的MQTT Topic, 该接口为同步接口

参数说明
---

| 参数                | 数据类型                            | 方向    | 说明
|---------------------|-------------------------------------|---------|-------------------------------------
| handle              | void *                              | 输入    | MQTT句柄
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

### <a name="IOT_MQTT_Unsubscribe">IOT_MQTT_Unsubscribe</a>

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
| handle          | void *          | 输入    | MQTT Context
| topic_filter    | const char *    | 输入    | 需要取消订阅的topic

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_MQTT_Publish">IOT_MQTT_Publish</a>

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
| handle      | void *                      | 输入    | MQTT Context
| topic_name  | const char *                | 输入    | 接收此推送消息的目标topic
| topic_msg   | iotx_mqtt_topic_info_pt     | 输入    | 需要推送的消息

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_OTA_Init">IOT_OTA_Init</a>

原型
---
```
void *IOT_OTA_Init(const char *product_key, const char *device_name, void *ch_signal);
```

接口说明
---
初始化OTA模块, 需要先建立与云端的MQTT连接后才能使用

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| product_key     | const char *    | 输入    | 设备三元组中的Product Key
| device_name     | const char *    | 输入    | 设备三元组中的Device Name
| ch_signal       | void *          | 输入    | MQTT句柄

返回值说明
---
| 值      | 说明
|---------|-------------
| NULL    | 失败
| 非NULL  | OTA句柄

-----

### <a name="IOT_OTA_Deinit">IOT_OTA_Deinit</a>

原型
---
```
int IOT_OTA_Deinit(void *handle)
```

接口说明
---
反初始化OTA模块, 释放所有资源

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_OTA_ReportVersion">IOT_OTA_ReportVersion</a>

原型
---
```
int IOT_OTA_ReportVersion(void *handle, const char *version);
```

接口说明
---
向云端上报当前SDK版本号

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------
| handle      | void *          | 输入    | OTA句柄
| version     | const char *    | 输入    | 版本号

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_OTA_ReportProgress">IOT_OTA_ReportProgress</a>

原型
---
```
int IOT_OTA_ReportProgress(void *handle, IOT_OTA_Progress_t progress, const char *msg);
```

接口说明
---
向云端上报升级进度

参数说明
---

| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|---------------------------------
| handle      | void *              | 输入    | OTA句柄
| progress    | IOT_OTA_Progress_t  | 输入    | 当前升级进度
| msg         | const char *        | 输入    | 升级状态的描述信息, 可以为NULL

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOT_OTAP_BURN_FAILED = -4,
    IOT_OTAP_CHECK_FALIED = -3,
    IOT_OTAP_FETCH_FAILED = -2,
    IOT_OTAP_GENERAL_FAILED = -1,
    IOT_OTAP_FETCH_PERCENTAGE_MIN = 0,
    IOT_OTAP_FETCH_PERCENTAGE_MAX = 100
} IOT_OTA_Progress_t;
```
+ `IOT_OTAP_BURN_FAILED`: 固件烧写失败
+ `IOT_OTAP_CHECK_FALIED`: 固件校验失败
+ `IOT_OTAP_FETCH_FAILED`: 固件下载失败
+ `IOT_OTAP_GENERAL_FAILED`: OTA其他错误
+ `IOT_OTAP_FETCH_PERCENTAGE_MIN`: 固件OTA进度最小值, 值为0
+ `IOT_OTAP_FETCH_PERCENTAGE_MAX`: 固件OTA进度最大值, 值为100
+ 升级进度取值范围为: [0,100]区间的整数

-----

### <a name="IOT_OTA_IsFetching">IOT_OTA_IsFetching</a>

原型
---
```
int IOT_OTA_IsFetching(void *handle);
```

接口说明
---
检测当前OTA模块是否处于从云端获取数据的状态

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值  | 说明
|-----|---------------------
| 0   | 未处于获取数据状态
| 1   | 正在从云端获取数据

-----

### <a name="IOT_OTA_IsFetchFinish">IOT_OTA_IsFetchFinish</a>

原型
---
```
int IOT_OTA_IsFetchFinish(void *handle);
```

接口说明
---
检测当前OTA模块是否获取数据完成

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值  | 说明
|-----|-------------------------
| 0   | 获取数据未完成
| 1   | 已从云端获取数据完成

-----

### <a name="IOT_OTA_FetchYield">IOT_OTA_FetchYield</a>

原型
---
```
int IOT_OTA_FetchYield(void *handle, char *buf, uint32_t buf_len, uint32_t timeout_s);
```

接口说明
---
该接口用于从网络接收报文, 需要用户周期性调用

参数说明
---

| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------
| handle      | void *  | 输入    | OTA句柄
| buf         | void *  | 输入    | 用于获取配置文件的临时buffer
| buf_len     | int     | 输入    | `data_buf`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_OTA_Ioctl">IOT_OTA_Ioctl</a>

原型
---
```
int IOT_OTA_Ioctl(void *handle, IOT_OTA_CmdType_t type, void *buf, size_t buf_len);
```

接口说明
---
用于设置OTA部分参数或获取当前OTA运行状态

参数说明
---

| 参数        | 数据类型            | 方向        | 说明
|-------------|---------------------|-------------|-----------------
| handle      | void *              | 输入        | OTA句柄
| type        | IOT_OTA_CmdType_t   | 输入        | 命令类型
| buf         | void *              | 输入/输出   | 命令buffer
| buf_len     | size_t              | 输入        | `buf`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    IOT_OTAG_COTA_CONFIG_ID,
    IOT_OTAG_COTA_CONFIG_SIZE,
    IOT_OTAG_COTA_SIGN,
    IOT_OTAG_COTA_SIGN_METHOD,
    IOT_OTAG_COTA_URL,
    IOT_OTAG_COTA_GETTYPE,
    IOT_OTAG_OTA_TYPE,
    IOT_OTAG_FETCHED_SIZE,     /* option for get already fetched size */
    IOT_OTAG_FILE_SIZE,        /* size of file */
    IOT_OTAG_MD5SUM,           /* md5 in string format */
    IOT_OTAG_VERSION,          /* version in string format */
    IOT_OTAG_CHECK_FIRMWARE,    /* Check firmware is valid or not */
    IOT_OTAG_CHECK_CONFIG,      /* Check config file is valid or not */
    IOT_OTAG_RESET_FETCHED_SIZE  /* reset the size_fetched parameter to be 0 */
} IOT_OTA_CmdType_t;
```
+ `IOT_OTAG_COTA_CONFIG_ID`: 当前可升级配置文件ID
+ `IOT_OTAG_COTA_CONFIG_SIZE`: 当前可升级配置文件大小
+ `IOT_OTAG_COTA_SIGN`: 当前可升级配置文件签名
+ `IOT_OTAG_COTA_SIGN_METHOD`: 当前可升级配置文件计算签名的方法
+ `IOT_OTAG_COTA_URL`: 当前可升级配置文件下载地址
+ `IOT_OTAG_COTA_GETTYPE`: 当前可升级配置文件类型
+ `IOT_OTAG_OTA_TYPE`: 当前OTA类型, COTA或FOTA
+ `IOT_OTAG_FETCHED_SIZE`: 当前可升级配置文件已下载大小
+ `IOT_OTAG_FILE_SIZE`: 当前可升级固件文件大小
+ `IOT_OTAG_MD5SUM`: 当前已下载文件MD5值
+ `IOT_OTAG_VERSION`: 当前可升级固件版本号
+ `IOT_OTAG_CHECK_FIRMWARE`: 对已下载固件文件进行校验
+ `IOT_OTAG_CHECK_CONFIG`: 对已下载配置文件进行校验
+ `IOT_OTAG_RESET_FETCHED_SIZE`: 下载开始前, 将已下载的数据量大小size_fetched值清零

-----

### <a name="IOT_OTA_GetLastError">IOT_OTA_GetLastError</a>

原型
---
```
int IOT_OTA_GetLastError(void *handle);
```

接口说明
---
获取最近一次的错误码

参数说明
---

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| handle  | void *  | 输入    | OTA句柄

返回值说明
---
| 值      | 说明
|---------|-------------------------
| 0       | 最近一次错误码为成功
| < 0     | 最近一次错误码为失败

-----

### <a name="IOT_Shadow_Construct">IOT_Shadow_Construct</a>

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

### <a name="IOT_Shadow_Destroy">IOT_Shadow_Destroy</a>

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

### <a name="IOT_Shadow_Yield">IOT_Shadow_Yield</a>

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

### <a name="IOT_Shadow_RegisterAttribute">IOT_Shadow_RegisterAttribute</a>

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

### <a name="IOT_Shadow_DeleteAttribute">IOT_Shadow_DeleteAttribute</a>

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

### <a name="IOT_Shadow_PushFormat_Init">IOT_Shadow_PushFormat_Init</a>

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

### <a name="IOT_Shadow_PushFormat_Add">IOT_Shadow_PushFormat_Add</a>

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

### <a name="IOT_Shadow_PushFormat_Finalize">IOT_Shadow_PushFormat_Finalize</a>

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

### <a name="IOT_Shadow_Push">IOT_Shadow_Push</a>

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

### <a name="IOT_Shadow_Push_Async">IOT_Shadow_Push_Async</a>

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

### <a name="IOT_Shadow_Pull">IOT_Shadow_Pull</a>

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

### <a name="IOT_Gateway_Generate_Message_ID">IOT_Gateway_Generate_Message_ID</a>

原型
---
```
uint32_t IOT_Gateway_Generate_Message_ID(void);
```

接口说明
---
用于生成消息ID, 在向云端发送报文时需要此消息ID来标识每一条消息

参数说明
---
无返回值

返回值说明
---
| 值      | 说明
|---------|---------
| > 0     | 消息ID

-----

### <a name="IOT_Gateway_Construct">IOT_Gateway_Construct</a>

原型
---
```
void *IOT_Gateway_Construct(iotx_gateway_param_pt gateway_param);
```

接口说明
---
主设备初始化, 建立与云端的连接

参数说明
---

| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|-------------
| gateway_param   | iotx_gateway_param_pt   | 输入    | 初始化参数

返回值说明
---
| 值      | 说明
|---------|-------------
| NULL    | 错误
| 非NULL  | 主设备句柄

参数的数据结构说明
---
```
typedef struct {
    iotx_mqtt_param_pt mqtt;
    void *event_pcontext;
    iotx_subdev_event_handle_func_fpt event_handler;
} iotx_gateway_param_t, *iotx_gateway_param_pt;
```
+ `mqtt`: mqtt初始化参数
+ `event_pcontext`: 用户Context
+ `event_handler`: 事件回调函数

-----

### <a name="IOT_Gateway_Destroy">IOT_Gateway_Destroy</a>

原型
---
```
int IOT_Gateway_Destroy(void **handle);
```

接口说明
---
关闭网络连接并销毁所有主子设备资源

参数说明
---

| 参数    | 数据类型    | 方向    | 说明
|---------|-------------|---------|-------------
| handle  | void **     | 输入    | 主设备句柄

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Subdevice_Register">IOT_Subdevice_Register</a>

原型
---
```
int IOT_Subdevice_Register(void *handle,
                           iotx_subdev_register_types_t type,
                           const char *product_key,
                           const char *device_name,
                           char *timestamp,
                           char *client_id,
                           char *sign,
                           iotx_subdev_sign_method_types_t sign_type);
```

接口说明
---
该接口为同步接口, 可用于子设备动态注册, 添加与主设备的拓扑关系. 若需要使用子设备动态注册的功能, `timestamp`/`client_id`和`sign`必须为NULL

参数说明
---

| 参数            | 数据类型                            | 方向    | 说明
|-----------------|-------------------------------------|---------|-----------------------------------------------------
| handle          | void *                              | 输入    | 主设备句柄
| type            | iotx_subdev_register_types_t        | 输入    | 是否需要子设备动态注册
| product_key     | const char *                        | 输入    | 子设备三元组的Product Key
| device_name     | const char *                        | 输入    | 子设备三元组的Device Name
| timestamp       | char *                              | 输入    | 设备时间戳, 用于计算签名值, 在不进行动态注册的情况下, 添加拓扑关系时使用
| clientid        | char *                              | 输入    | 标识设备, 用于计算签名值, 在不进行动态注册的情况下, 添加拓扑关系时使用
| sign            | char *                              | 输入    | 签名, 在不进行动态注册的情况下, 添加拓扑关系时使用
| sign_type       | iotx_subdev_sign_method_types_t     | 输入    | 签名的计算方法

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
+ client_id: 格式为"product_key.device_name", 例如, 子设备的Product Key为"sub_key", Device Name为"sub_name", 那么client_id为"sub_key.sub_name"
+ sign: 该签名用于在不进行动态注册的情况下, 添加拓扑关系时使用, 计算方法是使用**clientId%sdeviceName%sproductKey%stimestamp%s**作为原始数据, **DeviceSecret**作为机密密钥, 使用hmac系列算法计算出签名

-----

### <a name="IOT_Subdevice_Unregister">IOT_Subdevice_Unregister</a>

原型
---
```
int IOT_Subdevice_Unregister(void* handle, const char* product_key, const char* device_name);
```

接口说明
---
该接口为同步接口, 用于解除主子设备拓扑关系并向云端注销设备

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| handle          | void *          | 输入    | 主设备句柄
| product_key     | const char *    | 输入    | 子设备三元组的Product Key
| device_name     | const char *    | 输入    | 子设备三元组的Device Name

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Subdevice_Login">IOT_Subdevice_Login</a>

原型
---
```
int IOT_Subdevice_Login(void* handle,
                        const char* product_key,
                        const char* device_name,
                        const char* timestamp,
                        const char* client_id,
                        const char* sign,
                        iotx_subdev_sign_method_types_t sign_method_type,
                        iotx_subdev_clean_session_types_t clean_session_type)
```

接口说明
---
该接口为同步接口, 用于使子设备登录云端

参数说明
---

| 参数                | 数据类型                            | 方向    | 说明
|---------------------|-------------------------------------|---------|---------------------------------
| handle              | void *                              | 输入    | 主设备句柄
| type                | iotx_subdev_register_types_t        | 输入    | 是否需要子设备动态注册
| product_key         | const char *                        | 输入    | 子设备三元组的Product Key
| device_name         | const char *                        | 输入    | 子设备三元组的Device Name
| timestamp           | char *                              | 输入    | 设备时间戳, 用于计算签名值
| clientid            | char *                              | 输入    | 标识设备, 用于计算签名值
| sign                | char *                              | 输入    | 签名值
| sign_type           | iotx_subdev_sign_method_types_t     | 输入    | 签名的计算方法
| clean_session_type  | iotx_subdev_clean_session_types_t   | 输入    | 选择是否清理子设备离线时的消息

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
+ client_id: 格式为"product_key.device_name", 例如, 子设备的Product Key为"sub_key", Device Name为"sub_name", 那么client_id为"sub_key.sub_name"
+ sign: 该签名用于在不进行动态注册的情况下, 添加拓扑关系时使用, 计算方法是使用**clientId%sdeviceName%sproductKey%stimestamp%s**作为原始数据, **DeviceSecret**作为机密密钥, 使用hmac系列算法计算出签名

-----

### <a name="IOT_Subdevice_Logout">IOT_Subdevice_Logout</a>

原型
---
```
int IOT_Subdevice_Logout(void* handle, const char * product_key, const char * device_name);
```

接口说明
---
该接口为同步接口, 用于使子设备登出云端

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| handle          | void *          | 输入    | 主设备句柄
| product_key     | const char *    | 输入    | 子设备三元组的Product Key
| device_name     | const char *    | 输入    | 子设备三元组的Device Name

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Get_TOPO">IOT_Gateway_Get_TOPO</a>

原型
---
```
int IOT_Gateway_Get_TOPO(void* handle, char* get_topo_reply, uint32_t* length);
```

接口说明
---
该接口为同步接口, 用于向云端获取主子设备拓扑关系列表, 该列表为JSON数组格式

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| handle          | void *          | 输入    | 主设备句柄
| product_key     | const char *    | 输入    | 子设备三元组的Product Key
| get_topo_reply  | char *          | 输入    | 用于存放topo关系列表
| length          | uint32_t *      | 输入    | `get_topo_reply`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Get_Config">IOT_Gateway_Get_Config</a>

原型
---
```
int IOT_Gateway_Get_Config(void *handle,
                           char *get_config_reply,
                           uint32_t *length);
```

接口说明
---
该接口为同步接口, 用于从云端获取产品配置文件

参数说明
---

| 参数                | 数据类型    | 方向    | 说明
|---------------------|-------------|---------|---------------------------------
| handle              | void *      | 输入    | 主设备句柄
| get_config_reply    | char *      | 输出    | 用于存放获取到的配置文件数据
| length              | uint32_t *  | 输出    | 实际配置文件大小

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Publish_Found_List">IOT_Gateway_Publish_Found_List</a>

原型
---
```
int IOT_Gateway_Publish_Found_List(void* handle, const char* product_key, const char* device_name);
```

接口说明
---
该接口为同步接口, 通知云端当前有子设备尝试接入. 该接口常见的使用场景是: 当用户需要对接入的子设备做自己的认证时, 可通过该接口将尝试接入的子设备上报给云端, 通过云端数据流转通知到用户的云端做认证, 返回结果会通过`通知添加设备topo关系(/thing/topo/add/notify)`的消息返回

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------
| handle          | void *          | 输入    | 主设备句柄
| product_key     | const char *    | 输入    | 子设备三元组的Product Key
| device_name     | const char *    | 输入    | 子设备三元组的Device Name

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Yield">IOT_Gateway_Yield</a>

原型
---
```
int IOT_Gateway_Yield(void* handle, uint32_t timeout);
```

接口说明
---
从网络上获取报文, 需要用户周期性调用

参数说明
---

| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------
| handle      | void *      | 输入    | 主设备句柄
| timeout     | uint32_t    | 输入    | 尝试从网络上获取报文的超时时间

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Subscribe">IOT_Gateway_Subscribe</a>

原型
---
```
int IOT_Gateway_Subscribe(void* handle,
                            const char *topic_filter,
                            int qos,
                            iotx_subdev_event_handle_func_fpt topic_handle_func,
                            void *pcontext)
```

接口说明
---
用于向云端订阅指定topic的MQTT消息

参数说明
---

| 参数                | 数据类型                            | 方向    | 说明
|---------------------|-------------------------------------|---------|-------------------------------------------------
| handle              | void *                              | 输入    | 主设备句柄
| topic_filter        | const char *                        | 输入    | 需要订阅的topic
| qos                 | int                                 | 输入    | MQTT的qos级别
| topic_handle_func   | iotx_subdev_event_handle_func_fpt   | 输入    | 该订阅topic的mqtt消息到达时会调用的回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Unsubscribe">IOT_Gateway_Unsubscribe</a>

原型
---
```
int IOT_Gateway_Unsubscribe(void* handle, const char *topic_filter);
```

接口说明
---
用于向云端取消订阅指定topic

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------
| handle          | void *          | 输入    | 主设备句柄
| topic_filter    | const char *    | 输入    | 需要取消订阅的topic

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_Publish">IOT_Gateway_Publish</a>

原型
---
```
int IOT_Gateway_Publish(void *handle, const char *topic_name, iotx_mqtt_topic_info_pt topic_msg)
```

接口说明
---
该接口用于向云端推送MQTT消息

参数说明
---

| 参数        | 数据类型                    | 方向    | 说明
|-------------|-----------------------------|---------|-------------------------
| handle      | void *                      | 输入    | 主设备句柄
| topic_name  | const char *                | 输入    | 消息需要送达的topic
| topic_msg   | iotx_mqtt_topic_info_pt     | 输入    | 需要推送的MQTT消息

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_RRPC_Register">IOT_Gateway_RRPC_Register</a>

原型
---
```
int IOT_Gateway_RRPC_Register(void* handle,
                                const char* product_key,
                                const char* device_name,
                                rrpc_request_callback rrpc_callback);
```

接口说明
---
用于注册指定设备的同步服务调用回调函数, 当该设备收到同步服务调用请求时, 回调函数被触发

参数说明
---

| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|-----------------------------
| handle          | void *                  | 输入    | 主设备句柄
| product_key     | const char *            | 输入    | 设备三元组的Product Key
| device_name     | const char *            | 输入    | 设备三元组的Device Name
| rrpc_callback   | rrpc_request_callback   | 输入    | 同步服务调用的回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Gateway_RRPC_Response">IOT_Gateway_RRPC_Response</a>

原型
---
```
int IOT_Gateway_RRPC_Response(void* handle,
                                const char* product_key,
                                const char* device_name,
                                const char* message_id,
                                const char* response);
```

接口说明
---
当用户收到同步服务调用请求时, 可使用该接口进行回复

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-----------------------------------------
| handle          | void *          | 输入    | 主设备句柄
| product_key     | const char *    | 输入    | 设备三元组的Product Key
| device_name     | const char *    | 输入    | 设备三元组的Device Name
| message_id      | const char *    | 输入    | 在收到同步服务调用请求时获得的消息ID
| response        | const char *    | 输入    | 应答消息Payload

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="7.3 高级版(新版)API接口详解">7.3 高级版(新版)API接口详解</a>

### <a name="IOT_Linkkit_Open">IOT_Linkkit_Open</a>

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

### <a name="IOT_Linkkit_Connect">IOT_Linkkit_Connect</a>

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

| 参数    | 数据类型                        | 方向    | 说明
|---------|---------------------------------|---------|-------------------------------------
| devid   | int                             | 输入    | 设备ID

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Linkkit_Yield">IOT_Linkkit_Yield</a>

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

| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-------------------------------------------------
| timeout_ms  | int     | 输入    | 单线程模式下, 每次尝试接收网络报文的超时时间

返回值说明
---
无返回值

-----

### <a name="IOT_Linkkit_Close">IOT_Linkkit_Close</a>

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

| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|---------
| devid   | int     | 输入    | 设备ID

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="IOT_Linkkit_TriggerEvent">IOT_Linkkit_TriggerEvent</a>

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

| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|---------------------
| devid           | int     | 输入    | 设备ID
| eventid         | char *  | 输入    | TSL中定义的事件ID
| eventid_len     | int     | 输入    | 事件ID的长度
| payload         | char *  | 输入    | 事件Payload
| payload_len     | int     | 输入    | 事件Payload的长度

返回值说明
---
| 值      | 说明
|---------|---------
| >= 1    | 消息ID
| < 0     | 失败

-----

### <a name="IOT_Linkkit_Report">IOT_Linkkit_Report</a>

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

-----

### <a name="IOT_Linkkit_Query">IOT_Linkkit_Query</a>

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

### <a name="IOT_RegisterCallback">IOT_RegisterCallback</a>

原型
---
```
#define IOT_RegisterCallback(evt, cb)           iotx_register_for_##evt(cb);

```

接口说明
---
该接口用于注册事件的回调函数, 当Linkkit SDK产生事件时, 会调用对应的回调函数

参数说明
---

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| evt           | iotx_ioctl_event_t         | 输入    | 事件名称
| cb            | 根据evt的不同而各有不同        | 输入    | 回调函数

-----

返回值说明
---
无返回值

参数附加说明
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

| 事件 | 回调函数原型 | 事件触发条件说明 |
|------|-----------|--------|----
| [ITE_CONNECT_SUCC](#ITE_CONNECT_SUCC) | int callback(void); | 与云端连接成功时 |
| [ITE_DISCONNECTED](#ITE_DISCONNECTED) | int callback(void); | 与云端连接断开时 |
| [ITE_RAWDATA_ARRIVED](#ITE_RAWDATA_ARRIVED) | int callback(const int devid, const unsigned char *payload, const int payload_len);  | Linkkit收到收到raw data数据时 |
| [ITE_SERVICE_REQUEST](#ITE_SERVICE_REQUEST) | int callback(const int devid, const char *serviceid, const int serviceid_len, const char *request, const int request_len, char **response, int *response_len);  | Linkkit收到收到服务(同步/异步)调用请求时 |
| [ITE_PROPERTY_SET](#ITE_PROPERTY_SET) | int callback(const int devid, const char *request, const int request_len); | Linkkit收到收到属性设置请求时 |
| [ITE_PROPERTY_GET](#ITE_PROPERTY_GET) | int callback(const int devid, const char *request, const int request_len, char **response, int *response_len); | Linkkit收到收到属性获取的请求时 |
| [ITE_REPORT_REPLY](#ITE_REPORT_REPLY) | int callback(const int devid, const int msgid, const int code, const char *reply, const int reply_len); | Linkkit收到收到上报消息的应答时 |
| [ITE_TRIGGER_EVENT_REPLY](#ITE_TRIGGER_EVENT_REPLY) | int callback(const int devid, const int msgid, const int code, const char *eventid, const int eventid_len, const char *message, const int message_len); | Linkkit收到收到事件上报消息的应答时 |
| [ITE_TIMESTAMP_REPLY](#ITE_TIMESTAMP_REPLY) | int callback(const char *timestamp); | 当Linkkit收到收到查询时间戳请求的应答时 |
| [ITE_TOPOLIST_REPLY](#ITE_TOPOLIST_REPLY) | int callback(const int devid, const int msgid, const int code, const char * payload, const int payload_len); | Linkkit收到收到查询拓扑关系请求的应答时 |
| [ITE_PERMIT_JOIN](#ITE_PERMIT_JOIN) | int callback(const char * product_key, const int time); | Linkkit收到允许子设备入网的请求时
| [ITE_INITIALIZE_COMPLETED](#ITE_INITIALIZE_COMPLETED) | int callback(const int devid); | 设备初始化完成时 |
| [ITE_FOTA](#ITE_FOTA) | int callback(int type, const char *version); | Linkkit收到可用固件的通知时 |
| [ITE_COTA](#ITE_COTA) | int callback(int type, const char *config_id, int config_size, const char *get_type, const char *sign, const char *sign_method, const char *url); | Linkkit收到可用远程配置文件的通知时 |

### <a name="ITE_CONNECT_SUCC事件">ITE_CONNECT_SUCC事件</a>

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
| 值 | 说明 |
|---|---|---
| 0 | 事件处理成功 |
| -1 | 事件处理失败 |

### <a name="ITE_DISCONNECTED事件">ITE_DISCONNECTED事件</a>

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
| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_RAWDATA_ARRIVED事件">ITE_RAWDATA_ARRIVED事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| payload         | const unsigned char *       | 输入    | 透传数据payload
| payload_len     | const int                   | 输入    | payload的长度

返回值说明
---
| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_SERVICE_REQUEST事件">ITE_SERVICE_REQUEST事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| serviceid       | const char *                | 输入    | 服务ID
| serviceid_len   | const int                   | 输入    | serviceid的长度
| request         | const char *                | 输入    | 服务的输入参数
| request_len     | const int                   | 输入    | 服务的输入参数长度
| response        | char **                     | 输出    | 服务的输出参数
| response_len    | int *                       | 输出    | 服务的输出参数长度

返回值说明
---
返回值需要注意的是, 当***response**存在的情况下, 返回0或-1会将此次服务调用的成功与否一并发送给云端

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_PROPERTY_SET事件">ITE_PROPERTY_SET事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| request         | const char *                | 输入    | 属性设置的payload
| request_len     | const int                   | 输入    | payload的长度

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_PROPERTY_GET事件">ITE_PROPERTY_GET事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| request         | const char *                | 输入    | 属性获取请求的payload
| request_len     | const int                   | 输入    | payload的长度
| response        | char **                     | 输出    | 所有被请求的属性值的集合
| response_len    | int *                       | 输出    | *response的长度

返回值说明
---
返回值需要注意的是, 当***response**存在的情况下, 返回0或-1会将此次服务调用的成功与否一并发送给云端

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_REPORT_REPLY事件">ITE_REPORT_REPLY事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| msgid           | const int                   | 输入    | 消息ID
| code            | const int                   | 输入    | 云端返回的错误码
| reply           | const char *                | 输入    | 错误码的描述信息
| reply_len       | const int                   | 输入    | 错误码描述信息的长度

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_TRIGGER_EVENT_REPLY事件">ITE_TRIGGER_EVENT_REPLY事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| msgid           | const int                   | 输入    | 消息ID
| code            | const int                   | 输入    | 云端返回的错误码
| eventid         | const char *                | 输入    | 事件ID
| eventid_len     | const int                   | 输入    | 事件ID的长度
| message         | const char *                | 输入    | 事件错误码的描述信息
| message_len     | const int                   | 输入    | message的长度

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_TIMESTAMP_REPLY事件">ITE_TIMESTAMP_REPLY事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| timestamp       | const char *                | 输入     | 时间戳字符串

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_TOPOLIST_REPLY事件">ITE_TOPOLIST_REPLY事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID
| msgid           | const int                   | 输入    | 消息ID
| code            | const int                   | 输入    | 云端返回的错误码
| payload         | const char *                | 输入    | 拓扑关系列表
| payload_len     | const int                   | 输入    | payload的长度

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_PERMIT_JOIN事件">ITE_PERMIT_JOIN事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| product_key     | const char *                | 输入    | 子设备的Product Key, 如果该字段为字符串"NULL", 则允许任何子设备接入
| time            | const int                   | 输入    | 允许子设备接入的时间窗口

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_INITIALIZE_COMPLETED事件">ITE_INITIALIZE_COMPLETED事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| devid           | int                         | 输入    | 设备ID

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_FOTA事件">ITE_FOTA事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| type            | int                         | 输入    | FOTA的消息类型, 目前只有值为`0`的一种消息, 即新固件到达
| version         | const char *                | 输入    | 可用的固件版本号

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="ITE_COTA事件">ITE_COTA事件</a>

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
| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| type            | int                         | 输入    | COTA的消息类型, 目前只有值为`0`的一种消息, 即存在可用的配置文件
| config_id       | const char *                | 输入    | 配置文件ID
| config_size     | int                         | 输入    | 配置文件大小
| get_type        | const char *                | 输入    | 配置文件数据类型
| sign            | const char *                | 输入    | 配置文件的签名值
| sign_method     | const char *                | 输入    | 配置文件的签名方法
| url             | const char *                | 输入    | 配置文件的下载地址

返回值说明
---

| 值 | 说明 |
|---|---|---
|0|事件处理成功|
|-1|事件处理失败|

-----

### <a name="IOT_Ioctl">IOT_Ioctl</a>

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

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|-------------|---------------------
| option          | int                         | 输入        | 需要进行的操作
| data            | void *                      | 输入/输出    | option需要的输入/输出参数

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

-----

## <a name="7.4 高级版(旧版)单品API详解">7.4 高级版(旧版)单品API详解</a>

> 本节介绍的API适用于您的设备不具有对子设备的管理能力的场景, 参看 [单品](#单品) 的名词解释部分

### <a name="linkkit_answer_service">linkkit_answer_service</a>

原型
---
```
int deprecated linkkit_answer_service(const void *thing_id, const char *service_identifier, int response_id, int code);
```

接口说明
---
在用户收到异步服务调用请求后, 可使用该接口向云端回复异步服务的输出参数

参数说明
---

| 参数                | 数据类型        | 方向    | 说明
|---------------------|-----------------|---------|-------------------------------------------------
| thing_id            | const void *    | 输入    | 设备ID
| service_identifier  | const char *    | 输入    | 输出参数的ID
| response_id         | int             | 输入    | 消息ID, 应该与接收到异步服务请求的消息ID一致
| code                | int             | 输入    | 返回给云端的错误码

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_cota_init">linkkit_cota_init</a>

原型
---
```
int deprecated linkkit_cota_init(handle_service_cota_callback_fp_t callback_fp);
```

接口说明
---
初始化Config OTA的用户回调函数. 当获取到配置文件的更新信息时, 会通过此回调函数通知用户

当用户收到通知后, 可调用`linkkit_invoke_cota_service`获取配置文件

参数说明
---

| 参数            | 数据类型                            | 方向    | 说明
|-----------------|-------------------------------------|---------|-----------------
| callback_fp     | handle_service_cota_callback_fp_t   | 输入    | 用户回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef void (*handle_service_cota_callback_fp_t)(
                                service_cota_callback_type_t callback_type,
                                const char *configid,
                                uint32_t configsize,
                                const char *gettype,
                                const char *sign,
                                const char *signmethod,
                                const char *cota_url);
```
+ `callback_type`: 消息类型, 目前仅支持`service_cota_callback_type_new_version_detected`
+ `configid`: 配置文件ID
+ `configsize`: 配置文件大小
+ `gettype`: 配置文件数据类型, 当前为`文件`
+ `sign`: 文件的签名
+ `signmethod`: 计算签名所用的签名方法
+ `cota_url`: 配置文件下载地址

-----

### <a name="linkkit_dispatch">linkkit_dispatch</a>

原型
---
```
void *linkkit_dispatch(void);
```

接口说明
---
该接口用于用户获取sdk中的各种事件, 如属性设置请求/服务调用请求等, 需要用户周期性调用

参数说明
---
无参数

返回值说明
---
| 值      | 说明
|---------|-----
| NULL    | 无

-----

### <a name="linkkit_end">linkkit_end</a>

原型
---
```
int deprecated linkkit_end(void);
```

接口说明
---
关闭Linkkit与云端的连接并释放所有资源

参数说明
---
无参数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_fota_init">linkkit_fota_init</a>

原型
---
```
int deprecated linkkit_fota_init(handle_service_fota_callback_fp_t callback_fp);
```

接口说明
---
初始化Firmware OTA的用户回调函数. 当获取到固件的更新信息时, 会通过此回调函数通知用户

当用户收到通知后, 可调用`linkkit_invoke_fota_service`获取固件

参数说明
---

| 参数            | 数据类型                            | 方向    | 说明
|-----------------|-------------------------------------|---------|-----------------
| callback_fp     | handle_service_fota_callback_fp_t   | 输入    | 用户回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef void (*handle_service_fota_callback_fp_t)(
                                service_fota_callback_type_t callback_type,
                                const char *version);
```
+ `callback_type`: 消息类型, 目前仅支持`service_fota_callback_type_new_version_detected`
+ `version`: 当前可获取固件的版本号

-----

### <a name="linkkit_get_value">linkkit_get_value</a>

原型
---
```
int deprecated linkkit_get_value(linkkit_method_get_t method_get,
                                    const void *thing_id,
                                    const char *identifier,
                                    void *value,
                                    char **value_str);
```

接口说明
---
该接口用于获取设备影子中的TSL的相关值, `value`和`value_str`选填一个即可

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------
| method_get  | linkkit_method_get_t    | 输入    | 需要获取的TSL数据类型
| thing_id    | const void *            | 输入    | 设备ID
| identifier  | const char *            | 输入    | TSL数据标识的ID
| value       | void *                  | 输出    | 该buffer用于存放获取到的值
| value_str   | char **                 | 输出    | 获取值的字符串形式

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    linkkit_method_get_property_value = 0,
    linkkit_method_get_event_output_value,
    linkkit_method_get_service_input_value,
    linkkit_method_get_service_output_value,
    linkkit_method_get_number,
} linkkit_method_get_t;
```
+ linkkit_method_get_property_value: TSL中的属性
+ linkkit_method_get_event_output_value: TSL中事件的输出参数
+ linkkit_method_get_service_input_value: TSL中服务的输入参数
+ linkkit_method_get_service_output_value: TSL中服务的输出参数

-----

### <a name="linkkit_invoke_cota_get_config">linkkit_invoke_cota_get_config</a>

原型
---
```
int deprecated linkkit_invoke_cota_get_config(
                                const char *config_scope,
                                const char *get_type,
                                const char *attribute_Keys,
                                void *option);
```

接口说明
---
该接口用于向云端主动发起Config OTA, 即主动发起配置文件获取请求

参数说明
---

| 参数            | 数据类型        | 方向    | 说明
|-----------------|-----------------|---------|-------------------------------------
| config_scope    | const char *    | 输入    | 配置域, 当前为`product`
| get_type        | const char *    | 输入    | 配置的数据类型, 当前为`file`
| attribute_Keys  | const char *    | 输入    | 配置的属性信息, 当前为空字符串即可
| option          | void *          | 输入    | 保留

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_invoke_cota_service">linkkit_invoke_cota_service</a>

原型
---
```
int deprecated linkkit_invoke_cota_service(void *data_buf, int data_buf_length);
```

接口说明
---
该接口用于发起Config OTA请求, 需要在`linkkit_cota_init`设置的回调函数中使用

参数说明
---

| 参数                | 数据类型| 方向    | 说明
|---------------------|---------|---------|---------------------------------
| data_buf            | void *  | 输入    | 用于获取配置文件的临时buffer
| data_buf_length     | int     | 输入    | `data_buf`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_invoke_fota_service">linkkit_invoke_fota_service</a>

原型
---
```
int deprecated linkkit_invoke_fota_service(void *data_buf, int data_buf_length);
```

接口说明
---
该接口用于发起Firmware OTA请求, 需要在`linkkit_fota_init`设置的回调函数中使用

参数说明
---

| 参数                | 数据类型| 方向    | 说明
|---------------------|---------|---------|-----------------------------
| data_buf            | void *  | 输入    | 用于获取固件的临时buffer
| data_buf_length     | int     | 输入    | `data_buf` 的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_invoke_raw_service">linkkit_invoke_raw_service</a>

原型
---
```
int deprecated linkkit_invoke_raw_service(
                            const void *thing_id,
                            int is_up_raw,
                            void *raw_data,
                            int raw_data_length);
```

接口说明
---
透传数据接口. 当用户在云端控制台定义设备数据格式为`透传/自定义`时, 可使用此接口上传透传数据

参数说明
---

| 参数                | 数据类型        | 方向    | 说明
|---------------------|-----------------|---------|---------------------
| thing_id            | const void *    | 输入    | 设备ID
| is_up_raw           | int             | 输入    | 保留
| raw_data            | void *          | 输入    | 透传数据Payload
| raw_data_length     | int             | 输入    | 透传数据的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_is_end">linkkit_is_end</a>

原型
---
```
int deprecated linkkit_is_end();
```

接口说明
---
获取当前linkkit运行状态

参数说明
---
无参数

返回值说明
---
| 值  | 说明
|-----|---------------------
| 0   | linkkit未结束运行
| 1   | linkkit已结束运行

-----

### <a name="linkkit_is_try_leave">linkkit_is_try_leave</a>

原型
---
```
int deprecated linkkit_is_try_leave(void)
```

接口说明
---
检测当前linkkit是否正在尝试退出

参数说明
---
无参数

返回值说明
---
| 值  | 说明
|-----|---------------------
| 0   | linkkit未尝试退出
| 1   | linkkit正尝试退出

-----

### <a name="linkkit_post_property">linkkit_post_property</a>

原型
---
```
int deprecated linkkit_post_property(const void *thing_id,
                                        const char *property_identifier,
                                        handle_post_cb_fp_t cb);
```

接口说明
---
向云端上报属性信息

参数说明
---

| 参数                    | 数据类型                | 方向    | 说明
|-------------------------|-------------------------|---------|-------------------------------------
| thing_id                | const void *            | 输入    | 设备ID
| property_identifier     | const char *            | 输入    | 属性ID
| cb                      | handle_post_cb_fp_t     | 输入    | 属性上报返回应答时触发的回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_set_opt">linkkit_set_opt</a>

原型
---
```
int deprecated linkkit_set_opt(linkkit_opt_t opt, void *data);
```

接口说明
---
在用户使用`linkkit_start`启动linkkit之前, 可用此接口对SDK部分参数进行调整

参数说明
---

| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-------------------------
| opt     | linkkit_opt_t   | 输入    | 选择需要配置的参数类型
| data    | void *          | 输入    | 需要配置的参数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

参数附加说明
---
```
typedef enum {
    linkkit_opt_property_post_reply,
    linkkit_opt_event_post_reply,
    linkkit_opt_property_set_reply
} linkkit_opt_t;
```

+ `linkkit_opt_property_post_reply`: 在设备上报属性后, 是否需要云端的应答消息. `arg`数据类型为`int *`
+ `linkkit_opt_event_post_reply`: 在设备上报事件后, 是否需要云端的应答消息. `arg`数据类型为`int *`
+ `linkkit_opt_property_set_reply`: 在收到云端的属性设置后, 是否需要向云端发送应答消息. `arg`数据类型为`int *`

-----

### <a name="linkkit_set_tsl">linkkit_set_tsl</a>

原型
---
```
void *linkkit_set_tsl(const char *tsl, int tsl_len);
```

接口说明
---
该接口可将 `TSL` 转换成设备影子

参数说明
---

| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|---------------------
| tsl         | const char *    | 输入    | 设备所属产品的TSL
| tsl_len     | int             | 输入    | `tsl`的长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_set_value">linkkit_set_value</a>

原型
---
```
int deprecated linkkit_set_value(linkkit_method_set_t method_set,
                                    const void *thing_id,
                                    const char *identifier,
                                    const void *value,
                                    const char *value_str);
```

接口说明
---
用户可通过此接口设置设备影子的值, `value`和`value_str`选填一个即可

参数说明
---

| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------------------
| method_set  | linkkit_method_set_t    | 输入    | 需要设置的TSL数据类型
| thing_id    | const void *            | 输入    | 设备ID
| identifier  | const char *            | 输入    | TSL数据标识的ID
| value       | const void *            | 输入    | 需要设置的具体value
| value_str   | const char *            | 输入    | 需要设置的具体value的字符串表达形式

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_start">linkkit_start</a>

原型
---
```
int deprecated linkkit_start(int max_buffered_msg,
                                int get_tsl_from_cloud,
                                linkkit_loglevel_t log_level,
                                linkkit_ops_t *ops,
                                linkkit_cloud_domain_type_t domain_type,
                                void *user_context);
```

接口说明
---
该接口用于启动linkkit, 在调用该接口之前, 可使用 `linkkit_set_opt` 对SDK进行部分参数的调整

参数说明
---

| 参数                | 数据类型                        | 方向    | 说明
|---------------------|---------------------------------|---------|-------------------------
| max_buffered_msg    | int                             | 输入    | 保留
| get_tsl_from_cloud  | int                             | 输入    | 是否需要从云端拉取TSL
| ops                 | linkkit_ops_t *                 | 输入    | linkkit事件的回调函数
| domain_type         | linkkit_cloud_domain_type_t     | 输入    | 当前需要连接的region
| user_context        | void *                          | 输入    | 用户Context

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_trigger_event">linkkit_trigger_event</a>

原型
---
```
int deprecated linkkit_trigger_event(const void *thing_id,
                                        const char *event_identifier,
                                        handle_post_cb_fp_t cb);
```

接口说明
---
向云端上报事件信息

参数说明
---

| 参数                | 数据类型                | 方向    | 说明
|---------------------|-------------------------|---------|-------------------------------------
| thing_id            | const void *            | 输入    | 设备ID
| event_identifier    | const char *            | 输入    | 事件ID
| cb                  | handle_post_cb_fp_t     | 输入    | 事件上报返回应答时触发的回调函数

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_trigger_extended_info_operate">linkkit_trigger_extended_info_operate</a>

原型
---
```
int deprecated linkkit_trigger_extended_info_operate(
                            const void *thing_id,
                            const char *params,
                            linkkit_extended_info_operate_t linkkit_extended_info_operation);
```

接口说明
---
用于向云端发送设备标签的更新和删除命令

参数说明
---

| 参数                                | 数据类型                            | 方向    | 说明
|-------------------------------------|-------------------------------------|---------|---------------------------------
| thing_id                            | const void *                        | 输入    | 设备ID
| params                              | const char *                        | 输入    | 设备标签更新和删除命令Payload
| linkkit_extended_info_operation     | linkkit_extended_info_operate_t     | 输入    | 命令类型

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

### <a name="linkkit_try_leave">linkkit_try_leave</a>

原型
---
```
void deprecated linkkit_try_leave(void);
```

接口说明
---
表示即将调用`linkkit_end`来结束linkkit的运行

参数说明
---
无参数

返回值说明
---
无返回值

-----

### <a name="linkkit_yield">linkkit_yield</a>

原型
---
```
int deprecated linkkit_yield(int timeout_ms);
```

接口说明
---
从网络上获取报文, 需要用户周期性调用

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-----------------------------
| timeout_ms  | int     | 输入    | 尝试获取网络报文的超时时间

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| < 0     | 失败

-----

## <a name="7.5 高级版(旧版)网关API详解">7.5 高级版(旧版)网关API详解</a>

> 本节介绍的API适用于您的设备具有对子设备的管理能力的场景, 参看 [网关](#网关) 的名词解释部分

### <a name="linkkit_gateway_delete_extinfos">linkkit_gateway_delete_extinfos</a>

原型
---
```
int linkkit_gateway_delete_extinfos(int devid, linkkit_extinfo_t *extinfos, int nb_extinfos, int timeout_ms);
```

接口说明
---
删除由参数`extinfos`数组指定的拓展信息, 此接口为同步接口, 若参数`timeout_ms`为0则函数立即返回, 不等待云端应答

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|---------------------------------
| devid           | int                     | 输入    | 设备ID
| extinfos        | linkkit_extinfo_t *     | 输入    | 指向拓展参数结构体数组的指针
| nb_extinfos     | int                     | 输入    | 指明`extinfos`数组参数的数量
| timeout_ms      | int                     | 输入    | 发送超时时间

拓展参数结构体定义:
```
typedef struct {
    char *attrKey;    /* 拓展信息的key */
    char *attrValue;  /* 拓展信息的value */
} linkkit_extinfo_t;
```

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_exit">linkkit_gateway_exit</a>

原型
---
```
int linkkit_gateway_exit(void);
```

接口说明
---
网关反初始化, 与`linkkit_gateway_init()`对应

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_fota_init">linkkit_gateway_fota_init</a>

原型
---
```
int linkkit_gateway_fota_init(handle_service_fota_callback_fp_t callback_fp)
```

接口说明
---
FOTA服务初始化, 并注册回调函数, 当有FOTA事件触发时将会调用用户回调函数

参数说明
---
| 参数            | 数据类型                            | 方向    | 说明
|-----------------|-------------------------------------|---------|---------------------
| callback_fp     | handle_service_fota_callback_fp_t   | 输入    | FOTA服务回调函数

FOTA服务回调函数类型定义:
```
typedef void (*handle_service_fota_callback_fp_t)(service_fota_callback_type_t callback_type, const char *version);

typedef enum {
    service_fota_callback_type_new_version_detected = 10,   /* 检测到新版本 */
    service_fota_callback_type_number,
} service_fota_callback_type_t;
```

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_get_default_params">linkkit_gateway_get_default_params</a>

原型
---
```
linkkit_params_t *linkkit_gateway_get_default_params(void);
```

接口说明
---
获取默认的网关配置参数, 获取到的返回值将在调用`linkkit_gateway_init()`时作为参数传入, 用于初始化网关

参数说明
---
void

返回值说明
---
指向`linkkit_params_t`类型结构体的指针

```
typedef struct linkkit_params_s {
    int maxMsgSize;         /* reserved */
    int maxMsgQueueSize;    /* reserved */
    int threadPoolSize;     /* reserved */
    int threadStackSize;    /* reserved */

    int (*event_cb)(linkkit_event_t *ev, void *ctx);    /* 网关事件回调函数, 事件结构体查看下方 */
    void *ctx;              /* 用户数据 */
}linkkit_params_t;
```

网关事件结构体定义linkkit_event_t:
```
typedef struct {
    int event_type;             /* 网关事件类型 */

    union {
        struct {
            char *productKey;
            char *deviceName;
        } subdev_deleted;       /* 子设备删除事件的事件数据 */

        struct {
            char *productKey;
            int   timeoutSec;
        } subdev_permited;      /* 子设备启用事件的事件数据 */

        struct {
            char *subdevList;
        } subdev_install;       /* Reserver */
    } event_data;
} linkkit_event_t;
```

网关事件类型
```
enum {
    LINKKIT_EVENT_CLOUD_DISCONNECTED = 0,   /* 与云端断开连接 */
    LINKKIT_EVENT_CLOUD_CONNECTED    = 1,   /* 与云端建立连接 */
    LINKKIT_EVENT_SUBDEV_DELETED     = 2,   /* 子设备被删除 */
    LINKKIT_EVENT_SUBDEV_PERMITED    = 3,   /* 子设备被启用 */
    LINKLIT_EVENT_SUBDEV_SETUP       = 4,   /* Reserved */
};
```

-----

### <a name="linkkit_gateway_get_devinfo">linkkit_gateway_get_devinfo</a>

原型
---
```
int linkkit_gateway_get_devinfo(int devid, linkkit_devinfo_t *devinfo);
```

接口说明
---
获取设备信息, 输入设备ID, 返回对应的ProductKey, DeviceName等信息

参数说明
---
| 参数        | 数据类型                | 方向    | 说明
|-------------|-------------------------|---------|-----------------------------
| devid       | int                     | 输入    | 设备ID
| devinfo     | linkkit_devinfo_t *     | 输入    | 指向设备信息结构体的指针

```
typedef struct {
    char *productKey;           /* 设备的ProductKey */
    char *deviceName;           /* 设备的DeviceName */

    int   devtype;              /* 设备类型: 0 - 网关, 1 - 子设备 */
    int   login;                /* 登陆状态: 0 - 登出, 1 - 登入 */
    int   state;                /* 设备状态: 查看下方枚举类型定义 */
    int   online;               /* 在线状态: 0 - 离线, 1 - 在线 */
} linkkit_devinfo_t;

enum {
    LINKKIT_STATE_ENABLED  = 0, /* 设备已被云端启用 */
    LINKKIT_STATE_DISABLED,     /* 设备已被云端禁用 */
    LINKKIT_STATE_REMOVED,      /* 设备已被云端删除 */
};
```

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_get_num_devices">linkkit_gateway_get_num_devices</a>

原型
---
```
int linkkit_gateway_get_num_devices(void);
```

接口说明
---
获取注册到SDK的设备总数, 包括网关和所有子设备

参数说明
---
void

返回值说明
---
设备数量

-----

### <a name="linkkit_gateway_init">linkkit_gateway_init</a>

原型
---
```
int linkkit_gateway_init(linkkit_params_t *initParams);
```

接口说明
---
使用参数`initParams`初始化网关

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-------------------------------------------------------------
| initParams  | linkkit_params_t *  | 输入    | 初始化参数, 由`linkkit_gateway_get_default_params()`获取

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_invoke_fota_service">linkkit_gateway_invoke_fota_service</a>

原型
---
```
int linkkit_gateway_invoke_fota_service(void* data_buf, int data_buf_length);
```

接口说明
---
执行FOTA服务

参数说明
---
| 参数                | 数据类型| 方向    | 说明
|---------------------|---------|---------|-----------------------------------------
| data_buf            | void *  | 输入    | 数据缓冲区, OTA将使用此缓冲区下载固件
| data_buf_length     | int     | 输入    | 数据缓冲区字节长度

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_post_extinfos">linkkit_gateway_post_extinfos</a>

原型
---
```
int linkkit_gateway_post_extinfos(int devid, linkkit_extinfo_t *extinfos, int nb_extinfos, int timeout_ms)
```

接口说明
---
上报拓展信息, 拓展信息在控制台上以标签信息呈现. 此接口为同步接口, 若参数`timeout_ms`为0则函数立即返回, 不等待云端应答, 否则将一直等待云端应答直到超时发生

参数说明
---
| 参数            | 数据类型                | 方向    | 说明
|-----------------|-------------------------|---------|-------------------------------------
| devid           | int                     | 输入    | 设备ID
| extinfos        | linkkit_extinfo_t *     | 输入    | 指向拓展参数结构体数组的指针
| nb_extinfos     | int                     | 输入    | 指明`extinfos`数组中拓展参数的数量
| timeout_ms      | int                     | 输入    | 发送超时时间

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 上报成功
| -1  | 上报失败

-----

### <a name="linkkit_gateway_post_property_json">linkkit_gateway_post_property_json</a>

原型
---
```
int linkkit_gateway_post_property_json(int devid, char *property, int timeout_ms, void (*func)(int retval, void *ctx),
                                       void *ctx)
```

接口说明
---
以JSON格式上报网关或子设备属性, 此接口为非阻塞接口, 当在`timeout_ms`时间内接受到云端应答或出现应答超时将调用用户回调函数

参数说明
---
| 参数        | 数据类型                                | 方向    | 说明
|-------------|-----------------------------------------|---------|-----------------
| devid       | int                                     | 输入    | 设备ID
| property    | char *                                  | 输入    | 属性字符串
| timeout_ms  | int                                     | 输入    | 超时时间
| func        | void (*func)(int retval, void *ctx)     | 输入    | 用户回调函数
| ctx         | void *                                  | 输入    | 用户上下文数据

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 上报成功
| -1  | 上报失败

-----

### <a name="linkkit_gateway_post_property_json_sync">linkkit_gateway_post_property_json_sync</a>

原型
---
```
int linkkit_gateway_post_property_json_sync(int devid, char *property, int timeout_ms);
```

接口说明
---
以JSON格式上报网关或子设备属性, 为同步接口, 接收到云端应答会立即返回, 否则一直等待直到超时发生

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-------------
| devid       | int     | 输入    | 设备ID, 其中devid为0表示网关自身, 为自然数时表示子设备, 在子设备创建时得到
| property    | char *  | 输入    | 属性字符串
| timeout_ms  | int     | 输入    | 超时时间

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 上报成功
| -1  | 上报失败

-----

### <a name="linkkit_gateway_post_rawdata">linkkit_gateway_post_rawdata</a>

原型
---
```
int linkkit_gateway_post_rawdata(int devid, void *data, int len);
```

接口说明
---
上报网关或子设备的裸数据

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------------------
| devid   | int     | 输入    | 设备ID
| data    | void *  | 输入    | 指向用户裸数据的指针
| len     | int     | 输入    | 裸数据的字节长度

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 上报成功
| -1  | 上报失败

-----

### <a name="linkkit_gateway_set_event_callback">linkkit_gateway_set_event_callback</a>

原型
---
```
int linkkit_gateway_set_event_callback(linkkit_params_t *params, int (*event_cb)(linkkit_event_t *ev, void *ctx), void *ctx);
```

接口说明
---
注册网关事件回调函数, 同时加载用户数据

参数说明
---
| 参数        | 数据类型                                            | 方向    | 说明
|-------------|-----------------------------------------------------|---------|-----------------------------------------
| params      | linkkit_params_t *                                  | 输入    | 配置参数, 调用函数`linkkit_gateway_get_default_params()`时返回的参数
| event_cb    | int (*event_cb)(linkkit_event_t *ev, void *ctx)     | 输入    | 网关事件回调函数, 查看`linkkit_event_t`定义
| ctx         | void *                                              | 输入    | 用户数据

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_setopt">linkkit_gateway_setopt</a>

原型
---
```
int linkkit_gateway_setopt(linkkit_params_t *params, int option, void *value, int value_len);
```

接口说明
---
修改网关配置参数, 此数据将在调用`linkkit_gateway_init()`时作为参数传入

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-------------------------------------------------------------
| params      | linkkit_params_t *  | 输入    | 调用`linkkit_gateway_get_default_params()`时返回的参数指针
| option      | int                 | 输入    | 参数选项, 参考下方枚举类型
| value       | void *              | 输入    | 参数, 具体查看对应参数选项
| value_len   | int                 | 输入    | 参数字节长度

```
enum {
    LINKKIT_OPT_MAX_MSG_SIZE        = 1,    /* Reserved */
    LINKKIT_OPT_MAX_MSG_QUEUE_SIZE  = 2,    /* Reserved */
    LINKKIT_OPT_THREAD_POOL_SIZE    = 3,    /* Reserved */
    LINKKIT_OPT_THREAD_STACK_SIZE   = 4,    /* Reserved */
    LINKKIT_OPT_PROPERTY_POST_REPLY = 5,    /* 是否接收属性上报回应, 配置为0时相应回调将会不触发, 参数为int类型 */
    LINKKIT_OPT_EVENT_POST_REPLY    = 6,    /* 是否接收事件上报回应, 配置为0时相应回调将会不触发, 参数为int类型 */
    LINKKIT_OPT_PROPERTY_SET_REPLY  = 7     /* 是否回应云端的属性设置, 参数为int类型 */
};
```

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_start">linkkit_gateway_start</a>

原型
---
```
int linkkit_gateway_start(linkkit_cbs_t *cbs, void *ctx);
```

接口说明
---
启动网关服务, 与云端服务器建立连接

参数说明
---
| 参数    | 数据类型        | 方向    | 说明
|---------|-----------------|---------|-----------------------------------------------------
| cbs     | linkkit_cbs_t*  | 输入    | 指向回调处理函数结构体的指针, 参考`linkkit_cbs_t`
| ctx     | void *          | 输入    | 指向用户数据的指针

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_stop">linkkit_gateway_stop</a>

原型
---
```
int linkkit_gateway_stop(int devid);
```

接口说明
---
停止网关服务, 与云端服务器断开连接

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|---------
| devid   | int     | 输入    | 设备ID

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_subdev_create">linkkit_gateway_subdev_create</a>

原型
---
```
int linkkit_gateway_subdev_create(char *productKey, char *deviceName, linkkit_cbs_t *cbs, void *ctx);
```

接口说明
---
创建由productKey/deviceName指定子设备, 并注册用户回调函数, 同时载入用户数据. 若创建成功,

将返回用于唯一标识设备的ID

参数说明
---
| 参数        | 数据类型            | 方向    | 说明
|-------------|---------------------|---------|-------------------------
| productKey  | char *              | 输入    | 子设备ProductKey字符串
| deviceName  | char *              | 输入    | 子设备DeviceName字符串
| cbs         | linkkit_cbs_t *     | 输入    | 回调处理函数结构体
| ctx         | void *              | 输入    | 指向用户数据的指针

linkkit_cbs_t结构体定义:
```
typedef struct {

    int (*register_complete)(void *ctx);    /* 设备注册完成处理函数 */
    /**
     * @brief get property callback.
     *
     * @param in, properties to be get, in JSON array format, terminated by NULL.
     * @param out, output buffer fill by user, in json format, terminated by NULL.
     * @param out_len, out buffer length.
     * @param ctx, user private data passed by linkkit_gateway_start() or linkkit_gateway_subdev_create()
     *
     * @return 0 when success, -1 when fail.
     */
    int (*get_property)(char *in, char *out, int out_len, void *ctx);

    /**
     * @brief 属性设置处理函数.
     *
     * @param in, 被设置的属性, JSON字符串格式, NULL结尾
     * @param ctx, 由linkkit_gateway_start()或者linkkit_gateway_subdev_create()传入的用户数据
     *
     * @return 0 - 成功, -1 失败.
     */
    int (*set_property)(char *in, void *ctx);

    /**
     * @brief 服务调用处理
     *
     * @param identifier, service标示符, TSL中定义的有效服务
     * @param in, 服务输入数据, JSON字符串, NULL结尾
     * @param out, 服务输出数据的缓冲区, 用户可向缓冲区写入JSON格式的字符串数据, NULL结尾
     * @param out_len, 输出数据缓冲区的字节长度
     * @param ctx, 由linkkit_gateway_start()或者linkkit_gateway_subdev_create()传入的用户数据
     *
     * @return 0 - 成功, -1 - 失败.
     */
    int (*call_service)(char *identifier, char *in, char *out, int out_len, void *ctx);

    /**
     * @brief 云端下发数据
     *
     * @param in, 云端下包的裸数据
     * @param in_len, 下报裸数据的长度
     * @param out, 上报数据的缓冲区, 用户可向缓冲区写入裸数据
     * @param out_len, 上报裸数据的字节长度
     * @param ctx, 由linkkit_gateway_start()或者linkkit_gateway_subdev_create()传入的用户数据
     *
     * @return 上报数据的长度. 操作失败则返回 -1
     */
    ssize_t (*down_rawdata)(const void *in, int in_len, void *out, int out_len, void *ctx);

    /**
     * @brief 调用linkkit_gateway_post_rawdata()的应答处理
     *
     * @param data, 云端返回的裸数据
     * @param len, 裸数据的字节长度
     * @param ctx, 由linkkit_gateway_start()或者linkkit_gateway_subdev_create()传入的用户数据
     *
     * @return 0 - 成功, -1 失败.
     */
    int (*post_rawdata_reply)(const void *data, int len, void *ctx);
} linkkit_cbs_t;
```

返回值说明
---
| 值      | 说明
|---------|-------------------------------------
| > 0     | 子设备创建成功, 返回对应的设备ID
| < 0     | 子设备创建失败

-----

### <a name="linkkit_gateway_subdev_destroy">linkkit_gateway_subdev_destroy</a>

原型
---
```
int linkkit_gateway_subdev_destroy(int devid);
```

接口说明
---
删除识别ID标识的子设备, 回收资源

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|---------
| devid   | int     | 输入    | 设备ID

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 操作成功
| -1  | 操作失败

-----

### <a name="linkkit_gateway_subdev_login">linkkit_gateway_subdev_login</a>

原型
---
```
int linkkit_gateway_subdev_login(int devid);
```

接口说明
---
子设备上线, 云端将可以访问子设备

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|---------
| devid   | int     | 输入    | 设备ID

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 上线成功
| -1  | 上线失败

-----

### <a name="linkkit_gateway_subdev_logout">linkkit_gateway_subdev_logout</a>

原型
---
```
int linkkit_gateway_subdev_logout(int devid);
```

接口说明
---
子设备下线, 云端将无法访问子设备

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|---------
| devid   | int     | 输入    | 设备ID

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

### <a name="linkkit_gateway_subdev_register">linkkit_gateway_subdev_register</a>

原型
---
```
int linkkit_gateway_subdev_register(char *productKey, char *deviceName, char *deviceSecret);
```

接口说明
---
向云端注册productKey/deviceName指定的子设备, 并将子设备加入网关的拓扑关系

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-----------------------------
| productKey      | char *  | 输入    | 子设备ProductKey字符串
| deviceName      | char *  | 输入    | 子设备DeviceName字符串
| deviceSecret    | char *  | 输入    | 子设备DeviceSecret字符串, 若要使用动态注册功能, 此入参应为NULL或者空字符串

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

### <a name="linkkit_gateway_subdev_unregister">linkkit_gateway_subdev_unregister</a>

原型
---
```
int linkkit_gateway_subdev_unregister(char *productKey, char *deviceName);
```

接口说明
---
向云端注销productKey/deviceName指定的子设备, 并将子设备从网关的拓扑关系移除

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|-------------------------
| productKey  | char *  | 输入    | 子设备ProductKey字符串
| deviceName  | char *  | 输入    | 子设备DeviceName字符串

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

### <a name="linkkit_gateway_trigger_event_json">linkkit_gateway_trigger_event_json</a>

原型
---
```
int linkkit_gateway_trigger_event_json(int devid, char *identifier, char *event, int timeout_ms,
                                       void (*func)(int retval, void *ctx), void *ctx);
```

接口说明
---
网关主动上报事件, 异步接口

参数说明
---
| 参数        | 数据类型                                | 方向    | 说明
|-------------|-----------------------------------------|---------|-----------------------------------------------------
| devid       | int                                     | 输入    | 设备ID
| identifier  | char *                                  | 输入    | 事件标示符字符串
| event       | char *                                  | 输入    | 事件的具体参数, 为JSON格式字符串
| timeout_ms  | int                                     | 输入    | 上报超时时间, 单位ms, 若为0则立即返回, 不等待云端回复
| func        | void (*func)(int retval, void *ctx)     | 输入    | 服务器回应到达之后将调用的回调函数
| ctx         | void *                                  | 输入    | SDK调用回调函数`func`时, 传给回调函数的入参

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

### <a name="linkkit_gateway_trigger_event_json_sync">linkkit_gateway_trigger_event_json_sync</a>

原型
---
```
int linkkit_gateway_trigger_event_json_sync(int devid, char *identifier, char *event, int timeout_ms);
```

接口说明
---
网关主动上报事件

参数说明
---
| 参数        | 数据类型| 方向    | 说明
|-------------|---------|---------|---------------------------------------------------------
| devid       | int     | 输入    | 设备ID
| identifier  | char *  | 输入    | 事件标示符字符串
| event       | char *  | 输入    | 事件的具体参数, 为JSON格式字符串
| timeout_ms  | int     | 输入    | 上报超时时间, 单位ms, 若为0则立即返回, 不等待云端回复

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----


