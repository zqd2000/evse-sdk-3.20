# <a name="目录">目录</a>

* [SDk协议API详解](#SDk协议API详解)
    - [evs_linkkit_new](#evs_linkkit_new)
    - [evs_linkkit_time_sync](#evs_linkkit_time_sync)
    - [evs_linkkit_fota](#evs_linkkit_fota)
    - [evs_linkkit_free](#evs_linkkit_free)
    - [evs_mainloop](#evs_mainloop)
    - [evs_send_event](#evs_send_event)
    - [evs_send_property](#evs_send_property)
* [Event列表详解](#Event列表详解)
    - [EVS_CMD_EVENT_FIREWARE_INFO](#EVS_CMD_EVENT_FIREWARE_INFO)
    - [EVS_CMD_EVENT_ASK_FEEMODEL](#EVS_CMD_EVENT_ASK_FEEMODEL)
    - [EVS_CMD_EVENT_STARTCHARGE](#EVS_CMD_EVENT_STARTCHARGE)
    - [EVS_CMD_EVENT_STARTRESULT](#EVS_CMD_EVENT_STARTRESULT)
    - [EVS_CMD_EVENT_STOPCHARGE](#EVS_CMD_EVENT_STOPCHARGE)
    - [EVS_CMD_EVENT_TRADEINFO](#EVS_CMD_EVENT_TRADEINFO)
    - [EVS_CMD_EVENT_ALARM](#EVS_CMD_EVENT_ALARM)
    - [EVS_CMD_EVENT_ACPILE_CHANGE](#EVS_CMD_EVENT_ACPILE_CHANGE)
    - [EVS_CMD_EVENT_DCPILE_CHANGE](#EVS_CMD_EVENT_DCPILE_CHANGE)
    - [EVS_CMD_EVENT_GROUNDLOCK_CHANGE](#EVS_CMD_EVENT_GROUNDLOCK_CHANGE)
    - [EVS_CMD_EVENT_GATELOCK_CHANGE](#EVS_CMD_EVENT_GATELOCK_CHANGE)
    - [EVS_CMD_EVENT_ASK_DEV_CONFIG](#EVS_CMD_EVENT_ASK_DEV_CONFIG)
    - [EVS_CMD_EVENT_CAR_INFO](#EVS_CMD_EVENT_CAR_INFO)
* [Poperty列表详解](#Poperty列表详解)
    - [EVS_CMD_PROPERTY_DCPILE](#EVS_CMD_PROPERTY_DCPILE)
    - [EVS_CMD_PROPERTY_ACPILE](#EVS_CMD_PROPERTY_ACPILE)
    - [EVS_CMD_PROPERTY_AC_WORK](#EVS_CMD_PROPERTY_AC_WORK)
    - [EVS_CMD_PROPERTY_AC_NONWORK](#EVS_CMD_PROPERTY_AC_NONWORK)
    - [EVS_CMD_PROPERTY_DC_WORK](#EVS_CMD_PROPERTY_DC_WORK)
    - [EVS_CMD_PROPERTY_DC_NONWORK](#EVS_CMD_PROPERTY_DC_NONWORK)
    - [EVS_CMD_PROPERTY_DC_OUTMETER](#EVS_CMD_PROPERTY_DC_OUTMETER)
    - [EVS_CMD_PROPERTY_AC_OUTMETER](#EVS_CMD_PROPERTY_AC_OUTMETER)
    - [EVS_CMD_PROPERTY_BMS](#EVS_CMD_PROPERTY_BMS)
    - [EVS_CMD_PROPERTY_DC_INPUT_METER](#EVS_CMD_PROPERTY_DC_INPUT_METER)
* [Service回调列表](#Service回调列表)

# <a name="SDk协议API详解">SDk协议API详解</a>

> 补充说明: JSON报文中, 消息id取值范围 `0~4294967295` , id是String类型的数字，如"12345"

## <a name="evs_linkkit_new">evs_linkkit_new</a>

原型
---

``` 
int evs_linkkit_new(const int evs_is_ready,const int is_device_uid);
```

接口说明
---
初始化SDK资源, 在对SDK进行操作之前, 必须先调用此接口.

参数说明
---

| 参数            | 数据类型   | 方向    | 说明
|-----------------|-----------|---------|-------------------------------------------
| evs_is_ready    | const int | 输入    | 1: 设备准备就绪 0: 设备未准备就绪
| is_device_uid   | const int | 输入    | 0: 使用注册码获取证书 1: 使用设备唯一编码获取证书

返回值说明
---
| 值     | 说明
|--------|-----------------
| 0      | 创建设备成功
| -1     | 设备未准备就绪
| -2     | 获取设备注册码失败
| -3     | 设置设备证书失败

-----

## <a name="evs_linkkit_time_sync">evs_linkkit_time_sync</a>

原型
---

``` 
int evs_linkkit_time_sync(void);
```

接口说明
---
对于主设备来说, 将会建立设备与云端的通信. 对于子设备来说, 将向云端注册该子设备(如果需要的话), 并添加主子设备拓扑关系

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 1       | 失败

-----

## <a name="evs_linkkit_fota">evs_linkkit_fota</a>

原型
---

``` 
void evs_linkkit_fota(unsigned char *buffer, int buffer_length);
```

接口说明
---
当iot平台连下发新固件升级通知时，通过该函数进行ota固件包下载

参数说明
---
| 参数            | 数据类型      | 方向    | 说明
|----------------|---------------|---------|-------------------------------------------------
| buffer         | unsigned char | 输入    | 固件接收缓存区
| buffer_length  | int           | 输入    | 缓存区长度

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 1       | 失败

-----

## <a name="evs_linkkit_free">evs_linkkit_free</a>

原型
---

``` 
int evs_linkkit_free(void);
```

接口说明
---
若设备ID为主设备, 则关闭网络连接并释放Linkkit所有占用资源

参数说明
---
无入参

返回值说明
---
| 值      | 说明
|---------|---------
| 0       | 成功
| 1       | 失败

-----

## <a name="evs_mainloop">evs_mainloop</a>

原型
---

``` 
int evs_mainloop(void);
```

接口说明
---
SDK功能运行函数

参数说明
---
无入参

返回值说明
---
| 值      | 说明
|---------|---------
| -1    | 设备linkkit打开失败
| -2     | 设备linkkit打开重试等待
| -3     | 设备linkkit连接失败
| -4     | 设备linkkit连接重试等待

-----

## <a name="evs_send_event">evs_send_event</a>

原型
---

``` 
void evs_send_event(evs_cmd_event_enum event_type, void *param);
```

接口说明
---
向云端发送事件消息。

参数说明
---

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|----------------------------|---------|---------------------
| event_type      | evs_cmd_event_enum         | 输入    | 发送事件类型
| param           | void*                      | 输入    | 发送参数

返回值说明
---
无返回值

参数附加说明
---

``` 
typedef enum
{
	EVS_CMD_EVENT_FIREWARE_INFO,
	EVS_CMD_EVENT_ASK_FEEMODEL,
	EVS_CMD_EVENT_STARTCHARGE,
	EVS_CMD_EVENT_STARTRESULT,
	EVS_CMD_EVENT_STOPCHARGE,
	EVS_CMD_EVENT_TRADEINFO,
	EVS_CMD_EVENT_ALARM,
	EVS_CMD_EVENT_ACPILE_CHANGE,
	EVS_CMD_EVENT_DCPILE_CHANGE,
	EVS_CMD_EVENT_GROUNDLOCK_CHANGE,
	EVS_CMD_EVENT_GATELOCK_CHANGE,
	EVS_CMD_EVENT_ASK_DEV_CONFIG,
} evs_cmd_event_enum;

```

----

## <a name="evs_send_property">evs_send_property</a>

原型
---

``` 
void evs_send_property(evs_cmd_property_enum property_type, void *param);
```

接口说明
---
向云端发送设备属性信息

参数说明
---

| 参数            | 数据类型                    | 方向    | 说明
|-----------------|-----------------------------|---------|---------------------
| property_type   | evs_cmd_property_enum       | 输入    | 发送属性类型
| param           | void*                       | 输入    | 发送参数

返回值说明
---
无返回值

参数附加说明
---

``` 
typedef enum
{
	EVS_CMD_PROPERTY_DCPILE,
	EVS_CMD_PROPERTY_ACPILE,
	EVS_CMD_PROPERTY_AC_WORK,
	EVS_CMD_PROPERTY_AC_NONWORK,
	EVS_CMD_PROPERTY_DC_WORK,
	EVS_CMD_PROPERTY_DC_NONWORK,
	EVS_CMD_PROPERTY_DC_OUTMETER,
	EVS_CMD_PROPERTY_AC_OUTMETER,
	EVS_CMD_PROPERTY_BMS,
	EVS_CMD_PROPERTY_DC_INPUT_METER,
} evs_cmd_property_enum;
```

-----

## <a name="EVS_RegisterCallback">EVS_RegisterCallback</a>

原型
---

``` 
define EVS_RegisterCallback(evt, cb)           EVS_RegisterCallback##evt(cb);
```

接口说明
---
该接口用于注册SDK服务的回调函数, 当SDK产生消息时, 会调用对应的回调函数

参数说明
---

| 参数     | 数据类型                    | 方向    | 说明
|---------|-----------------------------|---------|-------------
| evt     | evs_service_type_t          | 输入    | 服务名称
| cb      | 根据evt的不同而各有不同       | 输入    | 回调函数

-----
返回值说明
---
无返回值

参数附加说明
---

``` 
typedef enum
{
    EVS_CONF_GET_SRV,
    EVS_CONF_UPDATE_SRV,
    EVS_QUE_DARA_SRV,
    EVS_DEV_MAINTAIN_SRV,
    EVS_CTRL_LOCK_SRV,
    EVS_FEE_MODEL_UPDATA_SRV,
    EVS_START_CHARGE_SRV,
    EVS_AUTH_RESULT_SRV,
    EVS_STOP_CHARGE_SRV,
    EVS_ORDER_CHECK_SRV,
    EVS_RSV_CHARGE_SRV,
    EVS_GROUND_LOCK_SRV,
    EVS_GATE_LOCK_SRV,
    EVS_ORDERLY_CHARGE_SRV,
  
    EVS_STATE_EVERYTHING,
    EVS_CONNECT_SUCC,
    EVS_DISCONNECTED,
    EVS_REPORT_REPLY,
    EVS_TRIGGER_EVENT_REPLY,
    EVS_CERT_GET,
    EVS_CERT_SET,
    EVS_DEVICE_REG_CODE_GET,
    EVS_DEVICE_UID_GET,
    EVS_TIME_SYNC,
    EVS_OTA_UPDATE,

} evs_service_type_t;
```

# <a name="Event列表详解">Event列表详解</a>

### <a name="EVS_CMD_EVENT_FIREWARE_INFO">EVS_CMD_EVENT_FIREWARE_INFO</a>

* 设备固件信息数据上报参数详情

``` 
typedef struct
{
	char simNo[EVS_MAX_ICCID_LEN];								   // 1		SIM卡号
	char eleModelId[EVS_MAX_MODEL_ID_LEN];						   // 2		电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN];						   // 3		服务费模型编号
	char stakeModel[EVS_MAX_PILE_TYPE_LEN];						   // 4		充电桩型号
	unsigned int vendorCode;									   // 5		生产厂商编码
	char devSn[EVS_MAX_DEV_SN_LEN];								   // 6		出厂编号//字符串
	unsigned char devType;										   // 7		桩类型
	unsigned char portNum;										   // 8		充电接口数量
	char simMac[EVS_MAX_MAC_ADDR_LEN];							   // 9		网络MAC地址//字符串
	unsigned int longitude;										   // 10		经度
	unsigned int latitude;										   // 11		纬度
	unsigned int height;										   // 12		高度
	unsigned int gridType;										   // 13		坐标类型
	char btMac[EVS_MAX_MAC_ADDR_LEN];							   // 14		系统时钟字符串
	unsigned char meaType;										   // 15		蓝牙MAC地址
	unsigned int otRate;										   // 16		计量方式
	unsigned int otMinVol;										   // 17		额定功率
	unsigned int otMaxVol;										   // 18		输出最大电压
	unsigned int otCur;											   // 19		输出最大电流
	char inMeter[EVS_MAX_INPUT_METER_NUM][EVS_MAX_METER_ADDR_LEN]; // 20		交流输入电表地址//压缩BCD
	char outMeter[EVS_MAX_PORT_NUM][EVS_MAX_METER_ADDR_LEN];	   // 21		计量用电能表地址//压缩BCD
	unsigned int CT;											   // 22		电流互感器系数 默认值1
	unsigned char isGateLock;									   // 23		是否有智能门锁
	unsigned char isGroundLock;									   // 24		是否有地锁
} evs_event_fireware_info;
```

### <a name="EVS_CMD_EVENT_ASK_FEEMODEL">EVS_CMD_EVENT_ASK_FEEMODEL</a>

* 设备计费模型请求上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				   // 1	充电枪编号
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 2	电费计费模型编号
	char serModeId[EVS_MAX_MODEL_ID_LEN];  // 2	服务费模型编号
} evs_event_ask_feeModel;
```

### <a name="EVS_CMD_EVENT_STARTCHARGE">EVS_CMD_EVENT_STARTCHARGE</a>

* 设备启动充电请求上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char startType;			// 4	启动方式
	char authCode[EVS_MAX_CAR_VIN_LEN]; // 5	鉴权码 若启动方式为反向扫码，填入二维码信息；若为即插即充则为VIN码。
	unsigned char batterySOC;			// 6	电池SOC
	unsigned int batteryCap;			// 7	电车容量
	unsigned int chargeTimes;			// 8	已充电次数
	unsigned int batteryVol;			// 9	当前电池电压
} evs_event_startCharge;
```

### <a name="EVS_CMD_EVENT_STARTRESULT">EVS_CMD_EVENT_STARTRESULT</a>

* 设备启动充电结果上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char startResult;			// 4	启动结果
	unsigned int faultCode;				// 5	故障代码
	char vinCode[EVS_MAX_CAR_VIN_LEN];	// 6	vin码
} evs_event_startResult;
```

### <a name="EVS_CMD_EVENT_STOPCHARGE">EVS_CMD_EVENT_STOPCHARGE</a>

* 设备停止充电结果上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char stopResult;			// 4	停止结果
	unsigned int resultCode;			// 5	停止原因
	unsigned char stopFailReson;		// 6	停止失败原因
} evs_event_stopCharge;
```

### <a name="EVS_CMD_EVENT_TRADEINFO">EVS_CMD_EVENT_TRADEINFO</a>

* 交易记录事件上传参数详情

``` 
typedef struct
{
	unsigned char gunNo;				   // 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN];	   // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	   // 3	设备交易流水号
	char vinCode[EVS_MAX_CAR_VIN_LEN];	   // 4	VIN
	unsigned char timeDivType;			   // 5	计量计费类型
	unsigned int chargeStartTime;		   // 6	开始充电时间
	unsigned int chargeEndTime;			   // 7	结束充电时间
	unsigned char startSoc;				   // 8	启动时SOC
	unsigned char endSoc;				   // 9	停止时SOC
	unsigned int reason;				   // 10	停止充电原因
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 11	计量计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 11	计量计费模型编号
	unsigned int sumStart;				   // 12	电表总起示值
	unsigned int sumEnd;				   // 13	电表总止示值
	unsigned int totalElect;			   // 14	总电量
	unsigned int sharpElect;			   // 15	尖电量
	unsigned int peakElect;				   // 16	峰电量
	unsigned int flatElect;				   // 17	平电量
	unsigned int valleyElect;			   // 18	谷电量
	unsigned int totalPowerCost;		   // 19	总电费
	unsigned int totalServCost;			   // 20	总服务费
	unsigned int sharpPowerCost;		   // 21	尖电费
	unsigned int peakPowerCost;			   // 22	峰电费
	unsigned int flatPowerCost;			   // 23	平电费
	unsigned int valleyPowerCost;		   // 24	谷电费
	unsigned int sharpServCost;			   // 25	尖服务费
	unsigned int peakServCost;			   // 26	峰服务费
	unsigned int flatServCost;			   // 27	平服务费
	unsigned int valleyServCost;		   // 28	谷服务费
} evs_event_tradeInfo;
```

### <a name="EVS_CMD_EVENT_ALARM">EVS_CMD_EVENT_ALARM</a>

* 故障告警事件上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;						  // 1	枪编号
	unsigned short faultSum;					  // 2	故障总
	unsigned short warnSum;						  // 3	告警总
	unsigned short faultValue[EVS_MAX_ALARM_LEN]; // 4	故障点数据
	unsigned short warnValue[EVS_MAX_ALARM_LEN];  // 5	告警点数据
} evs_event_alarm;
```

### <a name="EVS_CMD_EVENT_ACPILE_CHANGE">EVS_CMD_EVENT_ACPILE_CHANGE</a>

* 交流设备状态变更信息上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;		   // 1	充电枪编号
	unsigned int yxOccurTime;	   // 2	发生时刻
	unsigned char connCheckStatus; // 3	变位点数据
} evs_event_pile_stutus_change;
```

### <a name="EVS_CMD_EVENT_DCPILE_CHANGE">EVS_CMD_EVENT_DCPILE_CHANGE</a>

* 直流设备状态变更信息上报详情

``` 
typedef struct
{
	unsigned char gunNo;		   // 1	充电枪编号
	unsigned int yxOccurTime;	   // 2	发生时刻
	unsigned char connCheckStatus; // 3	变位点数据
} evs_event_pile_stutus_change;
```

### <a name="EVS_CMD_EVENT_GROUNDLOCK_CHANGE">EVS_CMD_EVENT_GROUNDLOCK_CHANGE</a>

* 智能地锁状态变更信息上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;		// 1	充电枪编号
	unsigned char lockState;	// 2	地锁状态
	unsigned char powerType;	// 3	供电方式
	unsigned char cellState;	// 4	电池状态
	unsigned char lockerState;	// 5	锁舌状态
	unsigned char lockerForced; // 6	锁舌受外力强制动作
	unsigned char lowPower;		// 7	电池低电量报警
	unsigned char soc;			// 8	电池SOC
	unsigned int openCnt;		// 9	开闭次数
} evs_event_groundLock_change;
```

### <a name="EVS_CMD_EVENT_GATELOCK_CHANGE">EVS_CMD_EVENT_GATELOCK_CHANGE</a>

* 智能门锁状态变更信息上报参数详情

``` 
typedef struct
{
	unsigned char lockNo;	 // 1	充电枪编号
	unsigned char lockState; // 2	智能门锁状态
} evs_event_gateLock_change;
```

### <a name="EVS_CMD_EVENT_ASK_DEV_CONFIG">EVS_CMD_EVENT_ASK_DEV_CONFIG</a>

* 获取设备配置信息请求上报

``` 
无
```

### <a name="EVS_CMD_EVENT_CAR_INFO">EVS_CMD_EVENT_CAR_INFO</a>

* 充电前车辆信息上报事件

``` 
typedef struct
{
	unsigned char gunNo;			    // 1	充电枪编号
	unsigned char batterySOC;		    // 2	电池SOC
	unsigned int batteryCap;		    // 3	电车容量
	char vinCode[EVS_MAX_CAR_VIN_LEN];	// 4	vin码
	unsigned char state;			    // 5	获取车辆信息状态
} evs_event_car_info;
```

# <a name="Poperty列表详解">Poperty列表详解</a>

### <a name="EVS_CMD_PROPERTY_DCPILE">EVS_CMD_PROPERTY_DCPILE</a>

* 直流设备属性上报参数详情

``` 
typedef struct
{
	unsigned char netType;				   // 1	网络类型
	unsigned char sigVal;				   // 2	网络信号等级
	unsigned char netId;				   // 3	网络运营商
	unsigned int acVolA;				   // 4	A相采集电压
	unsigned int acCurA;				   // 5	A相采集电流
	unsigned int acVolB;				   // 6	B相采集电压
	unsigned int acCurB;				   // 7	B相采集电流
	unsigned int acVolC;				   // 8	C相采集电压
	unsigned int acCurC;				   // 9	C相采集电流
	unsigned short caseTemp;			   // 10 设备内温度
	unsigned short inletTemp;			   // 11 设备入风口温度
	unsigned short outletTemp;			   // 12 设备出风口温度
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 13 电费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 14 服务费模型编号
} evs_property_dcPile;
```

### <a name="EVS_CMD_PROPERTY_ACPILE">EVS_CMD_PROPERTY_ACPILE</a>

* 交流设备属性上报参数详情

``` 
typedef struct
{
	unsigned char netType;				   // 1	网络类型
	unsigned char sigVal;				   // 2	网络信号等级
	unsigned char netId;				   // 3	网络运营商
	unsigned int acVolA;				   // 4	A相采集电压
	unsigned int acCurA;				   // 5	A相采集电流
	unsigned int acVolB;				   // 6	B相采集电压
	unsigned int acCurB;				   // 7	B相采集电流
	unsigned int acVolC;				   // 8	C相采集电压
	unsigned int acCurC;				   // 9	C相采集电流
	unsigned short caseTemp;			   // 10 桩内温度
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 11 电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 12 服务费模型编号
} evs_property_acPile;
```

### <a name="EVS_CMD_PROPERTY_AC_WORK">EVS_CMD_PROPERTY_AC_WORK</a>

* : 交流设备充电过程实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	unsigned char workStatus;			// 3	工作状态
	unsigned char conStatus;			// 4	连接确认开关状态
	unsigned char outRelayStatus;		// 5	输出继电器状态
	unsigned char eLockStatus;			// 6	充电接口电子锁状态
	unsigned short gunTemp;				// 7	充电枪头温度
	unsigned int acVolA;				// 8	充电设备A相输出电压
	unsigned int acCurA;				// 9	充电设备A相输出电流
	unsigned int acVolB;				// 10	充电设备B相输出电压
	unsigned int acCurB;				// 11	充电设备B相输出电流
	unsigned int acVolC;				// 12	充电设备C相输出电压
	unsigned int acCurC;				// 13	充电设备C相输出电流
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 14	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 15	设备交易流水号
	unsigned int realPower;				// 16	充电实际功率
	unsigned int chgTime;				// 17	累计充电时间
	unsigned int totalElect;			// 18	总电量
	unsigned int sharpElect;			// 19	尖电量
	unsigned int peakElect;				// 20	峰电量
	unsigned int flatElect;				// 21	平电量
	unsigned int valleyElect;			// 22	谷电量
	unsigned int totalCost;				// 23	总金额
	unsigned int totalPowerCost;		// 24	总电费
	unsigned int totalServCost;			// 25	总服务费
	unsigned int PwmDutyRadio;			// 26	PWM占空比
} evs_property_ac_work;
```

### <a name="EVS_CMD_PROPERTY_AC_NONWORK">EVS_CMD_PROPERTY_AC_NONWORK</a>

* 交流设备非充电过程实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;		  // 1	充电枪编号
	unsigned char workStatus;	  // 3	工作状态
	unsigned char conStatus;	  // 4	连接确认开关状态
	unsigned char outRelayStatus; // 5	输出继电器状态
	unsigned char eLockStatus;	  // 6	充电接口电子锁状态
	unsigned short gunTemp;		  // 7	充电枪头温度
	unsigned int acVolA;		  // 8	充电设备A相输出电压
	unsigned int acCurA;		  // 9	充电设备A相输出电流
	unsigned int acVolB;		  // 10	充电设备B相输出电压
	unsigned int acCurB;		  // 11	充电设备B相输出电流
	unsigned int acVolC;		  // 12	充电设备C相输出电压
	unsigned int acCurC;		  // 13	充电设备C相输出电流
} evs_property_ac_nonWork;
```

### <a name="EVS_CMD_PROPERTY_DC_WORK">EVS_CMD_PROPERTY_DC_WORK</a>

* 直流设备充电过程实时属性上报详情

``` 
typedef struct
{
	unsigned char gunNo;				// 充电枪编号
	unsigned char workStatus;			// 工作状态
	unsigned char gunStatus;			// 充电枪连接状态
	unsigned char eLockStatus;			// 充电枪电子锁状态
	unsigned char DCK1Status;			// 直流输出接触器K1状态
	unsigned char DCK2Status;			// 直流输出接触器K2状态
	unsigned char DCPlusFuseStatus;		// DC+熔断器状态
	unsigned char DCMinusFuseStatus;	// DC-熔断器状态
	unsigned short conTemp1;			// 充电接口DC+温度
	unsigned short conTemp2;			// 充电接口DC-温度
	unsigned int dcVol;					// 输出电压
	unsigned int dcCur;					// 输出电流
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 设备交易流水号
	unsigned char chgType;				// 充电类型
	unsigned int realPower;				// 充电设备输出功率
	unsigned int chgTime;				// 累计充电时间
	unsigned char socVal;				// SOC
	unsigned short needVol;				// 充电需求电压
	unsigned short needCur;				// 充电需求电流
	unsigned char chargeMode;			// 充电模式
	unsigned short bmsVol;				// BMS充电电压测量值
	unsigned short bmsCur;				// BMS充电电流测量值
	unsigned short SingleMHV;			// 最高单体动力蓄电池电压
	unsigned short remainT;				// 估算充满剩余充电时间
	unsigned short MHTemp;				// 最高动力蓄电池温度
	unsigned short MLTemp;				// 最低动力蓄电池温度
	unsigned int totalElect;			// 总电量
	unsigned int sharpElect;			// 尖电量
	unsigned int peakElect;				// 峰电量
	unsigned int flatElect;				// 平电量
	unsigned int valleyElect;			// 谷电量
	unsigned int totalCost;				// 总金额
	unsigned int totalPowerCost;		// 总电费
	unsigned int totalServCost;			// 总服务费
} evs_property_dc_work;
```

### <a name="EVS_CMD_PROPERTY_DC_NONWORK">EVS_CMD_PROPERTY_DC_NONWORK</a>

* 直流设备非充电过程实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;			 // 充电枪编号
	unsigned char workStatus;		 // 工作状态
	unsigned char gunStatus;		 // 充电枪连接状态
	unsigned char eLockStatus;		 // 充电枪电子锁状态
	unsigned char DCK1Status;		 // 直流输出接触器K1状态
	unsigned char DCK2Status;		 // 直流输出接触器K2状态
	unsigned char DCPlusFuseStatus;	 // DC+熔断器状态
	unsigned char DCMinusFuseStatus; // DC-熔断器状态
	unsigned short conTemp1;		 // 充电接口DC+温度
	unsigned short conTemp2;		 // 充电接口DC-温度
	unsigned int dcVol;				 // 输出电压
	unsigned int dcCur;				 // 输出电流
} evs_property_dc_nonWork;
```

### <a name="EVS_CMD_PROPERTY_AC_OUTMETER">EVS_CMD_PROPERTY_AC_OUTMETER</a>

* 交流设备输出电表实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;							// 1	充电枪编号
	char acqTime[EVS_MAX_TIMESTAMP_LEN];			// 2	采集时间
	unsigned char mailAddr[EVS_MAX_METER_ADDR_LEN]; // 3	通信地址 压缩BCD
	unsigned char meterNo[EVS_MAX_METER_ADDR_LEN];	// 4	表号 压缩BCD
	char assetId[EVS_MAX_METER_ASSET_LEN];			// 5	电表资产编码
	unsigned int sumMeter;							// 6	电表底值
	char lastTrade[EVS_MAX_TRADE_LEN];				// 7	最后交易流水
	unsigned int elec;								// 8	充电中订单的已充电量
} evs_property_meter;
```

### <a name="EVS_CMD_PROPERTY_DC_OUTMETER">EVS_CMD_PROPERTY_DC_OUTMETER</a>

* 直流设备输出电表实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;							// 1	充电枪编号
	char acqTime[EVS_MAX_TIMESTAMP_LEN];			// 2	采集时间
	unsigned char mailAddr[EVS_MAX_METER_ADDR_LEN]; // 3	通信地址 压缩BCD
	unsigned char meterNo[EVS_MAX_METER_ADDR_LEN];	// 4	表号 压缩BCD
	char assetId[EVS_MAX_METER_ASSET_LEN];			// 5	电表资产编码
	unsigned int sumMeter;							// 6	电表底值
	char lastTrade[EVS_MAX_TRADE_LEN];				// 7	最后交易流水
	unsigned int elec;								// 8	充电中订单的已充电量
} evs_property_meter;
```

### <a name="EVS_CMD_PROPERTY_BMS">EVS_CMD_PROPERTY_BMS</a>

* 直流设备充电过程BMS实时属性上报参数详情

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char socVal;				// 4	SOC
	unsigned char BMSVer;				// 5	BMS通信协议版本号
	unsigned short BMSMaxVol;			// 6	最高允许充电总电压
	unsigned char batType;				// 7	电池类型
	unsigned short batRatedCap;			// 8	整车动力蓄电池额定容量
	unsigned short batRatedTotalVol;	// 9	整车动力蓄电池额定总电压
	unsigned short singlBatMaxAllowVol; // 10	单体动力蓄电池最高允许充电电压
	unsigned short maxAllowCur;			// 11	最高允许充电电流
	unsigned short battotalEnergy;		// 12	整车动力蓄电池标称总能量
	unsigned short maxVol;				// 13	最高允许充电总电压
	unsigned short maxTemp;				// 14	最高允许温度
	unsigned short batCurVol;			// 15	整车动力蓄电池当前电池电压
} evs_property_BMS;
```

### <a name="EVS_CMD_PROPERTY_DC_INPUT_METER">EVS_CMD_PROPERTY_DC_INPUT_METER</a>

* 直流设备输入侧交流电表属性上报

``` 
typedef struct
{
	unsigned char gunNo;							// 充电枪编号
	char acqTime[EVS_MAX_TIMESTAMP_LEN];			// 采集时间
	unsigned char mailAddr[EVS_MAX_METER_ADDR_LEN]; // 通信地址 压缩BCD
	unsigned char meterNo[EVS_MAX_METER_ADDR_LEN];	// 电表表号 压缩BCD
	char assetId[EVS_MAX_METER_ASSET_LEN];			// 电表资产编码
	unsigned int sumMeter;							// 电表底值
	unsigned int ApElect;							// A相正向总电量
	unsigned int BpElect;							// B相正向总电量
	unsigned int CpElect;							// C相正向总电量
} evs_property_dc_input_meter;
```

-----

# <a name="Service回调列表">Service回调列表</a>

| 服务消息类型                                                    | 回调函数原型                                                                                                                                                    | 触发条件说明
|---------------------------------------------------------|-------------------------------------------------------------------------------------------|--------------------------------------------------------------
| [EVS_CONF_GET_SRV](#EVS_CONF_GET_SRV)                   | int callback(evs_data_dev_config *result); | 收到云端下发的配置信息获取请求
| [EVS_CONF_UPDATE_SRV](#EVS_CONF_UPDATE_SRV)                   | int callback(evs_data_dev_config *param, int *result); | 收到云端下发的配置信息更新请求
| [EVS_QUE_DATA_SRV](#EVS_QUE_DATA_SRV)                   | int callback(evs_service_query_log *param, evs_service_feedback_query_log *result); | 收到云端下发的日志查询请求
| [EVS_DEV_MAINTAIN_SRV](#EVS_DEV_MAINTAIN_SRV)     | int callback(evs_service_dev_maintain *param, evs_service_feedback_dev_maintain *result); | 收到云端下发的设备维护请求
| [EVS_CTRL_LOCK_SRV](#EVS_CTRL_LOCK_SRV)                         | int callback(evs_service_lockCtrl *param, evs_service_feedback_lockCtrl *result); | 收到云端下发的电子锁控制请求
| [EVS_FEE_MODEL_UPDATA_SRV](#EVS_FEE_MODEL_UPDATA_SRV)                       | int callback(evs_service_issue_feeModel *param, evs_service_feedback_feeModel *result); |收到云端下发的计费模型更新请求
| [EVS_START_CHARGE_SRV](#EVS_START_CHARGE_SRV)                   | int callback(evs_service_startCharge *param, evs_service_feedback_startCharge *result); | 收到云端下发的启动充电请求
| [EVS_AUTH_RESULT_SRV](#EVS_AUTH_RESULT_SRV)                   | int callback(evs_service_authCharge *param, evs_service_feedback_authCharge *result); | 收到云端下发的鉴权启动充电结果
| [EVS_STOP_CHARGE_SRV](#EVS_STOP_CHARGE_SRV)                   | int callback(evs_service_stopCharge *param, evs_service_feedback_stopCharge *result); | 收到云端下发的停止充电请求
| [EVS_ORDER_CHECK_SRV](#EVS_ORDER_CHECK_SRV)                   | int callback(evs_service_confirmTrade *param, void *result); | 收到云端下发的交易记录确认事件
| [EVS_RSV_CHARGE_SRV](#EVS_RSV_CHARGE_SRV)     | int callback(evs_service_rsvCharge *param, evs_service_feedback_rsvCharge *result); | 搜到云端下发的预约充电请求
| [EVS_GROUND_LOCK_SRV](#EVS_GROUND_LOCK_SRV)                         | int callback(evs_service_groundLock_ctrl *param, evs_service_feedback_groundLock_ctrl *result); | 收到云端下发的智能地锁控制请求
| [EVS_GATE_LOCK_SRV](#EVS_GATE_LOCK_SRV)                   | int callback(evs_service_gateLock_ctrl *param, evs_service_feedback_gateLock_ctrl *result); | 收到云端下发的智能门锁控制请求
| [EVS_ORDERLY_CHARGE_SRV](#EVS_ORDERLY_CHARGE_SRV)                   | int callback(evs_service_orderCharge *param, evs_service_feedback_orderCharge *result); |收到云端下发的有序充电请求
| [EVS_STATE_EVERYTHING](#EVS_STATE_EVERYTHING)                       | int callback(int ev, const char *msg); | SDK内部运行状态
| [EVS_CONNECT_SUCC](#EVS_CONNECT_SUCC)                   | int callback(void); | 与云端连接成功时
| [EVS_DISCONNECTED](#EVS_DISCONNECTED)                   | int callback(void); | 与云端连接断开时
| [EVS_REPORT_REPLY](#EVS_REPORT_REPLY)                   | int callback(const int devid, const int msgid, const int code, const char *reply, const int reply_len); | 收到上报消息的应答时
| [EVS_TRIGGER_EVENT_REPLY](#EVS_TRIGGER_EVENT_REPLY)     | int callback(const int devid, const int msgid, const int code, const char *eventid, const int eventid_len, const char *message, const int message_len); | 收到事件上报消息的应答时
| [EVS_CERT_GET](#EVS_CERT_GET)                         | int callback(evs_device_meta *meta); | 当SDK获取设备证书组时
| [EVS_CERT_SET](#EVS_CERT_SET)                       | int callback(const evs_device_meta meta); | 当SDK设置设备证书组时
| [EVS_DEVICE_REG_CODE_GET](#EVS_DEVICE_REG_CODE_GET)     | int callback(char *device_reg_code); | 当SDK获取注册码时
| [EVS_DEVICE_UID_GET](#EVS_DEVICE_UID_GET)     | int callback(char *device_uid); | 收SDK获取设备唯一识别码时
| [EVS_TIME_SYNC](#EVS_TIME_SYNC)                         | int callback(const char *timestamp); | 当收到查询时间戳请求的应答时
| [EVS_OTA_UPDATE](#EVS_OTA_UPDATE)                       | int callback(int type, const char *version); | 可用固件的通知时
-----

# <a name="Service服务回调列表详解">Service服务回调列表详解</a>

## <a name="EVS_CONF_GET_SRV">EVS_CONF_GET_SRV</a>

原型
---

``` 
int callback(evs_data_dev_config *result);
```

接口说明
---
当SDK收到云端下发的配置信息获取请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| result      | evs_data_dev_config * | 输出    | 设备配置信息

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_CONF_UPDATE_SRV">EVS_CONF_UPDATE_SRV</a>

原型
---

``` 
int callback(evs_data_dev_config *param, int *result);
```

接口说明
---
当SDK收到云端下发的配置信息更新请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_data_dev_config * | 输入    | 设备配置信息
| result      | int | 输出    | 设备配置信息

参数附加说明
---

``` 
typedef struct
{
	unsigned int equipParamFreq;					   // 1		充电设备实时监测属性上报频率
	unsigned int gunElecFreq;						   // 2		充电枪充电中实时监测属性上报频率
	unsigned int nonElecFreq;						   // 2		充电枪非充电中实时监测属性上报频率
	unsigned int faultWarnings;						   // 3		故障告警全信息上传频率
	unsigned int acMeterFreq;						   // 4		充电设备交流电表底值监测属性上报频率
	unsigned int dcMeterFreq;						   // 5		直流输出电表底值监测属性上报频率
	unsigned int offlinChaLen;						   // 6		离线后可充电时长
	unsigned int grndLock;							   // 7		地锁监测上送频率
	unsigned int doorLock;							   // 8		网门锁监测上送频率
	unsigned int encodeCon;							   // 9		报文加密
	char qrCode[EVS_MAX_PORT_NUM][EVS_MAX_QRCODE_LEN]; // 10	二维码数据
} evs_data_dev_config;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_QUE_DATA_SRV">EVS_QUE_DATA_SRV</a>

原型
---

``` 
int callback(evs_service_query_log *param, evs_service_feedback_query_log *result);
```

接口说明
---
当SDK收到云端下发的配置信息更新请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_query_log * | 输入    | 平台日志查询信息
| result      | evs_service_feedback_query_log* | 输出    | 设备日志信息

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;	// 枪号	gunNo
	unsigned int startDate; // 查询起始时间戳	startDate
	unsigned int stopDate;	// 查询终止时间戳	stopDate
	unsigned char askType;	// 查询类型	askType
} evs_service_query_log;
```

``` 
typedef struct
{
	unsigned char gunNo;			 // 1	枪号
	unsigned int startDate;			 // 2	查询起始时间
	unsigned int stopDate;			 // 3	查询终止时间
	unsigned char askType;			 // 4	查询类型
	unsigned char succ;				 // 5	响应结果
	unsigned char retType;			 // 6	响应类型
	char dataArea[EVS_MAX_DATA_LEN]; // 7	响应数据区
} evs_service_feedback_query_log;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_DEV_MAINTAIN_SRV">EVS_DEV_MAINTAIN_SRV</a>

原型
---

``` 
int callback(evs_service_dev_maintain *param, evs_service_feedback_dev_maintain *result);
```

接口说明
---
当SDK收到云端下发的设备维护指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_dev_maintain * | 输入    | 平台设备维护信息
| result      | evs_service_feedback_dev_maintain* | 输出    | 设备维护结果

参数附加说明
---

``` 
typedef struct
{
	unsigned char ctrlType; // 控制类型
} evs_service_dev_maintain;
```

``` 
typedef struct
{
	unsigned char ctrlType; // 1	当前控制类型
	unsigned int reason;	// 2	失败原因
} evs_service_feedback_dev_maintain;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_CTRL_LOCK_SRV">EVS_CTRL_LOCK_SRV</a>

原型
---

``` 
int callback(evs_service_lockCtrl *param, evs_service_feedback_lockCtrl *result);
```

接口说明
---
当SDK收到云端下发的电子锁控制请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_lockCtrl * | 输入    | 平台电子锁控制指令
| result      | evs_service_feedback_lockCtrl* | 输出    | 设备控制结果

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;	 // 1	充电枪编号
	unsigned char lockParam; // 2	控制
} evs_service_lockCtrl;
```

``` 
typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char lockStatus; // 2	电子锁状态
	unsigned int resCode;	  // 3	结果
} evs_service_feedback_lockCtrl;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_FEE_MODEL_UPDATA_SRV">EVS_FEE_MODEL_UPDATA_SRV</a>

原型
---

``` 
int callback(evs_service_issue_feeModel *param, evs_service_feedback_feeModel *result)
```

接口说明
---
当SDK收到云端下发的计费模型更新指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_issue_feeModel * | 输入    | 平台下发计费模型信息
| result      | evs_service_feedback_feeModel* | 输出    | 设备返回计费模型更新结果

参数附加说明
---

``` 
typedef struct
{
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 1		电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 2		服务费模型编号
	unsigned char TimeNum;				   // 3		电费模型时段数N 取值范围：1—14
	char TimeSeg[EVS_MAX_MODEL_DEVSEG][5]; // 4		电费模型时段开始时间点
	char SegFlag[EVS_MAX_MODEL_DEVSEG];	   // 5		电费模型时段标志
	unsigned int chargeFee[4];			   // 6		电费模型
	unsigned int serviceFee[4];			   // 10	服务费费模型
} evs_service_issue_feeModel;
```

``` 
typedef struct
{
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 1		电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 2		服务费模型编号
	unsigned char result;				   // 3		失败原因
} evs_service_feedback_feeModel;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_START_CHARGE_SRV">EVS_START_CHARGE_SRV</a>

原型
---

``` 
int callback(evs_service_startCharge *param, evs_service_feedback_startCharge *result)
```

接口说明
---
当SDK收到云端下发的启动充电请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_startCharge * | 输入    | 平台下启动充电命令
| result      | evs_service_feedback_startCharge* | 输出    | 设备返回启动确认信息

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char startType;			// 4	启动方式
	unsigned char chargeMode;			// 5	充电模式
	unsigned int limitData;				// 6	限制值
	unsigned int stopCode;				// 7	停机码
	unsigned char startMode;			// 8	启动模式
	unsigned int insertGunTime;			// 10	插枪事件时间戳
} evs_service_startCharge;
```

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_startCharge;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_AUTH_RESULT_SRV">EVS_AUTH_RESULT_SRV</a>

原型
---

``` 
int callback(evs_service_authCharge *param, evs_service_feedback_authCharge *result)
```

接口说明
---
当SDK收到云端下发的设备鉴权启动充电结果时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_authCharge * | 输入    | 平台下鉴权充电结果
| result      | evs_service_feedback_authCharge* | 输出    | 设备返回鉴权确认信息

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	char vinCode[EVS_MAX_CAR_VIN_LEN];	// 4	填VIN信息。
	char oppoCode[EVS_MAX_QRCODE_LEN];	// 5	若启动方式为反向扫码，填入二维码信息；若无则为空。
	unsigned char result;				// 6	鉴权结果
	unsigned char chargeMode;			// 7	充电模式
	unsigned int limitData;				// 8	限制值
	unsigned int stopCode;				// 9	停机码
	unsigned char startMode;			// 10	启动模式
	unsigned int insertGunTime;			// 11	插枪事件时间戳
} evs_service_authCharge;
```

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_authCharge;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_STOP_CHARGE_SRV">EVS_STOP_CHARGE_SRV</a>

原型
---

``` 
int callback(evs_service_stopCharge *param, evs_service_feedback_stopCharge *result)
```

接口说明
---
当SDK收到云端下发的停止充电请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_stopCharge * | 输入    | 平台下停止充电命令
| result      | evs_service_feedback_stopCharge* | 输出    | 设备返回停止确认信息

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char stopReason;			// 4	停止原因
} evs_service_stopCharge;
```

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_stopCharge;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_ORDER_CHECK_SRV">EVS_ORDER_CHECK_SRV</a>

原型
---

``` 
int callback(evs_service_confirmTrade *param, void *result)
```

接口说明
---
当SDK收到云端下发的交易记录确认指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_confirmTrade * | 输入    | 平台下交易记录确认
| result      | void* | 输出    | 设备返回启动信息

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char errcode;				// 4	交易记录上传结果
} evs_service_confirmTrade;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_RSV_CHARGE_SRV">EVS_RSV_CHARGE_SRV</a>

原型
---

``` 
int callback(evs_service_rsvCharge *param, evs_service_feedback_rsvCharge *result)
```

接口说明
---
当SDK收到云端下发的预约充电请求时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_rsvCharge * | 输入    | 平台下预约充电命令
| result      | evs_service_feedback_rsvCharge* | 输出    | 设备返回预约结果

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char appomathod; // 2	预约方式 10：立即预约 11：取消预约
	unsigned short appoDelay; // 3	预约等候时长  分钟数，大于0，且不大于1440
} evs_service_rsvCharge;
```

``` 
typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char appomathod; // 2	预约方式
	unsigned char ret;		  // 3	预约结果
	unsigned char reason;	  // 4	失败原因
} evs_service_feedback_rsvCharge;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_GROUND_LOCK_SRV">EVS_GROUND_LOCK_SRV</a>

原型
---

``` 
int callback(evs_service_groundLock_ctrl *param, evs_service_feedback_groundLock_ctrl *result)
```

接口说明
---
当SDK收到云端下发的智能地锁控制指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_groundLock_ctrl * | 输入    | 平台下智能地锁控制命令
| result      | evs_service_feedback_groundLock_ctrl* | 输出    | 设备返回控制结果

参数附加说明
---

``` 
typedef struct
{
	unsigned char gunNo;	// 1	充电枪编号
	unsigned char ctrlFlag; // 2	控制指令
} evs_service_groundLock_ctrl;
```

``` 
typedef struct
{
	unsigned char gunNo;  // 1	充电枪编号
	unsigned char result; // 2	控制结果
	unsigned char reason; // 3	失败原因
} evs_service_feedback_groundLock_ctrl;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_GATE_LOCK_SRV">EVS_GATE_LOCK_SRV</a>

原型
---

``` 
int callback(evs_service_gateLock_ctrl *param, evs_service_feedback_gateLock_ctrl *result)
```

接口说明
---
当SDK收到云端下发的智能门锁控制指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_gateLock_ctrl * | 输入    | 平台下智能门锁控制命令
| result      | evs_service_feedback_gateLock_ctrl* | 输出    | 设备返回控制结果

参数附加说明
---

``` 
typedef struct
{
	unsigned char lockNo;	// 1	门锁编号
	unsigned char ctrlFlag; // 2	控制指令
} evs_service_gateLock_ctrl;
```

``` 
typedef struct
{
	unsigned char lockNo; // 1	充电枪编号
	unsigned char result; // 2	控制结果
} evs_service_feedback_gateLock_ctrl;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_ORDERLY_CHARGE_SRV">EVS_ORDERLY_CHARGE_SRV</a>

原型
---

``` 
int callback(evs_service_orderCharge *param, evs_service_feedback_orderCharge *result)
```

接口说明
---
当SDK收到云端下发的智能地锁控制指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| param      | evs_service_groundLock_ctrl * | 输入    | 平台下智能地锁控制命令
| result      | evs_service_feedback_groundLock_ctrl* | 输出    | 设备返回控制结果

参数附加说明
---

``` 
typedef struct
{
	char preTradeNo[EVS_MAX_TRADE_LEN];			 // 1	订单流水号
	unsigned char num;							 // 2	策略配置时间段数量
	unsigned char validTime[EVS_MAX_SEG_LEN][5]; // 3	策略生效时间
	unsigned short kw[EVS_MAX_SEG_LEN];			 // 4	策略配置功率

} evs_service_orderCharge;
```

``` 
typedef struct
{
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 1	订单流水号
	unsigned char result;				// 2	返回结果
	unsigned char reason;				// 3	失败原因
} evs_service_feedback_orderCharge;
```

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_STATE_EVERYTHING">EVS_STATE_EVERYTHING</a>

原型
---

``` 
int callback(int ev, const char *msg);
```

接口说明
---
当SDK收到云端下发的智能地锁控制指令时, 会触发此事件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------------|---------|-------------------------
| ev      | int  | 输入    | 消息ID
| msg      | char * | 输入    | 消息内容

返回值说明
---
| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_CONNECT_SUCC">EVS_CONNECT_SUCC</a>

原型
---

``` 
int callback(void);
```

接口说明
---
当SDK与云端连接成功时, 会触发此事件

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

## <a name="EVS_DISCONNECTED">EVS_DISCONNECTED</a>

原型
---

``` 
int callback(void);
```

接口说明
---
当SDK与云端连接断开时, 会触发此事件

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

## <a name="EVS_REPORT_REPLY">EVS_REPORT_REPLY</a>

原型
---

``` 
int callback(const int devid, const int msgid, const int code, const char *reply, const int reply_len);
```

接口说明
---
当SDK收到属性上报/设备标签更新/设备标签删除的应答时, 会触发此事件并调用回调函数

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

## <a name="EVS_TRIGGER_EVENT_REPLY">EVS_TRIGGER_EVENT_REPLY</a>

原型
---

``` 
int callback(const int devid, const int msgid, const int code, const char *eventid, const int eventid_len, const char *message, const int message_len);
```

接口说明
---
当SDK收到事件上报的应答时, 会触发此事件并调用回调函数

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

## <a name="EVS_CERT_GET">EVS_CERT_GET</a>

原型
---

``` 
int callback(evs_device_meta *meta);
```

接口说明
---
当SDK查询设备证书时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| meta   | evs_device_meta *    | 输入    | 设备证书

附加参数说明
---

``` 
typedef struct
{
	char product_key[IOTX_PRODUCT_KEY_LEN + 1];			//设备品类标识字符串
	char product_secret[IOTX_PRODUCT_SECRET_LEN + 1];	//设备品类密钥
	char device_name[IOTX_DEVICE_NAME_LEN + 1];			//某台设备的标识字符串:未注册前为设备出厂编号（16位长度），注册后为设备在物联管理平台的资产码（24位长度）
	char device_secret[IOTX_DEVICE_SECRET_LEN + 1];		//某台设备的设备密钥
	char device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1]; //某台设备的设备注册码
	char device_uid[IOTX_DEVICE_UID_LEN + 1];			//某台设备的出厂编号
} evs_device_meta;
```

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_CERT_SET">EVS_CERT_SET</a>

原型
---

``` 
int callback(evs_device_meta *meta);
```

接口说明
---
当SDK存储设备证书时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| meta   | evs_device_meta *    | 输入    | 设备证书

附加参数说明
---

``` 
typedef struct
{
	char product_key[IOTX_PRODUCT_KEY_LEN + 1];			//设备品类标识字符串
	char product_secret[IOTX_PRODUCT_SECRET_LEN + 1];	//设备品类密钥
	char device_name[IOTX_DEVICE_NAME_LEN + 1];			//某台设备的标识字符串:未注册前为设备出厂编号（16位长度），注册后为设备在物联管理平台的资产码（24位长度）
	char device_secret[IOTX_DEVICE_SECRET_LEN + 1];		//某台设备的设备密钥
	char device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1]; //某台设备的设备注册码
	char device_uid[IOTX_DEVICE_UID_LEN + 1];			//某台设备的出厂编号
} evs_device_meta;
```

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_DEVICE_REG_CODE_GET">EVS_DEVICE_REG_CODE_GET</a>

原型
---

``` 
int callback(char *device_reg_code);
```

接口说明
---
当SDK收到查询时间戳的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| device_reg_code   | char *    | 输出    | 设备注册码

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_DEVICE_UID_GET">EVS_DEVICE_UID_GET</a>

原型
---

``` 
int callback(char *device_uid); 
```

接口说明
---
当SDK收到查询时间戳的应答时, 会触发此事件并调用回调函数

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-----------------
| device_uid   | char *    | 输出    | 设备唯一标识码

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----

## <a name="EVS_TIME_SYNC">EVS_TIME_SYNC</a>

原型
---

``` 
int callback(const unsigned int timestamp);
```

接口说明
---
当SDK收到查询时间戳的应答时, 会触发此事件并调用回调函数

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

## <a name="EVS_OTA_UPDATE">EVS_OTA_UPDATE</a>

原型
---

``` 
int callback(const char *version);
```

接口说明
---
当SDK收到可用固件的通知时, 会触发此事件并调用回调函数. 用户在收到新固件通知后, 可使用 `evs_linkkit_fota` 消息获取新固件

参数说明
---
| 参数        | 数据类型        | 方向    | 说明
|-------------|-----------------|---------|-------------------------------------------------------------
| version     | const char *    | 输入    | 可用的固件版本号

返回值说明
---

| 值  | 说明
|-----|-----------------
| 0   | 事件处理成功
| -1  | 事件处理失败

-----
