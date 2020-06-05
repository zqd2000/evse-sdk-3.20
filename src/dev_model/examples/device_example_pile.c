#include "interface.h"
#include "protocol.h"
#include "wrappers.h"
#include "protocol_data_def.h"

/*智能门锁回调函数*/
int evs_gate_lock_service(const int input_data,int * output_data)
{
	*output_data = input_data + 5;
	printf("evs_gate_lock_service:input_data is %d,*output_data is %d \n",input_data,*output_data);
	return 0;
}
/*开始充电回调函数*/
int evs_charge_start_service(const int input_data,int * output_data)
{
	*output_data = input_data + 10;
	printf("evs_charge_start_service:input_data is %d,*output_data is %d \n",input_data,*output_data);
	return 0;
}

/** 建连成功事件回调 */
static int evs_connected_event_handler(void)
{
    printf(" EVS--- Cloud Connected\n");
    return 0;
}

/** 断开连接事件回调 */
static int evs_disconnected_event_handler(void)
{
    printf("EVS--- Cloud Disconnected\n");

    return 0;
}


/** 事件回调：接收到云端回复属性上报应答 **/
static int evs_report_reply_event_handler(const int msgid, const int code, const char *reply,
        const int reply_len)
{
    printf("EVS--- Message Post Reply Received, Message ID: %d, Code: %d, Reply: %.*s", msgid, code,
                  reply_len,
                  (reply == NULL) ? ("NULL") : (reply));
    return 0;
}

/** 事件回调：接收到云端回复的事件上报应答 **/
static int evs_trigger_event_reply_event_handler(const int msgid, const int code, const char *eventid,
        const int eventid_len, const char *message, const int message_len)
{
    printf("EVS--- Trigger Event Reply Received, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s",
                  msgid, code,
                  eventid_len,
                  eventid, message_len, message);

    return 0;
}

/** 事件回调: SDK内部运行状态打印 **/
static int evs_sdk_state_dump(int ev, const char *msg)
{
    printf("EVS--- received state event, -0x%04x(%s)\n", -ev, msg);
    return 0;
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
//int8_t evs_send_event(evs_cmd_event_enum event_type, void *param);

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
//int8_t evs_send_property(evs_cmd_property_enum property_type, void *param);

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
int8_t callback_service_query_log(evs_service_query_log *param, evs_service_feedback_query_log *result);

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
int8_t callback_service_devCtrl(evs_service_devCtrl *param, evs_service_feedback_devCtrl *result);

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
int8_t callback_service_lockCtrl(evs_service_lockCtrl *param, evs_service_lockCtrl *result);

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
int8_t callback_service_issue_feeModel(evs_service_issue_feeModel *param, evs_service_issue_feeModel *result);

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
int8_t callback_service_startCharge(evs_service_startCharge *param, evs_service_startCharge *result);

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
int8_t callback_service_authCharge(evs_service_authCharge *param, evs_service_authCharge *result);

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
int8_t callback_service_stopCharge(evs_service_stopCharge *param, evs_service_stopCharge *result);

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
int8_t callback_service_rsvCharge(evs_service_rsvCharge *param, evs_service_rsvCharge *result);

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
int8_t callback_service_confirmTrade(evs_service_confirmTrade *param, evs_service_confirmTrade *result);

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
int8_t callback_service_grounLock_ctrl(evs_service_groundLock_ctrl *param, evs_service_groundLock_ctrl *result);

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
int8_t callback_service_gateLock_ctrl(evs_service_gateLock_ctrl *param, evs_service_gateLock_ctrl *result);

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
int8_t callback_service_orderCharge(evs_service_orderCharge *param, evs_service_orderCharge *result);





int main()
{
    int cnt = 0;
	/* 注册回调函数 */
	
	evs_linkkit_new(0);

    EVS_RegisterCallback(EVS_GATA_LOCK_SRV, evs_gate_lock_service);
	
    EVS_RegisterCallback(EVS_CHARGE_START_SRV, evs_charge_start_service);
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
	while (1)
	{
		//protocol_service_callback(EVS_GATA_LOCK_SRV);
		//protocol_service_callback(EVS_CHARGE_START_SRV);
		//evs_poll();
		evs_mainloop();
		if((cnt%100)==0)
		{
			//evs_send_event();
			evs_send_property(evs_send_property_dcPile, &cnt);
		}
		if((cnt%200)==0)
		{
			evs_send_event(evs_send_event_fireware_info, &cnt);
		}
		HAL_SleepMs(10);
		cnt++;

	}
	
    return 0;
}