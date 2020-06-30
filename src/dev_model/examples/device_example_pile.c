#include "interface.h"
#include "protocol.h"
#include "wrappers.h"

char _product_key[IOTX_PRODUCT_KEY_LEN + 1] = "a1X3BP5v0vn";
char _device_name[IOTX_DEVICE_NAME_LEN + 1] = "EvseSdkTestDevice";
char _device_secret[IOTX_DEVICE_SECRET_LEN + 1] = "38be4ad34bd079b4f765f71a3a30fc4e";
char _device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1] = "";
char _device_uid[IOTX_DEVICE_UID_LEN + 1] = "1587416872968745";

#define DEVICE_EXAMPLE_TRACE(...)                               \
	do                                                          \
	{                                                           \
		HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__); \
		HAL_Printf(__VA_ARGS__);                                \
		HAL_Printf("\033[0m\r\n");                              \
	} while (0)

/** 建连成功事件回调 */
static int evs_connected_event_handler(void)
{
	DEVICE_EXAMPLE_TRACE(" EVS--- Cloud Connected\n");
	return 0;
}

/** 断开连接事件回调 */
static int evs_disconnected_event_handler(void)
{
	DEVICE_EXAMPLE_TRACE("EVS--- Cloud Disconnected\n");
	return 0;
}

/** 事件回调：接收到云端回复属性上报应答 **/
static int evs_report_reply_event_handler(const int msgid, const int code, const char *reply,
										  const int reply_len)
{
	DEVICE_EXAMPLE_TRACE("EVS--- Message Post Reply Received, Message ID: %d, Code: %d, Reply: %.*s", msgid, code,
						 reply_len,
						 (reply == NULL) ? ("NULL") : (reply));
	return 0;
}

/** 事件回调：接收到云端回复的事件上报应答 **/
static int evs_trigger_event_reply_event_handler(const int msgid, const int code, const char *eventid,
												 const int eventid_len, const char *message, const int message_len)
{
	DEVICE_EXAMPLE_TRACE("EVS--- Trigger Event Reply Received, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s",
						 msgid, code,
						 eventid_len,
						 eventid, message_len, message);

	return 0;
}

/** 事件回调: SDK内部运行状态打印 **/
static int evs_sdk_state_dump(int ev, const char *msg)
{
	DEVICE_EXAMPLE_TRACE("EVS--- received state event, -0x%04x(%s)\n", -ev, msg);
	return 0;
}

/** 事件回调: 证书设置 **/
static int evs_device_cert_set(const evs_device_meta meta)
{
	//在这里实现证书三元组的存储,下面代码只是示例，设置成功返回0，设置失败返回-1

	int len = strlen(meta.product_key);
	memset(_product_key, 0x0, sizeof(_product_key));
	strncpy(_product_key, meta.product_key, IOTX_PRODUCT_KEY_LEN);
	_product_key[len] = '\0';

	len = strlen(meta.device_name);
	memset(_device_name, 0x0, sizeof(_device_name));
	strncpy(_device_name, meta.device_name, IOTX_DEVICE_NAME_LEN);
	_device_name[len] = '\0';

	len = strlen(meta.device_secret);
	memset(_device_secret, 0x0, sizeof(_device_secret));
	strncpy(_device_secret, meta.device_secret, IOTX_DEVICE_SECRET_LEN);
	_device_secret[len] = '\0';

	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_cert_set\n");
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.product_key is %s\n", meta.product_key);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.device_name is %s\n", meta.device_name);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.device_secret is %s\n", meta.device_secret);
	return 0;
}
/** 事件回调: 证书读取 **/
static int evs_device_cert_get(evs_device_meta *meta)
{
	//在这里实现证书三元组的读取,下面为示例获取成功返回0，如果证书为空返回-1

	int len = strlen(_product_key);
	if (len < 5)
	{
		DEVICE_EXAMPLE_TRACE("_product_key length is %d", len);
		return -1;
	}

	memset(meta->product_key, 0x0, sizeof(meta->product_key));
	strncpy(meta->product_key, _product_key, IOTX_PRODUCT_KEY_LEN);
	meta->product_key[len] = '\0';

	len = strlen(_device_name);
	if (len < 2)
	{
		DEVICE_EXAMPLE_TRACE("_device_name length is %d", len);
		return -1;
	}
	memset(meta->device_name, 0x0, sizeof(meta->device_name));
	strncpy(meta->device_name, _device_name, IOTX_DEVICE_NAME_LEN);
	meta->device_name[len] = '\0';

	len = strlen(_device_secret);
	if (len < 5)
	{
		DEVICE_EXAMPLE_TRACE("_device_secret length is %d", len);
		return -1;
	}
	memset(meta->device_secret, 0x0, sizeof(meta->device_secret));
	strncpy(meta->device_secret, _device_secret, IOTX_DEVICE_SECRET_LEN);
	meta->device_secret[len] = '\0';

	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_cert_get\n");
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->product_key is %s\n", meta->product_key);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->device_name is %s\n", meta->device_name);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->device_secret is %s\n", meta->device_secret);
	return 0;
}
/** 事件回调: 设备注册码获取 **/
static int evs_device_reg_code_get(char *device_reg_code)
{
	//在这里实现注册码的读取操作，读取成功返回注册码长度，如果注册码为NULL或读取失败返回-1

	int len = strlen(_device_reg_code);
	memset(device_reg_code, 0x0, IOTX_DEVICE_REG_CODE_LEN);
	strncpy(device_reg_code, _device_reg_code, IOTX_DEVICE_REG_CODE_LEN);
	device_reg_code[len] = '\0';
	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_reg_code_get\n");
	DEVICE_EXAMPLE_TRACE("EVS--- device_reg_code is %s\n", device_reg_code);
	return strlen(_device_reg_code);
}
/** 事件回调: 设备唯一编码获取 **/
static int evs_device_uid_get(char *device_uid)
{
	//在这里实现注册码的读取操作，读取成功返回注册码长度，如果注册码为NULL或读取失败返回-1

	int len = strlen(_device_uid);
	memset(device_uid, 0x0, IOTX_DEVICE_UID_LEN);
	strncpy(device_uid, _device_uid, IOTX_DEVICE_UID_LEN);
	device_uid[len] = '\0';
	return strlen(_device_uid);
}

/******************************************SDK提供的接口供用户调用*************************************************/

/**
 *
 * 函数 evs_send_event() SDK内部实现的事件发送接口, 供使用者调用。
 * ---
 * Interface of evs_send_event() implemented by SDK， provide for user of SDK.
 *
 * 
 */
/**
 * @brief Send pile event data to SDK.
 *---
 * @param [in] event_type: @n the event you want to send.
 * @param [in] param: @n the event data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
//int  evs_send_event(evs_cmd_event_enum event_type, void *param);

/**
 *
 * 函数 evs_send_property() SDK内部实现的事件发送接口, 供使用者调用。
 * ---
 * Interface of evs_send_property() implemented by SDK， provide for user of SDK.
 *
 * 
 */
/**
 * @brief Send pile porperty data to SDK.
 *---
 * @param [in] event_type: @n the property you want to send.
 * @param [in] param: @n the property data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
//int  evs_send_property(evs_cmd_property_enum property_type, void *param);

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
 * 函数 callback_service_dev_maintain() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_dev_maintain() requires to be implemented by user of SDK.
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
int callback_service_lockCtrl(evs_service_lockCtrl *param, evs_service_feedback_lockCtrl *result)
{
	result->gunNo = 0;
	result->lockStatus = 10;
	DEVICE_EXAMPLE_TRACE("callback_service_lockCtrl:param is gunNo: %d, result is lockStatus；%d \n", param->gunNo, result->lockStatus);
	return 0;
}
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
int callback_service_startCharge(evs_service_startCharge *param, evs_service_feedback_startCharge *result)
{
	memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
	memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
	result->gunNo = param->gunNo;
	DEVICE_EXAMPLE_TRACE("callback_service_startCharge:param is gunNo:%d,result is tradeNo:%s \n", param->gunNo, result->tradeNo);
	return 0;
}

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
 * @param [out] result: @n the result data will be written by user of SDK.
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
int callback_service_gateLock_ctrl(evs_service_gateLock_ctrl *param, evs_service_feedback_gateLock_ctrl *result)
{
	result->lockNo = 1;
	result->result = 10;
	DEVICE_EXAMPLE_TRACE("evs_gate_lock_service:param is ctrlFlag: %d, result is lockNo: %d \n", param->ctrlFlag, param->lockNo);
	return 0;
}

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
/************直流功率调节控制与交流有序充电共用回调****************/
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
int callback_service_get_config(evs_data_dev_config *result)
{
	return 0;
}
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
int callback_service_update_config(evs_data_dev_config *param, int *result)
{
	return 0;
}

/**
 *ota升级 需要动态申请内存，根据设备当前状态通过返回值确定是否升级
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
 * @param [out] buffer: @n the ota buffer that need you to apply by malloc.

 * @param [out] buffer_length: @n the buffer length of ota.
 * @return do not update device -1 update device 0.
 * @see None.
 * @note None.
 */
int callback_service_ota_update(const char *version)
{
	unsigned char buf[1024] = {};
	DEVICE_EXAMPLE_TRACE("version is %s\n", version);
	evs_linkkit_fota(buf, 1024);
	return 0; //升级
}

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
int callback_service_time_sync(const unsigned int timestamp)
{
	return 0;
}

int main()
{
	int cnt = 0;
	int res = 0;
	/* 注册回调函数 */

	//目前仅为了测试
	/*
#ifdef DYNAMIC_REGISTER
	HAL_SleepMs(1000);
	return 0;
#endif
*/
	/** 事件回调: SDK充电枪电子锁控制回调 **/
	EVS_RegisterCallback(EVS_CTRL_LOCK_SRV, callback_service_lockCtrl);
	/** 事件回调: 充电桩智能门锁控制回调 **/
	EVS_RegisterCallback(EVS_GATE_LOCK_SRV, callback_service_gateLock_ctrl);
	/** 事件回调: 启动充电回调 **/
	EVS_RegisterCallback(EVS_START_CHARGE_SRV, callback_service_startCharge);
	EVS_RegisterCallback(EVS_CONF_GET_SRV, callback_service_get_config);
	EVS_RegisterCallback(EVS_CONF_UPDATE_SRV, callback_service_update_config);

	/** 事件回调: SDK内部运行状态打印 **/
	EVS_RegisterCallback(EVS_STATE_EVERYTHING, evs_sdk_state_dump);
	/** 建连成功事件回调 */
	EVS_RegisterCallback(EVS_CONNECT_SUCC, evs_connected_event_handler);
	/** 断开连接事件回调 */
	EVS_RegisterCallback(EVS_DISCONNECTED, evs_disconnected_event_handler);
	/** 事件回调：接收到云端回复的事件上报应答 **/
	EVS_RegisterCallback(EVS_TRIGGER_EVENT_REPLY, evs_trigger_event_reply_event_handler);
	/** 事件回调：接收到云端回复属性上报应答 **/
	EVS_RegisterCallback(EVS_REPORT_REPLY, evs_report_reply_event_handler);
	/** 事件回调：设备证书读取 **/
	EVS_RegisterCallback(EVS_CERT_GET, evs_device_cert_get);
	/** 事件回调：设备证书设置 **/
	EVS_RegisterCallback(EVS_CERT_SET, evs_device_cert_set);
	/** 事件回调：设备注册码获取 **/
	EVS_RegisterCallback(EVS_DEVICE_REG_CODE_GET, evs_device_reg_code_get);
	/** 事件回调：设备唯一码获取 **/
	EVS_RegisterCallback(EVS_DEVICE_UID_GET, evs_device_uid_get);
	/** 事件回调：时钟同步回调 **/
	EVS_RegisterCallback(EVS_TIME_SYNC, callback_service_time_sync);
	/** 事件回调：ota升级服务回调 **/
	EVS_RegisterCallback(EVS_OTA_UPDATE, callback_service_ota_update);
	/*如果使用设备不能进行注册码外部输入则调用设备唯一码进行换取注册码，然后注册码换证书
	res = evs_linkkit_new(0,1);
	如果设备可以进行注册码输入则调用，使用注册码换证书
	res = evs_linkkit_new(0,0);
	*/
	res = evs_linkkit_new(0, 0);
	if (res < 0)
	{
		return -1;
	}

	evs_property_dcPile dcPile_data;

	dcPile_data.acCurA = 380;
	dcPile_data.acCurB = 380;
	dcPile_data.acCurC = 380;

	dcPile_data.acVolA = 380;
	dcPile_data.acVolB = 380;
	dcPile_data.acVolC = 380;

	memset(dcPile_data.eleModelId, 0, 17);
	memcpy(dcPile_data.eleModelId, "111111111111", strlen("111111111111"));
	memset(dcPile_data.serModelId, 0, 17);
	memcpy(dcPile_data.serModelId, "111111111111", strlen("111111111111"));

	dcPile_data.sigVal = 31;
	dcPile_data.caseTemp = 100;
	dcPile_data.inletTemp = 70;
	dcPile_data.netId = 11;
	dcPile_data.netType = 13;
	dcPile_data.outletTemp = 30;

	evs_event_fireware_info fireware_info;
	unsigned char meterAddr1[6] = {0x12, 0x23, 0x34, 0x45, 0x56, 0x67};
	unsigned char meterAddr2[6] = {0};

	memset(fireware_info.inMeter, 0, sizeof(fireware_info.inMeter));
	memset(fireware_info.outMeter, 0, sizeof(fireware_info.outMeter));

	memcpy(fireware_info.inMeter[0], meterAddr1, 6);
	memcpy(fireware_info.inMeter[1], meterAddr1, 6);

	memcpy(fireware_info.outMeter[0], meterAddr1, 6);

	memset(fireware_info.btMac, 0, 33);
	memcpy(fireware_info.btMac, "aa:bb:cc:dd", strlen("aa:bb:cc:dd"));
	fireware_info.CT = 30;

	memset(fireware_info.devSn, 0, 17);
	memcpy(fireware_info.devSn, "2222aaaabbccdd", strlen("2222aaaabbccdd"));
	fireware_info.devType = 10;
	fireware_info.gridType = 12;
	fireware_info.height = 100;
	fireware_info.isGateLock = 10;
	fireware_info.isGroundLock = 10;
	fireware_info.latitude = 0;
	fireware_info.longitude = 0;
	fireware_info.meaType = 10;
	memset(fireware_info.eleModelId, 0, 17);
	memcpy(fireware_info.eleModelId, "1111aaaabbccdd", strlen("1111aaaabbccdd"));
	memset(fireware_info.serModelId, 0, 17);
	memcpy(fireware_info.serModelId, "1111aaaabbccdd", strlen("1111aaaabbccdd"));

	fireware_info.otMaxVol = 500;
	fireware_info.otMinVol = 220;
	fireware_info.otRate = 70;
	fireware_info.otCur = 380;
	fireware_info.portNum = 1;
	memset(fireware_info.simMac, 0, 33);
	memset(fireware_info.simNo, 0, 20);
	memset(fireware_info.stakeModel, 0, 20);
	memcpy(fireware_info.simMac, "aa:bb:cc:d", strlen("aa:bb:cc:d"));
	memcpy(fireware_info.simNo, "111111111111111111", strlen("111111111111111111"));
	memcpy(fireware_info.stakeModel, "222111111111111111", strlen("222111111111111111"));
	fireware_info.vendorCode = 1287;

	while (1)
	{
		evs_mainloop();
		if ((cnt % 100) == 0)
		{
			evs_send_property(EVS_CMD_PROPERTY_DCPILE, &dcPile_data);
		}
		if ((cnt % 200) == 0)
		{
			evs_send_event(EVS_CMD_EVENT_FIREWARE_INFO, &fireware_info);
		}
		if ((cnt % 300) == 0)
		{
			//evs_send_event(EVS_CMD_EVENT_STARTRESULT, &event_startResult_data);
		}
		HAL_SleepMs(100);
		cnt++;
	}

	return 0;
}
