#if !defined(_PROTOCOL_DATA_DEF_H_)
#define _PROTOCOL_DATA_DEF_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#define EVS_MAX_TRADE_LEN 32 + 1
#define EVS_MAX_CAR_VIN_LEN 17 + 1
#define EVS_MAX_MAC_ADDR_LEN 32 + 1
#define EVS_MAX_DATA_LEN 256
#define EVS_MAX_MODEL_ID_LEN 16 + 1
#define EVS_MAX_ALARM_LEN 32

typedef enum
{
	evs_send_event_fireware_info = 10,
	evs_send_event_ask_feeModel = 11,
	evs_send_event_startCharge = 12,
	evs_send_event_startResult = 13,
	evs_send_event_stopCharge = 14,
	evs_send_event_tradeInfo = 15,
	evs_send_event_alarm = 16,
	evs_send_event_acPile_change = 17,
	evs_send_event_dcPile_change = 18,
	evs_send_event_groundLock_change = 19,
	evs_send_event_gateLock_change = 20,
} evs_cmd_event_enum;

typedef enum
{
	evs_send_property_dcPile = 10,
	evs_send_property_acPile = 11,
	evs_send_property_ac_work = 12,
	evs_send_property_ac_nonwork = 13,
	evs_send_property_dc_work = 14,
	evs_send_property_dc_nonwork = 15,
	evs_send_property_meter = 16,
	evs_send_property_BMS = 17,
	evs_send_property_dc_input_meter = 18,
} evs_cmd_property_enum;

//固件信息上报事件参数
// 1		SIM卡号
// 2		计量计费模型编号
// 3		充电桩型号
// 4		生产厂商编码
// 5		出厂编号
// 6		桩类型
// 7		充电接口数量
// 8		网络MAC地址
// 9		经度
// 10		纬度
// 11		高度
// 12		坐标类型
// 13		系统时钟
// 14		蓝牙MAC地址
// 15		计量方式
// 16		额定功率
// 17		输出最大电压
// 18		输出最大电流
// 19		交流输入电表地址
// 20		计量用电能表地址
// 21		电流互感器系数
// 22		是否有智能门锁
// 23		是否有地锁
typedef struct
{
	uint8_t simNo[20];
	uint8_t modelId[EVS_MAX_MODEL_ID_LEN];
	uint8_t stakeModel[20];
	uint32_t vendorCode;
	uint8_t deSn[16 + 1]; //字符串
	uint8_t deType;
	uint8_t portNum;
	uint8_t simMac[EVS_MAX_MAC_ADDR_LEN]; //HEX数组
	uint32_t longitude;
	uint32_t latitude;
	uint32_t height;
	uint32_t gridType;
	uint32_t sysTime;
	uint8_t btMac[EVS_MAX_MAC_ADDR_LEN]; //HEX数组
	uint8_t meaType;
	uint32_t otRate;
	uint32_t otVol;
	uint32_t otCur;
	uint8_t inMeter[2][6];	//压缩BCD
	uint8_t outMeter[4][6]; //压缩BCD
	uint32_t CT;
	uint8_t isGateLock;
	uint8_t isGroundLock;
} evs_event_fireware_info;

//设备日志查询服务下发参数
// 枪号	gunNo
// 查询起始时间	startDate
// 查询终止时间	stopDate
// 查询类型	askType
typedef struct
{
	uint8_t gunNo;
	uint32_t startDate;
	uint32_t stopDate;
	uint8_t askType;
} evs_service_query_log;

//日志查询服务回复参数
// 1	枪号
// 2	查询起始时间
// 3	查询终止时间
// 4	查询类型
// 5	响应结果
// 6	响应类型
// 7	响应数据区
typedef struct
{
	uint8_t gunNo;
	uint32_t startDate;
	uint32_t stopDate;
	uint8_t askType;
	uint8_t succ;
	uint8_t retType;
	uint8_t dataArea[EVS_MAX_DATA_LEN];
} evs_service_feedback_query_log;

//设备维护指令服务下发参数
// 控制类型
typedef struct
{
	uint8_t ctrlType;
} evs_service_devCtrl;

//设备维护指令服务回复参数
// 1	当前控制类型
// 2	失败原因
typedef struct
{
	uint8_t ctrlType;
	uint32_t reason;
} evs_service_feedback_devCtrl;

// 充电枪电子锁控制服务下发参数
// 1	充电枪编号
// 2	控制
typedef struct
{
	uint8_t gunNo;
	uint8_t lockParam;
} evs_service_lockCtrl;

//充电枪电子锁控制服务回复参数
// 1	充电枪编号
// 2	电子锁状态
// 3	结果
typedef struct
{
	uint8_t gunNo;
	uint8_t lockStatus;
	uint32_t resCode;
} evs_service_feedback_lockCtrl;

// 计费模型请求事件
// 1	充电枪编号
// 2	当前模型编号
typedef struct
{
	uint8_t gunNo;
	uint8_t modelId[EVS_MAX_MODEL_ID_LEN];
} evs_event_ask_feeModel;

//计费模型更新服务下发参数
// 1		模型Id
// 2		失效时间 模型失效时间，格式为:YYYYMMDD
// 3		时段数N 取值范围：1—14
// 4		时段开始时间点
// 5		时段标志
// 6		电费
// 7		服务费
typedef struct
{
	uint8_t modelId[EVS_MAX_MODEL_ID_LEN];
	uint8_t validTime[8];
	uint8_t segNo;
	uint8_t timeSeg[14][4];
	uint8_t segFlag[14];
	uint32_t chargeFee[14];
	uint32_t serviceFee[14];
} evs_service_issue_feeModel;

//计费模型更新结果设备回复参数
// 1		计量计费模型编号
// 2		失败原因
typedef struct
{
	uint8_t modelId[EVS_MAX_MODEL_ID_LEN];
	uint8_t res;
} evs_service_feedback_feeModel;

//远程启动充电服务下发参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	启动方式
// 5	充电模式
// 6	限制值
// 7	停机码
// 8	启动模式
// 9	辅助电源电压
// 10	插枪事件时间戳
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t startType;
	uint8_t chargeMode;
	uint32_t limitData;
	uint32_t stopCode;
	uint8_t startMode;
	uint8_t auxiVolt;
	uint32_t insertGunTime;
} evs_service_startCharge;

//启动充电服务设备回复参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
} evs_service_feedback_startCharge;

//启动充电结果事件参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	启动结果
// 5	故障代码
// 6	vin码

typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t startResult;
	uint32_t faultCode;
	uint8_t vinCode[EVS_MAX_CAR_VIN_LEN];
} evs_event_startResult;

//启动充电鉴权事件参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	启动方式
// 5	鉴权码
// 6	电池SOC
// 7	电车容量
// 8	已充电次数
// 9	当前电池电压
// 10	辅助电源电压
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t startType;
	uint8_t vinCode[EVS_MAX_CAR_VIN_LEN];
	uint8_t batterySOC;
	uint32_t batteryCap;
	uint32_t chargeTimes;
	uint32_t batteryVol;
	uint8_t auxiVolt;
} evs_event_startCharge;

//鉴权充电服务下发参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	VIN码/反向扫码二维码
// 5	鉴权结果
// 6	充电模式
// 7	限制值
// 8	停机码
// 9	启动模式
// 10	插枪事件时间戳

typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t authCode[40]; //若启动方式为反向扫码，填入二维码信息；若启动方式为即插即充，填VIN信息。
	uint8_t result;
	uint8_t chargeMode;
	uint32_t limitData;
	uint32_t stopCode;
	uint8_t startMode;
	uint32_t insertGunTime;
} evs_service_authCharge;

//鉴权启动充电服务设备回复参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
} evs_service_feedback_authCharge;

//远程停止充电服务下发参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	停止原因
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t stopReason;
} evs_service_stopCharge;

//远程停止充电服务设备回复参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
} evs_service_feedback_stopCharge;

//停止充电结果事件上传参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	停止结果
// 5	停止原因
// 6	停止失败原因
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t stopResult;
	uint32_t resultCode;
	uint8_t stopFailReson;
} evs_event_stopCharge;

//交易记录事件上传参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	VIN
// 5	计量计费类型
// 6	开始充电时间
// 7	结束充电时间
// 8	启动时SOC
// 9	停止时SOC
// 10	停止充电原因
// 11	计量计费模型编号
// 12	电表总起示值
// 13	电表总止示值
// 14	总电量
// 15	尖电量
// 16	峰电量
// 17	平电量
// 18	谷电量
// 19	总电费
// 20	总服务费
// 21	尖电费
// 22	峰电费
// 23	平电费
// 24	谷电费
// 25	尖服务费
// 26	峰服务费
// 27	平服务费
// 28	谷服务费
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t vinCode[EVS_MAX_CAR_VIN_LEN];
	uint8_t timeDivType;
	uint32_t chargeStartTime;
	uint32_t chargeEndTime;
	uint8_t startSoc;
	uint8_t endSoc;
	uint32_t reason;
	uint8_t modelId[EVS_MAX_MODEL_ID_LEN];
	uint32_t sumStart;
	uint32_t sumEnd;
	uint32_t totalElect;
	uint32_t sharpElect;
	uint32_t peakElect;
	uint32_t flatElect;
	uint32_t valleyElect;
	uint32_t totalPowerCost;
	uint32_t totalServCost;
	uint32_t sharpPowerCost;
	uint32_t peakPowerCost;
	uint32_t flatPowerCost;
	uint32_t valleyPowerCost;
	uint32_t sharpServCost;
	uint32_t peakServCost;
	uint32_t flatServCost;
	uint32_t valleyServCost;
} evs_event_tradeInfo;

//交易记录确认服务下发参数
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	交易记录上传结果
typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t errcode;
} evs_service_confirmTrade;

//故障告警事件上传参数
// 1	枪编号
// 2	故障总
// 3	告警总
// 4	故障点数据
// 5	告警点数据
typedef struct
{
	uint8_t gunNo;
	uint16_t faultSum;
	uint16_t warnSum;
	uint16_t faultValue[EVS_MAX_ALARM_LEN];
	uint16_t warnValue[EVS_MAX_ALARM_LEN];
} evs_event_alarm;

//预约充电服务下发参数
// 1	充电枪编号
// 2	预约方式 10：立即预约 11：取消预约
// 3	预约等候时长  分钟数，大于0，且不大于1440
typedef struct
{
	uint8_t gunNo;
	uint8_t appomathod;
	uint16_t appoDelay;
} evs_service_rsvCharge;

//预约充电服务设备回复参数
// 1	充电枪编号
// 2	预约方式
// 3	预约结果
// 4	失败原因
typedef struct
{
	uint8_t gunNo;
	uint8_t appomathod;
	uint8_t ret;
	uint8_t reason;
} evs_service_feedback_rsvCharge;

//地锁控制服务下发参数
// 1	充电枪编号
// 2	控制指令
typedef struct
{
	uint8_t gunNo;
	uint8_t ctrlFlag;
} evs_service_groundLock_ctrl;

//地锁控制服务回复参数
// 1	充电枪编号
// 2	控制结果
// 3	失败原因
typedef struct
{
	uint8_t gunNo;
	uint8_t result;
	uint8_t reason;
} evs_service_feedback_groundLock_ctrl;

//地锁状态变化事件上传参数
// 1	充电枪编号
// 2	地锁状态
// 3	供电方式
// 4	电池状态
// 5	锁舌状态
// 6	锁舌受外力强制动作
// 7	电池低电量报警
// 8	电池SOC
// 9	开闭次数
typedef struct
{
	uint8_t gunNo;
	uint8_t lockState;
	uint8_t powerType;
	uint8_t cellState;
	uint8_t lockerState;
	uint8_t lockerForced;
	uint8_t lowPower;
	uint8_t soc;
	uint32_t openCnt;
} evs_event_groundLock_change;

//智能门锁控制服务下发参数
// 1	门锁编号
// 2	控制指令
typedef struct
{
	uint8_t lcokNo;
	uint8_t ctrlFlag;
} evs_service_gateLock_ctrl;

//智能门锁控制服务回复参数
// 1	充电枪编号
// 2	控制结果
typedef struct
{
	uint8_t lockNo;
	uint8_t result;
} evs_service_feedback_gateLock_ctrl;

//智能门锁状态变化事件上传参数
// 1	充电枪编号
// 2	智能门锁状态
typedef struct
{
	uint8_t lockNo;
	uint8_t lockState;
} evs_event_gateLock_change;

//有序充电策略服务下发参数
// 1	订单流水号
// 2	策略生效时间
// 3	策略配置功率
typedef struct
{
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t validTime[5][4]; //字符串数组。时间格式采用HHMM，24小时制。策略范围24小时内最多五段 例如 ：[time1,time2,time3…]。
	uint8_t kw[5];			 //整型数组。功率精确到0.1KW[kw1,kw2,kw3…]
} evs_service_orderCharge;

//有序充电策略服务设备回复参数
// 1	订单流水号
// 2	返回结果
// 3	失败原因
typedef struct
{
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t result;
	uint8_t reason;
} evs_service_feedback_orderCharge;

//交直流充电设备枪状态变化事件上传参数
// 1	充电枪编号
// 2	发生时刻
// 3	状态变更点数总数
// 4	变位点数据
typedef struct
{
	uint8_t gunNo;
	uint32_t time;
	uint16_t Sum;
	uint16_t val[7]; //格式为“[标识1：值,标识2：值,...标识N：值]”，标识详见附录 I
} evs_event_pile_stutus_change;

/*********************************************交流业务相关************************************************************/
//交流设备属性上报参数
// 1	网络类型
// 2	网络信号等级
// 3	网络运营商
// 4	A相采集电压
// 5	A相采集电流
// 6	B相采集电压
// 7	B相采集电流
// 8	C相采集电压
// 9	C相采集电流
// 10	桩内温度
// 11	计量计费模型编号

typedef struct
{
	uint8_t netType;
	uint8_t sigVal;
	uint8_t netID;
	uint32_t acVolA;
	uint32_t acCurA;
	uint32_t acVolB;
	uint32_t acCurB;
	uint32_t acVolC;
	uint32_t acCurC;
	uint16_t caseTamp;
	uint8_t modelID[EVS_MAX_MODEL_ID_LEN];
} evs_property_acPile;

//交流充电枪充电中实时监测属性
// 1	充电枪编号
// 2	运行状态
// 3	充电状态
// 4	连接确认开关状态
// 5	输出继电器状态
// 6	充电接口电子锁状态
// 7	充电枪头温度
// 8	充电设备A相输出电压
// 9	充电设备A相输出电流
// 10	充电设备B相输出电压
// 11	充电设备B相输出电流
// 12	充电设备C相输出电压
// 13	充电设备C相输出电流
// 14	平台交易流水号
// 15	设备交易流水号
// 16	充电实际功率
// 17	累计充电时间
// 18	总电量
// 19	尖电量
// 20	峰电量
// 21	平电量
// 22	谷电量
// 23	总金额
// 24	总电费
// 25	总服务费

typedef struct
{
	uint8_t gunNo;
	uint8_t RunStatus;
	uint8_t WorkStatus;
	uint8_t conStatus;
	uint8_t outRelayStatus;
	uint8_t eLockStatus;
	uint16_t gunTemp;
	uint32_t acVolA;
	uint32_t acCurA;
	uint32_t acVolB;
	uint32_t acCurB;
	uint32_t acVolC;
	uint32_t acCurC;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint32_t realPower;
	uint32_t chgTime;
	uint32_t totalElect;
	uint32_t sharpElect;
	uint32_t peakElect;
	uint32_t flatElect;
	uint32_t valleyElect;
	uint32_t totalCost;
	uint32_t totalPowerCost;
	uint32_t totalServCost;
} evs_property_ac_work;

//交流充电枪非充电中实时监测属性
// 1	充电枪编号
// 2	运行状态
// 3	充电状态
// 4	连接确认开关状态
// 5	输出继电器状态
// 6	充电接口电子锁状态
// 7	充电枪头温度
// 8	充电设备A相输出电压
// 9	充电设备A相输出电流
// 10	充电设备B相输出电压
// 11	充电设备B相输出电流
// 12	充电设备C相输出电压
// 13	充电设备C相输出电流
typedef struct
{
	uint8_t gunNo;
	uint8_t RunStatus;
	uint8_t WorkStatus;
	uint8_t conStatus;
	uint8_t outRelayStatus;
	uint8_t eLockStatus;
	uint16_t gunTemp;
	uint32_t acVolA;
	uint32_t acCurA;
	uint32_t acVolB;
	uint32_t acCurB;
	uint32_t acVolC;
	uint32_t acCurC;
} evs_property_ac_nonWork;

/*********************************************直流业务相关************************************************************/

//直流设备属性上报参数
// 1	网络类型
// 2	网络信号等级
// 3	网络运营商
// 4	A相采集电压
// 5	A相采集电流
// 6	B相采集电压
// 7	B相采集电流
// 8	C相采集电压
// 9	C相采集电流
// 10	设备内温度
// 11	设备入风口温度
// 12	设备出风口温度
// 13	计量计费模型编号
typedef struct
{
	uint8_t netType;
	uint8_t sigVal;
	uint8_t netID;
	uint32_t acVolA;
	uint32_t acCurA;
	uint32_t acVolB;
	uint32_t acCurB;
	uint32_t acVolC;
	uint32_t acCurC;
	uint16_t caseTamp;
	uint16_t inletTemp;
	uint16_t outletTemp;
	uint8_t modelID[EVS_MAX_MODEL_ID_LEN];
} evs_property_dcPile;
//直流充电枪BMS监测属性
// 1	充电枪编号
// 2	平台交易流水号
// 3	设备交易流水号
// 4	SOC
// 5	BMS通信协议版本号
// 6	最高允许充电总电压
// 7	电池类型
// 8	整车动力蓄电池额定容量
// 9	整车动力蓄电池额定总电压
// 10	单体动力蓄电池最高允许充电电压
// 11	最高允许充电电流
// 12	整车动力蓄电池标称总能量
// 13	最高允许充电总电压
// 14	最高允许温度
// 15	整车动力蓄电池当前电池电压

typedef struct
{
	uint8_t gunNo;
	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t socVal;
	uint8_t BMSVer;
	uint16_t BMSMaxVol;
	uint8_t batType;
	uint16_t batRatedCap;
	uint16_t batRatedTotalVol;
	uint16_t singlBatMaxAllowVol;
	uint16_t maxAllowCur;
	uint16_t battotalEnergy;
	uint16_t maxVol;
	uint16_t maxTemp;
	uint16_t batCurVol;
} evs_property_BMS;

//直流充电枪充电中实时监测属性
// 充电枪编号
// 运行状态
// 充电状态
// 充电枪连接状态
// 充电枪电子锁状态
// 直流输出接触器K1状态
// 直流输出接触器K2状态
// DC+熔断器状态
// DC-熔断器状态
// 充电接口DC+温度
// 充电接口DC-温度
// 输出电压
// 输出电流
// 平台交易流水号
// 设备交易流水号
// 充电类型
// 充电设备输出功率
// 累计充电时间
// SOC
// 充电需求电压
// 充电需求电流
// 充电模式
// BMS充电电压测量值
// BMS充电电流测量值
// 最高单体动力蓄电池电压
// 估算充满剩余充电时间
// 最高动力蓄电池温度
// 最低动力蓄电池温度
// 总电量
// 尖电量
// 峰电量
// 平电量
// 谷电量
// 总金额
// 总电费
// 总服务费
typedef struct
{
	uint8_t gunNo;
	uint8_t RunStatus;
	uint8_t WorkStatus;
	uint8_t conStatus;
	uint8_t outRelayStatus;
	uint8_t eLockStatus;

	uint8_t DCK1Status;
	uint8_t DCK2Status;
	uint8_t DCPlusFuseStatus;
	uint8_t DCMinusFuseStatus;
	uint16_t conTemp1;
	uint16_t conTemp2;
	uint32_t dcVol;
	uint32_t dcCur;

	uint8_t preTradeNo[EVS_MAX_TRADE_LEN];
	uint8_t tradeNo[EVS_MAX_TRADE_LEN];
	uint8_t chgType;
	uint32_t realPower;
	uint32_t chgTime;
	uint8_t socVal;
	uint16_t needVol;
	uint16_t needCur;
	uint32_t totalElect;
	uint8_t chargeMode;
	uint16_t bmsVol;
	uint16_t bmsCur;
	uint16_t SingleMHV;
	uint16_t remainT;
	uint16_t MHTemp;
	uint16_t MLTemp;
	uint32_t sharpElect;
	uint32_t peakElect;
	uint32_t flatElect;
	uint32_t valleyElect;
	uint32_t totalCost;
	uint32_t totalPowerCost;
	uint32_t totalServCost;
} evs_property_dc_work;
//直流充电枪非充电中实时监测属性
// 充电枪编号
// 运行状态
// 充电状态
// 充电枪连接状态
// 充电枪电子锁状态
// 直流输出接触器K1状态
// 直流输出接触器K2状态
// DC+熔断器状态
// DC-熔断器状态
// 充电接口DC+温度
// 充电接口DC-温度
// 输出电压
// 输出电流
typedef struct
{
	uint8_t gunNo;
	uint8_t RunStatus;
	uint8_t WorkStatus;
	uint8_t conStatus;
	uint8_t eLockStatus;

	uint8_t DCK1Status;
	uint8_t DCK2Status;
	uint8_t DCPlusFuseStatus;
	uint8_t DCMinusFuseStatus;
	uint16_t conTemp1;
	uint16_t conTemp2;
	uint32_t dcVol;
	uint32_t dcCur;
} evs_property_dc_nonwork;

//直流输入电表底值监测属性
// 充电枪编号
// 采集时间
// 通信地址
// 表号
// 电表资产编码
// 电表底值
// A相正向总电量
// B相正向总电量
// C相正向总电量
typedef struct
{
	uint8_t gunNo;
	uint32_t acqTime;
	uint8_t mailAddr[6]; //压缩BCD
	uint8_t meterNo[6];
	uint8_t assetID[32];
	uint32_t sumMeter;
	uint32_t ApElect;
	uint32_t BpElect;
	uint32_t CpElect;
} evs_property_dc_input_meter;

/******************************************公共属性区*************************************************/

//交直流输出电表底值监测属性
// 1	充电枪编号
// 2	采集时间
// 3	通信地址
// 4	表号
// 5	电表资产编码
// 6	电表底值
// 7	最后交易流水
// 8	充电中订单的已充电量
typedef struct
{
	uint8_t gunNo;
	uint32_t acqTime;
	uint8_t mailAddr[6]; //压缩BCD
	uint8_t meterNo[6];
	uint8_t assetID[32];
	uint32_t sumMeter;
	uint8_t lastTrade[EVS_MAX_TRADE_LEN];
	uint32_t power;
} evs_property_meter;



#endif