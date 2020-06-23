#if !defined(_PROTOCOL_DATA_DEF_H_)
#define _PROTOCOL_DATA_DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infra_types.h"
#include "infra_defs.h"

/*******************************用户可配置项***************************************/
#define EVS_MAX_PORT_NUM (4)		//充电接口数量
#define EVS_MAX_INPUT_METER_NUM (2) //直流充电桩输入电表数量
#define EVS_MAX_ALARM_LEN (5)		//最大故障告警数
/*********************************************************************************/

#define EVS_MAX_TRADE_LEN (38 + 1)
#define EVS_MAX_CAR_VIN_LEN (17 + 1)
#define EVS_MAX_MAC_ADDR_LEN (32 + 1)
#define EVS_MAX_MODEL_ID_LEN (16 + 1)

#define EVS_MAX_DATA_LEN (512)
#define EVS_MAX_QRCODE_LEN (40)
#define EVS_MAX_ICCID_LEN (24)
#define EVS_MAX_PILE_TYPE_LEN (20)
#define EVS_MAX_DEV_SN_LEN (16 + 1)
#define EVS_MAX_MODEL_DEVSEG (48)
#define EVS_MAX_METER_ADDR_LEN (6)
#define EVS_MAX_METER_ASSET_LEN (32 + 1)
#define EVS_MAX_TIMESTAMP_LEN (15 + 1)

typedef struct
{
	char product_key[IOTX_PRODUCT_KEY_LEN + 1];
	char product_secret[IOTX_PRODUCT_SECRET_LEN + 1];
	char device_name[IOTX_DEVICE_NAME_LEN + 1];
	char device_secret[IOTX_DEVICE_SECRET_LEN + 1];
	char device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1];
	char device_uid[IOTX_DEVICE_UID_LEN + 1];
} evs_device_meta;

typedef enum
{
	EVS_CMD_EVENT_FIREWARE_INFO = 10,
	EVS_CMD_EVENT_ASK_FEEMODEL = 11,
	EVS_CMD_EVENT_STARTCHARGE = 12,
	EVS_CMD_EVENT_STARTRESULT = 13,
	EVS_CMD_EVENT_STOPCHARGE = 14,
	EVS_CMD_EVENT_TRADEINFO = 15,
	EVS_CMD_EVENT_ALARM = 16,
	EVS_CMD_EVENT_ACPILE_CHANGE = 17,
	EVS_CMD_EVENT_DCPILE_CHANGE = 18,
	EVS_CMD_EVENT_GROUNDLOCK_CHANGE = 19,
	EVS_CMD_EVENT_GATELOCK_CHANGE = 20,
	EVS_CMD_EVENT_ASK_DEV_CONFIG = 21,

} evs_cmd_event_enum;

typedef enum
{
	EVS_CMD_PROPERTY_DCPILE = 10,
	EVS_CMD_PROPERTY_ACPILE = 11,
	EVS_CMD_PROPERTY_AC_WORK = 12,
	EVS_CMD_PROPERTY_AC_NONWORK = 13,
	EVS_CMD_PROPERTY_DC_WORK = 14,
	EVS_CMD_PROPERTY_DC_NONWORK = 15,
	EVS_CMD_PROPERTY_DC_OUTMETER = 16,
	EVS_CMD_PROPERTY_AC_OUTMETER = 17,
	EVS_CMD_PROPERTY_BMS = 18,
	EVS_CMD_PROPERTY_DC_INPUT_METER = 19,
} evs_cmd_property_enum;

//固件信息上报事件参数

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

//设备配置数据
typedef struct
{
	unsigned int equipParamFreq;					   // 1		充电设备实时监测属性上报频率
	unsigned int gunElecFeeq;						   // 2		充电枪充电中实时监测属性上报频率
	unsigned int nonElecFreq;						   // 2		充电枪非充电中实时监测属性上报频率
	unsigned int faultWarnings;						   // 3		故障告警全信息上传频率
	unsigned int acMeterFreq;						   // 4		充电设备交流电表底值监测属性上报频率
	unsigned int dcMeterFreq;						   // 5		直流输出电表底值监测属性上报频率
	unsigned int offlinChaLen;						   // 6		离线后可充电时长
	unsigned int grndLock;							   // 7		地锁监测上送频率
	unsigned int doorLock;							   // 8		网门锁监测上送频率
	unsigned int encodeCon;							   // 9		报文加密
	char qrCode[EVS_MAX_PORT_NUM][EVS_MAX_QRCODE_LEN]; // 10		二维码数据
} evs_data_dev_config;

//设备日志查询服务下发参数

typedef struct
{
	unsigned char gunNo;	// 枪号	gunNo
	unsigned int startDate; // 查询起始时间戳	startDate
	unsigned int stopDate;	// 查询终止时间戳	stopDate
	unsigned char askType;	// 查询类型	askType
} evs_service_query_log;

//日志查询服务回复参数

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

//设备维护指令服务下发参数

typedef struct
{
	unsigned char ctrlType; // 控制类型
} evs_service_dev_maintain;

//设备维护指令服务回复参数

typedef struct
{
	unsigned char ctrlType; // 1	当前控制类型
	unsigned int reason;	// 2	失败原因
} evs_service_feedback_dev_maintain;

// 充电枪电子锁控制服务下发参数

typedef struct
{
	unsigned char gunNo;	 // 1	充电枪编号
	unsigned char lockParam; // 2	控制
} evs_service_lockCtrl;

//充电枪电子锁控制服务回复参数

typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char lockStatus; // 2	电子锁状态
	unsigned int resCode;	  // 3	结果
} evs_service_feedback_lockCtrl;

// 计费模型请求事件

typedef struct
{
	unsigned char gunNo;				   // 1	充电枪编号
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 2	电费计费模型编号
	char serModeId[EVS_MAX_MODEL_ID_LEN];  // 2	服务费模型编号
} evs_event_ask_feeModel;

//计费模型更新服务下发参数

// typedef struct
// {
// 	unsigned char eleModelId[EVS_MAX_MODEL_ID_LEN];	   // 1		电费计费模型编号
// 	unsigned char serModelId[EVS_MAX_MODEL_ID_LEN];	   // 2		服务费模型编号
// 	unsigned char eleTimeNum;						   // 3		电费模型时段数N 取值范围：1—14
// 	unsigned char eleTimeSeg[EVS_MAX_MODEL_DEVSEG][5]; // 4		电费模型时段开始时间点
// 	unsigned char eleSegFlag[EVS_MAX_MODEL_DEVSEG];	   // 5		电费模型时段标志
// 	unsigned int chargeFee[4];						   // 6		电费模型
// 	unsigned char serTimeNum;						   // 7		服务费模型时段数N 取值范围：1—14
// 	unsigned char serTimeSeg[EVS_MAX_MODEL_DEVSEG][5]; // 8		服务费费模型时段开始时间点
// 	unsigned char serSegFlag[EVS_MAX_MODEL_DEVSEG];	   // 9		服务费费模型时段标志
// 	unsigned int serviceFee[4];						   // 10	服务费费模型
// } evs_service_issue_feeModel;

typedef struct
{
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 1		电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 2		服务费模型编号
	unsigned char TimeNum;				   // 3		电费模型时段数N 取值范围：1—14
	char TimeSeg[EVS_MAX_MODEL_DEVSEG][5]; // 4		电费模型时段开始时间点
	char SegFlag[EVS_MAX_MODEL_DEVSEG];	   // 5		电费模型时段标志
	unsigned int chargeFee[4];			   // 6		电费模型
	unsigned int serviceFee[4];			   // 10		服务费费模型
} evs_service_issue_feeModel;

//计费模型更新结果设备回复参数

typedef struct
{
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 1		电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 2		服务费模型编号
	unsigned char result;				   // 3		失败原因
} evs_service_feedback_feeModel;

//远程启动充电服务下发参数

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

//启动充电服务设备回复参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_startCharge;

//启动充电结果事件参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char startResult;			// 4	启动结果
	unsigned int faultCode;				// 5	故障代码
	char vinCode[EVS_MAX_CAR_VIN_LEN];	// 6	vin码
} evs_event_startResult;

//启动充电鉴权事件参数

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

//鉴权充电服务下发参数

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

//鉴权启动充电服务设备回复参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_authCharge;

//远程停止充电服务下发参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char stopReason;			// 4	停止原因
} evs_service_stopCharge;

//远程停止充电服务设备回复参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
} evs_service_feedback_stopCharge;

//停止充电结果事件上传参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char stopResult;			// 4	停止结果
	unsigned int resultCode;			// 5	停止原因
	unsigned char stopFailReson;		// 6	停止失败原因
} evs_event_stopCharge;

//交易记录事件上传参数

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

//交易记录确认服务下发参数

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 2	平台交易流水号
	char tradeNo[EVS_MAX_TRADE_LEN];	// 3	设备交易流水号
	unsigned char errcode;				// 4	交易记录上传结果
} evs_service_confirmTrade;

//故障告警事件上传参数

typedef struct
{
	unsigned char gunNo;						  // 1	枪编号
	unsigned short faultSum;					  // 2	故障总
	unsigned short warnSum;						  // 3	告警总
	unsigned short faultValue[EVS_MAX_ALARM_LEN]; // 4	故障点数据
	unsigned short warnValue[EVS_MAX_ALARM_LEN];  // 5	告警点数据
} evs_event_alarm;

//预约充电服务下发参数

typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char appomathod; // 2	预约方式 10：立即预约 11：取消预约
	unsigned short appoDelay; // 3	预约等候时长  分钟数，大于0，且不大于1440
} evs_service_rsvCharge;

//预约充电服务设备回复参数

typedef struct
{
	unsigned char gunNo;	  // 1	充电枪编号
	unsigned char appomathod; // 2	预约方式
	unsigned char ret;		  // 3	预约结果
	unsigned char reason;	  // 4	失败原因
} evs_service_feedback_rsvCharge;

//地锁控制服务下发参数

typedef struct
{
	unsigned char gunNo;	// 1	充电枪编号
	unsigned char ctrlFlag; // 2	控制指令
} evs_service_groundLock_ctrl;

//地锁控制服务回复参数

typedef struct
{
	unsigned char gunNo;  // 1	充电枪编号
	unsigned char result; // 2	控制结果
	unsigned char reason; // 3	失败原因
} evs_service_feedback_groundLock_ctrl;

//地锁状态变化事件上传参数

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

//智能门锁控制服务下发参数

typedef struct
{
	unsigned char lockNo;	// 1	门锁编号
	unsigned char ctrlFlag; // 2	控制指令
} evs_service_gateLock_ctrl;

//智能门锁控制服务回复参数

typedef struct
{
	unsigned char lockNo; // 1	充电枪编号
	unsigned char result; // 2	控制结果
} evs_service_feedback_gateLock_ctrl;

//智能门锁状态变化事件上传参数

typedef struct
{
	unsigned char lockNo;	 // 1	充电枪编号
	unsigned char lockState; // 2	智能门锁状态
} evs_event_gateLock_change;

//有序充电策略服务下发参数

typedef struct
{
	char preTradeNo[EVS_MAX_TRADE_LEN]; // 1	订单流水号
	unsigned char num;					// 2	策略配置时间段数量
	unsigned char validTime[5][4];		// 3	策略生效时间//字符串数组。时间格式采用HHMM，24小时制。策略范围24小时内最多五段 例如 ：[time1,time2,time3…]。
	unsigned char kw[5];				// 4	策略配置功率//整型数组。功率精确到0.1KW[kw1,kw2,kw3…]

} evs_service_orderCharge;

//有序充电策略服务设备回复参数

typedef struct
{
	char tradeNo[EVS_MAX_TRADE_LEN]; // 1	订单流水号
	unsigned char result;			 // 2	返回结果
	unsigned char reason;			 // 3	失败原因
} evs_service_feedback_orderCharge;

//交直流充电设备枪状态变化事件上传参数

typedef struct
{
	unsigned char gunNo;		   // 1	充电枪编号
	unsigned int yxOccurTime;	   // 2	发生时刻
	unsigned char connCheckStatus; // 3	变位点数据
} evs_event_pile_stutus_change;

/*********************************************交流业务相关************************************************************/
//交流设备属性上报参数

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
	unsigned short caseTemp;			   // 10	桩内温度
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 11	电费计费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 12	服务费模型编号
} evs_property_acPile;

//交流充电枪充电中实时监测属性

typedef struct
{
	unsigned char gunNo;				// 1	充电枪编号
	unsigned char workStatus;			// 3	工资状态
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
} evs_property_ac_work;

//交流充电枪非充电中实时监测属性

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

/*********************************************直流业务相关************************************************************/

//直流设备属性上报参数

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
	unsigned short caseTemp;			   // 10	设备内温度
	unsigned short inletTemp;			   // 11	设备入风口温度
	unsigned short outletTemp;			   // 12	设备出风口温度
	char eleModelId[EVS_MAX_MODEL_ID_LEN]; // 13	电费模型编号
	char serModelId[EVS_MAX_MODEL_ID_LEN]; // 14	服务费模型编号
} evs_property_dcPile;

//直流充电枪BMS监测属性

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

//直流充电枪充电中实时监测属性

typedef struct
{
	unsigned char gunNo;	   // 充电枪编号
	unsigned char workStatus;  // 工作状态
	unsigned char gunStatus;   // 充电枪连接状态
	unsigned char eLockStatus; // 充电枪电子锁状态

	unsigned char DCK1Status;		 // 直流输出接触器K1状态
	unsigned char DCK2Status;		 // 直流输出接触器K2状态
	unsigned char DCPlusFuseStatus;	 // DC+熔断器状态
	unsigned char DCMinusFuseStatus; // DC-熔断器状态
	unsigned short conTemp1;		 // 充电接口DC+温度
	unsigned short conTemp2;		 // 充电接口DC-温度
	unsigned int dcVol;				 // 输出电压
	unsigned int dcCur;				 // 输出电流

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

//直流充电枪非充电中实时监测属性

typedef struct
{
	unsigned char gunNo;	   // 充电枪编号
	unsigned char workStatus;  // 工作状态
	unsigned char gunStatus;   // 充电枪连接状态
	unsigned char eLockStatus; // 充电枪电子锁状态

	unsigned char DCK1Status;		 // 直流输出接触器K1状态
	unsigned char DCK2Status;		 // 直流输出接触器K2状态
	unsigned char DCPlusFuseStatus;	 // DC+熔断器状态
	unsigned char DCMinusFuseStatus; // DC-熔断器状态
	unsigned short conTemp1;		 // 充电接口DC+温度
	unsigned short conTemp2;		 // 充电接口DC-温度
	unsigned int dcVol;				 // 输出电压
	unsigned int dcCur;				 // 输出电流
} evs_property_dc_nonWork;

//直流输入电表底值监测属性

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

/******************************************公共属性区*************************************************/

//交直流输出电表底值监测属性

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

/******************************************需用户实现的回调函数*************************************************/

/**
 *
 * 函数 callback_service_query_log() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_query_log() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform log query service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_query_log(evs_service_query_log *param, evs_service_feedback_query_log *result);

/**
 *
 * 函数 callback_service_devCtrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_devCtrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform device control service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_dev_maintain(evs_service_dev_maintain *param, evs_service_feedback_dev_maintain *result);

/**
 *
 * 函数 callback_service_lockCtrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_lockCtrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform chargeGun e-lock control service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_lockCtrl(evs_service_lockCtrl *param, evs_service_feedback_lockCtrl *result);

/**
 *
 * 函数 callback_service_issue_feeModel() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_issue_feeModel() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform feemodel issue service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_issue_feeModel(evs_service_issue_feeModel *param, evs_service_feedback_feeModel *result);

/**
 *
 * 函数 callback_service_startCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_startCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform remote start-charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_startCharge(evs_service_startCharge *param, evs_service_feedback_startCharge *result);

/**
 *
 * 函数 callback_service_authCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_authCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform authorization charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_authCharge(evs_service_authCharge *param, evs_service_feedback_authCharge *result);

/**
 *
 * 函数 callback_service_stopCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_stopCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform remote stop-charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_stopCharge(evs_service_stopCharge *param, evs_service_feedback_stopCharge *result);

/**
 *
 * 函数 callback_service_rsvCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_rsvCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform reservation charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_rsvCharge(evs_service_rsvCharge *param, evs_service_feedback_rsvCharge *result);

/**
 *
 * 函数 callback_service_confirmTrade() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_confirmTrade() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform transaction confirm service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_confirmTrade(evs_service_confirmTrade *param, void *result);

/**
 *
 * 函数 callback_service_grounLock_ctrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_grounLock_ctrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform smart ground locker service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_grounLock_ctrl(evs_service_groundLock_ctrl *param, evs_service_feedback_groundLock_ctrl *result);

/**
 *
 * 函数 callback_service_gateLock_ctrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_gateLock_ctrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform smart gate locker service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_gateLock_ctrl(evs_service_gateLock_ctrl *param, evs_service_feedback_gateLock_ctrl *result);

/**
 *
 * 函数 callback_service_orderCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_orderCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform order-charge strategy service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_orderCharge(evs_service_orderCharge *param, evs_service_feedback_orderCharge *result);

/**
 *
 * 函数 callback_service_get_config() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_get_config() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform device configuration get service by result through SDK.
 *---
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_get_config(evs_data_dev_config *result);

/**
 *
 * 函数 callback_service_update_config() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_update_config() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform update devicce configuration service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_update_config(evs_data_dev_config *param, int *result);

/**
 *
 * 函数 callback_service_ota_update() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_ota_update() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief perform the ota order  from IOT platform .
 *---
 * @param [in] version: @n the new firmware version received from IOT platform.
 * 
 * @return do not update device -1 update device 0.
 * @see None.
 * @note None.
 */
int callback_service_ota_update(const char *version);

/**
 *
 * 函数 callback_service_time_sync() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_time_sync() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief send timestamp that Recived from IOT platform to user by timestamp through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_time_sync(const unsigned int timestamp);

#endif