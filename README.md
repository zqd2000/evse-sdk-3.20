# EVSE_SDK快速入门验证

本章描述如何在Ubuntu上通过物模型的编程方式, 上报和接收业务报文. 这个环节使用Ubuntu主机模拟IoT设备, 体验跟云端的连接和交互

## <a name="准备开发环境">准备开发环境</a>

### <a name="安装本地开发环境">安装本地开发环境</a>

#### <a name="安装Ubuntu16.04">安装Ubuntu16.04</a>

本文编写是对照的编译环境是__64位__主机上的`Ubuntu16.04`, 在其它Linux版本上尚未验证过, 推荐安装与阿里一致的发行版以避免碰到兼容性方面的问题

如果您使用`Windows`操作系统, 可以安装虚拟机软件`Virtualbox`获得Linux开发环境, 下载地址: [https://www.virtualbox.org/wiki/Downloads](https://www.virtualbox.org/wiki/Downloads)

然后安装64位的Desktop版本的`Ubuntu 16.04.x LTS`, 下载地址: [http://releases.ubuntu.com/16.04](http://releases.ubuntu.com/16.04)

#### <a name="安装必备软件">安装必备软件</a>

本SDK的开发编译环境使用如下软件: `make-4.1`, `git-2.7.4`, `gcc-5.4.0`, `gcov-5.4.0`, `lcov-1.12`, `bash-4.3.48`, `tar-1.28`, `mingw-5.3.1`, `gawk-4.1.3`

可使用如下命令行安装必要的软件:

```
$ sudo apt-get install -y build-essential make git gcc gawk
```

## <a name="以物模型编程方式接入设备">以物模型编程方式接入设备</a>

### <a name="创建产品和设备">创建产品和设备</a>

可以在阿里云IoT物联网平台以及其上承载的多个行业服务中进行产品的创建, 下面是在阿里云IoT物联网平台创建产品的帮助链接:

* [如何创建支持物模型的产品](https://help.aliyun.com/document_detail/73728.html)
* [如何定义物模型](https://help.aliyun.com/document_detail/73727.html)

---

本示例所属产品的物模型描述文件`model_for_device_example_pile.JSON`存放在`./src/dev_model/examples/`目录下，用户可将该文件中`productkey`替换为自己创建产品的`productKey`，并在 **产品详情** - **功能定义** 页面点击 **导入物模型** 按钮导入到自己创建的产品中。

定义物模型之后云端会为该物模型生成物模型(TSL)描述文件, 该文件使用JSON格式进行描述

### <a name="产品功能实现">产品功能实现</a>

#### <a name="填写设备三元组到例程中">填写设备三元组到例程中</a>

将 `device_example_pile.c` 中的三元组替换成云端创建的设备的三元组

```
char _product_key[IOTX_PRODUCT_KEY_LEN + 1] = "a1X3BP5v0vn";
char _device_name[IOTX_DEVICE_NAME_LEN + 1] = "EvseSdkTestDevice";
char _device_secret[IOTX_DEVICE_SECRET_LEN + 1] = "38be4ad34bd079b4f765f71a3a30fc4e";
```

#### <a name="编译与运行程序">编译与运行程序</a>

在SDK顶层目录执行如下命令:

```
$ make distclean
$ make
```

编译成功完成后, 生成的高级版例子程序在当前路径的 `output/release/bin` 目录下, 名为`device_example_pile`

在SDK顶层目录执行如下命令:

```
$ ./output/release/bin/device_example_pile
```

### <a name="观察数据">观察数据</a>

示例程序会定期将`dcDeRealIty`属性的数值上报云端, 因此可以在云端查看收到的属性。

#### <a name="属性上报">属性上报</a>

示例中使用__evs\_send\_property__作为上报属性的例子. 该示例会循环上报各种情况的payload, 用户可观察在上报错误payload时返回的提示信息:

代码中上报属性的代码片段如下:

```
/* Post Proprety Example */
if ((cnt % 100) == 0)
{
	evs_send_property(EVS_CMD_PROPERTY_DCPILE, &dcPile_data);
}
```

下面是上报正常属性时的日志

```
evs_sdk_state_dump.61: EVS--- received state event, -0x0928(pub-uri: /sys/a1X3BP5v0vn/EvseSdkTestDevice/thing/event/propert)
```

这里是发送给云端的消息

```
> {
>     "id": "44",
>     "version": "1.0",
>     "params": {
>         "dcDeRealIty": {
>             "netType": 13,
>             "sigVal": 31,
>             "netId": 11,
>             "acVolA": 380,
>             "acCurA": 380,
>             "acVolB": 380,
>             "acCurB": 380,
>             "acVolC": 380,
>             "acCurC": 380,
>             "caseTemp": 100,
>             "inletTemp": 70,
>             "outletTemp": 30,
>             "eleModelId": "111111111111",
>             "serModelId": "111111111111"
>         }
>     },
>     "method": "thing.event.property.post"
> }
```

收到的云端应答

```
< {
<     "code": 200,
<     "data": {
<     },
<     "id": "44",
<     "message": "success",
<     "method": "thing.event.property.post",
<     "version": "1.0"
< }
```

用户回调函数的日志

```
evs_report_reply_event_handler.42: EVS--- Message Post Reply Received, Message ID: 44, Code: 200, Reply: {}
```



#### <a name="事件上报">事件上报</a>

示例中使用 `evs_send_event` 上报属性. 该示例会循环上报各种情况的payload, 用户可观察在上报错误payload时返回的提示信息:

正常上报事件的情况

```
if ((cnt % 200) == 0)
{
	evs_send_event(EVS_CMD_EVENT_FIREWARE_INFO, &fireware_info);
}
```

示例程序中 `fireware_info` 事件(Event)是约每20s上报一次, 在以上各种情况中循环. 其中正常上报的日志如下:

```
evs_sdk_state_dump.61: EVS--- received state event, -0x0928(pub-uri: /sys/a1X3BP5v0vn/EvseSdkTestDevice/thing/event/firmwar)
```

向云端上报的事件消息内容及日志

```
> {
>     "id": "45",
>     "version": "1.0",
>     "params": {
>         "simNo": "111111111111111111",
>         "eleModelId": "1111aaaabbccdd",
>         "stakeModel": "222111111111111111",
>         "devSn": "2222aaaabbccdd",
>         "serModelId": "1111aaaabbccdd",
>         "stakeModel": "222111111111111111",
>         "simMac": "aa: bb: cc: d",
>         "btMac": "aa: bb: cc: dd",
>         "vendorCode": 1287,
>         "devType": 10,
>         "portNum": 1,
>         "longitude": 0,
>         "latitude": 0,
>         "height": 100,
>         "gridType": 12,
>         "meaType": 10,
>         "otRate": 70,
>         "otMaxVol": 500,
>         "otMinVol": 220,
>         "otCur": 380,
>         "CT": 30,
>         "isGateLock": 10,
>         "isGroundLock": 10,
>         "inMeter": [
>             "122334455667"
>         ],
>         "outMeter": [
>             "122334455667"
>         ]
>     },
>     "method": "thing.event.firmwareEvt.post"
> }

```

从云端收到的应答消息内容及日志

```
< {
<     "code": 200,
<     "data": {
<     },
<     "id": "45",
<     "message": "success",
<     "method": "thing.event.firmwareEvt.post",
<     "version": "1.0"
< }

evs_sdk_state_dump.61: EVS--- received state event, -0x0927(cloud response msgid: 45, code: 200, data: {})
```

用户回调函数 `evs_trigger_event_reply_event_handler()` 中的日志:

```
evs_trigger_event_reply_event_handler.53: EVS--- Trigger Event Reply Received, Message ID: 45, Code: 200, EventID: firmwareEvt, Message: success
^[aevs_sdk_state_dump.61: EVS--- received state event, -0x0928(pub-uri: /sys/a1X3BP5v0vn/EvseSdkTestDevice/thing/event/propert)
```

#### <a name="服务调用">服务调用</a>

注册服务消息的处理函数

```
EVS_RegisterCallback(EVS_START_CHARGE_SRV, callback_service_startCharge);
```

收到服务请求消息时, 会进入下面的回调函数。设备端演示了一个简单的加法运算服务，入参为`evs_service_startCharge`结构体指针，出参为`evs_service_feedback_startCharge`指针，例程中使用入参结构体参数直接拷入出参结构体参数做出参。

```
int callback_service_startCharge(evs_service_startCharge *param, evs_service_feedback_startCharge *result)
{
	memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
	memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
	result->gunNo = param->gunNo + 1;
	DEVICE_EXAMPLE_TRACE("callback_service_startCharge:param is gunNo:%d,result is tradeNo:%s \n", param->gunNo, result->tradeNo);
	return 0;
}
```

在阿里云平台在线调试输入如下参数

![image-20200630140950556]( https://raw.githubusercontent.com/zqd2000/evse-sdk-3.20/master/tmp/image-20200630140950556.png )

此时在设备端可以看到如下日志

收到的云端的服务调用, 输入参数如下。

```
< {
<     "method": "thing.service.startChargeSrv",
<     "id": "981962794",
<     "params": {
<         "stopCode": 123456,
<         "gunNo": 1,
<         "tradeNo": "123456",
<         "chargeMode": 11,
<         "limitData": 10,
<         "insertGunTime": 1593159410,
<         "startMode": 10,
<         "preTradeNo": "1234567893458668891569898869997",
<         "startType": 13
<     },
<     "version": "1.0.0"
< }

evs_sdk_state_dump.61: EVS--- received state event, -0x0927(cloud request msgid: 981962794, method: thing.service.startChar)
```

在回调函数中将 输入参数中的`gunNo` 加 `1`的值相加后赋值给 输出参数中的`gunNo` 后, 上报到云端

```
> {
>     "id": "981962794",
>     "code": 200,
>     "data": {
>         "preTradeNo": "1234567893458668891569898869997",
>         "tradeNo": "1234567893458668891569898869997",
>         "gunNo": 2
>     }
> }
```

###### 阿里云原生SDK数据

# 用户手册

https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/Linkkit_User_Manual

# C-SDK 简介

设备厂商在设备上集成 `C-SDK` 后, 可以将设备安全的接入到阿里云IoT物联网平台, 从而使设备可以被阿里云IoT物联网平台进行管理

设备需要支持TCP/IP协议栈或串口通信, 以及C99标准的C库才能集成SDK, zigbee/433/KNX这样的非IP设备需要通过网关设备接入到阿里云IoT物联网平台, 网关设备需要集成C-SDK


# 快速开始

用户可以通过[快速的体验C-SDK](https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Quick_Start)感受如何将设备连接到阿里云物联网平台, 并如何将设备的数据发送到平台/以及如何从物联网平台接收数据


# 移植说明
C-SDK与OS/硬件平台无关, 全部部分用C编写, 它定义了HAL层来对接与硬件相关的功能, 因此在使用C-SDK时用户需要去实现相关的HAL函数

目前C-SDK已提供了在Linux/Windows上HAL的参考实现, 同时对于一些常见的OS或者模组也进行了适配, 可以[访问此处](https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Port_Guide/Porting_Overview)查看如何在相应平台上进行SDK的编译与集成


# 编程文档

SDK提供了一系列的编程文档来描述如何使用SDK提供的软件功能, 请[访问此处](https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/Linkkit_User_Manual)进行了解

# 变更说明
20200605 在阿里SDK-3.20基础上进行了协议层框架封装

20200623 基础功能基本完善，修改设备唯一编码长度宏定义名称，进行第一轮测试

20200630 发布V1.0版本 