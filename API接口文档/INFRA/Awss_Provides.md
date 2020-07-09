# <a name="目录">目录</a>
+ [WIFI provisoion API详解](#WIFI provisoion API详解)
    * [awss_start](#awss_start)
    * [awss_stop](#awss_stop)
    * [awss_config_press](#awss_config_press)
    * [awss_dev_ap_start](#awss_dev_ap_start)
    * [awss_dev_ap_stop](#awss_dev_ap_stop)
    * [awss_report_cloud](#awss_report_cloud)
    * [awss_report_reset](#awss_report_reset)
    * [iotx_event_regist_cb](#iotx_event_regist_cb)

# <a name="WIFI provisoion API详解">WIFI provisoion API详解</a>

## <a name="awss_start">awss_start</a>

原型
---
```
int awss_start(void);
```

接口说明
---
启动配网服务

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|-------------
| 0   | 成功
| -1  | 启动失败

-----

## <a name="awss_stop">awss_stop</a>

原型
---
```
int awss_stop();
```

接口说明
---
停止配网服务

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

## <a name="awss_config_press">awss_config_press</a>

原型
---
```
int awss_config_press();
```

接口说明
---
使能配网，开始解awss报文

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败


-----

## <a name="awss_dev_ap_start">awss_dev_ap_start</a>

原型
---
```
int awss_dev_ap_start();
```

接口说明
---
启动设备热点配网，与awss_start互斥

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

## <a name="awss_dev_ap_stop">awss_dev_ap_stop</a>

原型
---
```
int awss_dev_ap_stop();
```

接口说明
---
停止设备热点配网

参数说明
---
void 

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

## <a name="awss_report_cloud">awss_report_cloud</a>

原型
---
```
int awss_report_cloud();
```

接口说明
---
启动绑定服务，上报绑定信息

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

## <a name="awss_report_reset">awss_report_reset</a>

原型
---
```
int awss_report_reset();
```

接口说明
---
向云端上报解除绑定消息

参数说明
---
void

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败

-----

-----

## <a name="iotx_event_regist_cb">iotx_event_regist_cb</a>

原型
---
```
int iotx_event_regist_cb(void (*monitor_cb)(int event));
```

接口说明
---
注册包括配网绑定在内的linkkit事件通知回调函数

参数说明
---
```
void (*monitor_cb)(int event)
```

用户需要注册事件回调函数原型。

event为配网绑定相关事件，具体如下：

```
enum iotx_event_t {
    IOTX_AWSS_START = 0x1000,       /* AWSS start without enbale, just supports device discover */
    IOTX_AWSS_ENABLE,               /* AWSS enable */
    IOTX_AWSS_LOCK_CHAN,            /* AWSS lock channel(Got AWSS sync packet) */
    IOTX_AWSS_CS_ERR,               /* AWSS AWSS checksum is error */
    IOTX_AWSS_PASSWD_ERR,           /* AWSS decrypt passwd error */
    IOTX_AWSS_GOT_SSID_PASSWD,      /* AWSS parse ssid and passwd successfully */
    IOTX_AWSS_CONNECT_ADHA,         /* AWSS try to connnect adha (device discover, router solution) */
    IOTX_AWSS_CONNECT_ADHA_FAIL,    /* AWSS fails to connect adha */
    IOTX_AWSS_CONNECT_AHA,          /* AWSS try to connect aha (AP solution) */
    IOTX_AWSS_CONNECT_AHA_FAIL,     /* AWSS fails to connect aha */
    IOTX_AWSS_SETUP_NOTIFY,         /* AWSS sends out device setup information (AP and router solution) */
    IOTX_AWSS_CONNECT_ROUTER,       /* AWSS try to connect destination router */
    IOTX_AWSS_CONNECT_ROUTER_FAIL,  /* AWSS fails to connect destination router. */
    IOTX_AWSS_GOT_IP,               /* AWSS connects destination successfully and got ip address */
    IOTX_AWSS_SUC_NOTIFY,           /* AWSS sends out success notify (AWSS sucess) */
    IOTX_AWSS_BIND_NOTIFY,          /* AWSS sends out bind notify information to support bind between user and device */
    IOTX_AWSS_ENABLE_TIMEOUT,       /* AWSS enable timeout(user needs to call awss_config_press again to enable awss) */
    IOTX_CONN_CLOUD = 0x2000,       /* Device try to connect cloud */
    IOTX_CONN_CLOUD_FAIL,           /* Device fails to connect cloud, refer to net_sockets.h for error code */
    IOTX_CONN_CLOUD_SUC,            /* Device connects cloud successfully */
    IOTX_RESET = 0x3000,            /* Linkkit reset success (just got reset response from cloud without any other operation) */
};
```

返回值说明
---
| 值  | 说明
|-----|---------
| 0   | 成功
| -1  | 失败


