/*
 * Copyright (C) 2015-2019 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "infra_config.h"
#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "infra_state.h"
#include "dev_model_api.h"
#include "wrappers.h"
#include "cJSON.h"
#ifdef ATM_ENABLED
#include "at_api.h"
#endif
#include "protocol.h"
#include "interface.h"
#include "protocol_data_def.h"

//#include "protocol_data_def.h"

char g_product_key[IOTX_PRODUCT_KEY_LEN + 1] = "a1j42i9aAVT";
/* setup your productSecret !!! */
char g_product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "Pwe3oQ5g11H50rXC";
/* setup your deviceName !!! */
char g_device_name[IOTX_DEVICE_NAME_LEN + 1] = "sdkTestDevice";
/* setup your deviceSecret !!! */
char g_device_secret[IOTX_DEVICE_SECRET_LEN + 1] = "pxxr7YkE5LR9Oi0bIhvam8WPAfDTqY2E";

#define EXAMPLE_TRACE(...)                                      \
    do                                                          \
    {                                                           \
        HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__); \
        HAL_Printf(__VA_ARGS__);                                \
        HAL_Printf("\033[0m\r\n");                              \
    } while (0)
#define EXAMPLE_MASTER_DEVID (0)
#define EXAMPLE_YIELD_TIMEOUT_MS (200)

typedef struct
{
    int master_devid;
    int cloud_connected;
    int master_initialized;
} user_example_ctx_t;
static user_example_ctx_t g_user_example_ctx;
iotx_linkkit_dev_meta_info_t master_meta_info;

/**
 * @brief 解析所有属性设置的值
 * @param request 指向属性设置请求payload的指针
 * @param request_len 属性设置请求的payload长度
 * @return 解析成功: 0, 解析失败: <0
 */
int32_t app_parse_property(const char *request, uint32_t request_len)
{
    cJSON *structcnt = NULL;

    cJSON *req = cJSON_Parse(request);
    if (req == NULL || !cJSON_IsObject(req))
    {
        return STATE_DEV_MODEL_WRONG_JSON_FORMAT;
    }

    structcnt = cJSON_GetObjectItem(req, "structCnt");
    if (structcnt != NULL && cJSON_IsObject(structcnt))
    {
        /* process property structCnt here */

        EXAMPLE_TRACE("struct property id: structCnt");
    }

    cJSON_Delete(req);
    return 0;
}

/** 建连成功事件回调 */
static int user_connected_event_handler(void)
{
    void *callback;
    EXAMPLE_TRACE("Cloud Connected");
    g_user_example_ctx.cloud_connected = 1;
    callback = evs_service_callback(EVS_CONNECT_SUCC);
    if (callback)
    {
        ((int (*)(void))callback)();
    }
    return 0;
}

/** 断开连接事件回调 */
static int user_disconnected_event_handler(void)
{
    void *callback;
    EXAMPLE_TRACE("Cloud Disconnected");
    g_user_example_ctx.cloud_connected = 0;
    callback = evs_service_callback(EVS_DISCONNECTED);
    if (callback)
    {
        ((int (*)(void))callback)();
    }
    return 0;
}

/* 设备初始化成功事件回调 */
static int user_initialized(const int devid)
{
    EXAMPLE_TRACE("Device Initialized");
    g_user_example_ctx.master_initialized = 1;

    return 0;
}

/** 事件回调：接收到云端回复属性上报应答 **/
static int user_report_reply_event_handler(const int devid, const int msgid, const int code, const char *reply,
                                           const int reply_len)
{
    void *callback;
    EXAMPLE_TRACE("Message Post Reply Received, Message ID: %d, Code: %d, Reply: %.*s", msgid, code,
                  reply_len,
                  (reply == NULL) ? ("NULL") : (reply));
    callback = evs_service_callback(EVS_REPORT_REPLY);
    if (callback)
    {
        ((int (*)(const int msgid, const int code, const char *reply,
                  const int reply_len))callback)(msgid, code, reply, reply_len);
    }
    return 0;
}

/** 事件回调：接收到云端回复的事件上报应答 **/
static int user_trigger_event_reply_event_handler(const int devid, const int msgid, const int code, const char *eventid,
                                                  const int eventid_len, const char *message, const int message_len)
{
    void *callback;
    EXAMPLE_TRACE("Trigger Event Reply Received, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s",
                  msgid, code,
                  eventid_len,
                  eventid, message_len, message);

    callback = evs_service_callback(EVS_TRIGGER_EVENT_REPLY);
    if (callback)
    {
        ((int (*)(const int msgid, const int code, const char *eventid,
                  const int eventid_len, const char *message, const int message_len))callback)(msgid, code, eventid, eventid_len, message, message_len);
    }
    return 0;
}

/** 事件回调：接收到云端下发的属性设置 **/
static int user_property_set_event_handler(const int devid, const char *request, const int request_len)
{
    int res = 0;
    EXAMPLE_TRACE("Property Set Received, Request: %s", request);

    app_parse_property(request, request_len);

    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)request, request_len);
    EXAMPLE_TRACE("Post Property return: %d", res);

    return 0;
}

/** 事件回调：接收到云端下发的服务请求 **/
static int user_service_request_event_handler(const int devid, const char *serviceid, const int serviceid_len,
                                              const char *request, const int request_len,
                                              char **response, int *response_len)
{
    int add_result = 0;
    cJSON *root = NULL, *item_number_a = NULL, *item_number_b = NULL;
    const char *response_fmt = "{\"Result\": %d}";

    EXAMPLE_TRACE("Service Request Received, Service ID: %.*s, Payload: %s", serviceid_len, serviceid, request);

    /* Parse Root */
    root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }

    if (strlen("Operation_Service") == serviceid_len && memcmp("Operation_Service", serviceid, serviceid_len) == 0)
    {
        /* Parse NumberA */
        item_number_a = cJSON_GetObjectItem(root, "NumberA");
        if (item_number_a == NULL || !cJSON_IsNumber(item_number_a))
        {
            cJSON_Delete(root);
            return -1;
        }
        EXAMPLE_TRACE("NumberA = %d", item_number_a->valueint);

        /* Parse NumberB */
        item_number_b = cJSON_GetObjectItem(root, "NumberB");
        if (item_number_b == NULL || !cJSON_IsNumber(item_number_b))
        {
            cJSON_Delete(root);
            return -1;
        }
        EXAMPLE_TRACE("NumberB = %d", item_number_b->valueint);

        add_result = item_number_a->valueint + item_number_b->valueint;

        //protocol_service_callback(EVS_GATA_LOCK_SRV);
        //protocol_service_callback(EVS_CHARGE_START_SRV);

        /* Send Service Response To Cloud */
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        if (*response == NULL)
        {
            EXAMPLE_TRACE("Memory Not Enough");
            return -1;
        }
        memset(*response, 0, *response_len);
        HAL_Snprintf(*response, *response_len, response_fmt, add_result);
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    return 0;
}

/** 事件回调：接收到云端回复的时间戳 **/
static int user_timestamp_reply_event_handler(const char *timestamp)
{
    EXAMPLE_TRACE("Current Timestamp: %s", timestamp);

    return 0;
}

/** FOTA事件回调处理 **/
static int user_fota_event_handler(int type, const char *version)
{
    char buffer[128] = {0};
    int buffer_length = 128;

    /* 0 - new firmware exist, query the new firmware */
    if (type == 0)
    {
        EXAMPLE_TRACE("New Firmware Version: %s", version);

        IOT_Linkkit_Query(EXAMPLE_MASTER_DEVID, ITM_MSG_QUERY_FOTA_DATA, (unsigned char *)buffer, buffer_length);
    }

    return 0;
}

/** 事件回调：接收到云端错误信息 **/
static int user_cloud_error_handler(const int code, const char *data, const char *detail)
{
    EXAMPLE_TRACE("code =%d ,data=%s, detail=%s", code, data, detail);
    return 0;
}

/** 事件回调：通过动态注册获取到DeviceSecret **/
static int dynreg_device_secret(const char *device_secret)
{
    EXAMPLE_TRACE("device secret: %s", device_secret);
    return 0;
}

/** 事件回调: SDK内部运行状态打印 **/
static int user_sdk_state_dump(int ev, const char *msg)
{
    void *callback;
    printf("received state event, -0x%04x(%s)\n", -ev, msg);
    callback = evs_service_callback(EVS_STATE_EVERYTHING);
    if (callback)
    {
        ((int (*)(int ev, const char *msg))callback)(ev, msg);
    }
    return 0;
}

void user_post_property(void)
{
    static int cnt = 0;
    int res = 0;

    char property_payload[30] = {0};
    HAL_Snprintf(property_payload, sizeof(property_payload), "{\"Counter\": %d}", cnt++);

    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)property_payload, strlen(property_payload));

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
}

void user_post_event(void)
{
    int res = 0;
    char *event_id = "HardwareError";
    char *event_payload = "{\"ErrorCode\": 0}";

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, event_id, strlen(event_id),
                                   event_payload, strlen(event_payload));
    EXAMPLE_TRACE("Post Event Message ID: %d", res);
}

/*
函数名称 int evs_linkkit_new(const int evs_is_ready)
函数功能：当设备就绪后（可以读取到设备的设备证书信息和设备注册码），创建于阿里云平台通信的LINKKIT套件
输入参数：evs_is_ready 
1：设备准备就绪   
0: 设备未准备就绪
返回值:
0                                 设备执行成功
EVS_IS_NOT_READY           设备未准备就绪
EVS_GET_REG_CODE_FAULT     获取设备注册码失败
EVS_SET_CERT_FAULT         设置设备证书失败 
*/
int evs_linkkit_new(const int evs_is_ready)
{

    //iotx_linkkit_dev_meta_info_t master_meta_info;
    int dynamic_register = 0, post_reply_need = 0;
    memset(&g_user_example_ctx, 0, sizeof(user_example_ctx_t));

#ifdef ATM_ENABLED
    if (IOT_ATM_Init() < 0)
    {
        EXAMPLE_TRACE("IOT_ATM_Init failed!\n");
        return -1;
    }
#endif
    /*
    //如果设备没有就绪直接返回
    if(evs_is_ready == 0)
    {
        return EVS_IS_NOT_READY;
    }
    //获取设备证书
    if(evs_get_cert()==0)
    {
        //拷贝三元组到SDK
        memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
        memcpy(master_meta_info.product_key, g_product_key, strlen(g_product_key));
        memcpy(master_meta_info.product_secret, g_product_secret, strlen(g_product_secret));
        memcpy(master_meta_info.device_name, g_device_name, strlen(g_device_name));
        memcpy(master_meta_info.device_secret, g_device_secret, strlen(g_device_secret));
    }
    else
    {
        //获取设备注册码进行动态注册
        if(evs_get_reg_code()==0)
        {
            //1.去平台进行注册，得到证书
            //………………
            //2.设置设备证书
            if(evs_set_cert()!=0)
            {
                return EVS_SET_CERT_FAULT;
            }
        }
        else
        {
            return EVS_GET_REG_CODE_FAULT;
        }
        
    }
*/
    memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
    memcpy(master_meta_info.product_key, g_product_key, strlen(g_product_key));
    memcpy(master_meta_info.product_secret, g_product_secret, strlen(g_product_secret));
    memcpy(master_meta_info.device_name, g_device_name, strlen(g_device_name));
    memcpy(master_meta_info.device_secret, g_device_secret, strlen(g_device_secret));

    IOT_SetLogLevel(IOT_LOG_DEBUG);

    /* 注册回调函数 */
    IOT_RegisterCallback(ITE_STATE_EVERYTHING, user_sdk_state_dump);
    IOT_RegisterCallback(ITE_CONNECT_SUCC, user_connected_event_handler);
    IOT_RegisterCallback(ITE_DISCONNECTED, user_disconnected_event_handler);
    IOT_RegisterCallback(ITE_SERVICE_REQUEST, user_service_request_event_handler);
    IOT_RegisterCallback(ITE_PROPERTY_SET, user_property_set_event_handler);
    IOT_RegisterCallback(ITE_REPORT_REPLY, user_report_reply_event_handler);
    IOT_RegisterCallback(ITE_TRIGGER_EVENT_REPLY, user_trigger_event_reply_event_handler);
    IOT_RegisterCallback(ITE_TIMESTAMP_REPLY, user_timestamp_reply_event_handler);
    IOT_RegisterCallback(ITE_INITIALIZE_COMPLETED, user_initialized);
    IOT_RegisterCallback(ITE_FOTA, user_fota_event_handler);
    IOT_RegisterCallback(ITE_CLOUD_ERROR, user_cloud_error_handler);
    IOT_RegisterCallback(ITE_DYNREG_DEVICE_SECRET, dynreg_device_secret);

    /* 选择上线方式（是否使用动态注册） */
    dynamic_register = 0;
    IOT_Ioctl(IOTX_IOCTL_SET_DYNAMIC_REGISTER, (void *)&dynamic_register);

    /* 是否需用属性、事件上报(设置)应答 */
    post_reply_need = 1;
    IOT_Ioctl(IOTX_IOCTL_RECV_EVENT_REPLY, (void *)&post_reply_need);

    return 0;
}
int evs_linkkit_free()
{
    IOT_Linkkit_Close(g_user_example_ctx.master_devid);
    IOT_SetLogLevel(IOT_LOG_NONE);
    return 0;
}

/*
函数名称 int evs_mainloop()
输入参数：无
返回值:
EVS_LINKKIT_OPEN_FAULT           设备linkkit打开失败
EVS_LINKKIT_OPEN_WAIT            设备linkkit打开重试等待
EVS_LINKKIT_CONNECT_FAULT        设备linkkit连接失败  
EVS_LINKKIT_CONNECT_WAIT         设备linkkit连接重试等待  
*/
int evs_mainloop()
{

    static int main_loop_step = 0;
    static int evs_linkkit_open_cnt = 0;
    static int evs_linkkit_connect_cnt = 0;
    static int cnt = 0;
    int res = 0;
    switch (main_loop_step)
    {
    case EVS_LINKKIT_OPEN:
        if ((evs_linkkit_open_cnt % 200) == 0)
        {
            g_user_example_ctx.master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
            if (g_user_example_ctx.master_devid >= 0)
            {
                main_loop_step++;
                evs_linkkit_open_cnt = 0;
            }
            else
            {
                EXAMPLE_TRACE("IOT_Linkkit_Open failed! retry after %d ms\n", 2000);
                return EVS_LINKKIT_OPEN_FAULT;
            }
        }
        else
        {
            evs_linkkit_open_cnt++;
            return EVS_LINKKIT_OPEN_WAIT;
        }
    case EVS_LINKKIT_CONNECT:
        if ((evs_linkkit_connect_cnt % 500) == 0)
        {
            res = IOT_Linkkit_Connect(g_user_example_ctx.master_devid);
            if (res >= 0)
            {
                main_loop_step++;
                evs_linkkit_connect_cnt = 0;
            }
            else
            {
                EXAMPLE_TRACE("IOT_Linkkit_Connect failed! retry after %d ms\n", 5000);
                return EVS_LINKKIT_CONNECT_FAULT;
            }
        }
        else
        {
            evs_linkkit_connect_cnt++;
            return EVS_LINKKIT_CONNECT_WAIT;
        }
    case EVS_LINKKIT_POLL:
        IOT_Linkkit_Yield(EXAMPLE_YIELD_TIMEOUT_MS);
#if 0
        /* Post Proprety Example */
        if ((cnt % 200) == 0) {
            user_post_property(); 
        }

        /* Post Event Example */
        if ((cnt % 100) == 0) {
            user_post_event(); 
        }
        cnt++;
#endif
        break;
    default:
        break;
    }
}

/*服务回调函数*/
void protocol_service_callback(evs_service_type_t type)
{

    void *callback;
    int output1 = 0, output2 = 0;
    switch (type)
    {
    case EVS_GATA_LOCK_SRV /* constant-expression */:
        /* code */
        callback = evs_service_callback(EVS_GATA_LOCK_SRV);
        if (callback)
        {
            ((int (*)(const int, int *))callback)(5, &output1);
        }
        printf("evs_service_callback EVS_GATA_LOCK_SRV %d\n", output1);
        break;
    case EVS_CHARGE_START_SRV /* constant-expression */:
        /* code */
        callback = evs_service_callback(EVS_GATA_LOCK_SRV);
        if (callback)
        {
            ((int (*)(const int, int *))callback)(10, &output2);
        }
        printf("evs_service_callback EVS_CHARGE_START_SRV %d\n", output2);
        break;

    default:
        break;
    }
}

/**
 * @brief Send pile event data to SDK.
 *---
 * @param [in] event_type: @n the event you want to send.
 * @param [in] param: @n the event data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int8_t evs_send_event(evs_cmd_event_enum event_type, void *param)
{
    switch (event_type)
    {
    case evs_send_event_fireware_info:
        user_post_event();
        break;
    case evs_send_event_ask_feeModel:
        /* code */
        break;
    case evs_send_event_startCharge:
        /* code */
        break;
    case evs_send_event_startResult:
        /* code */
        break;
    case evs_send_event_stopCharge:
        /* code */
        break;
    case evs_send_event_tradeInfo:
        /* code */
        break;
    case evs_send_event_alarm:
        /* code */
        break;
    case evs_send_event_acPile_change:
        /* code */
        break;
    case evs_send_event_dcPile_change:
        /* code */
        break;
    case evs_send_event_groundLock_change:
        /* code */
        break;
    case evs_send_event_gateLock_change:
        /* code */
        break;

    default:
        break;
    }
}

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
int8_t evs_send_property(evs_cmd_property_enum property_type, void *param)
{
    switch (property_type)
    {
    case evs_send_property_dcPile:
        user_post_property();
        break;
    case evs_send_property_acPile:
        user_post_property();
        break;
    case evs_send_property_ac_work:
        user_post_property();
        break;
    case evs_send_property_ac_nonwork:
        user_post_property();
        break;
    case evs_send_property_BMS:
        user_post_property();
        break;
    case evs_send_property_dc_input_meter:
        user_post_property();
        break;
    case evs_send_property_meter:
        user_post_property();
        break;
    case evs_send_property_dc_work:
        user_post_property();
        break;
    case evs_send_property_dc_nonwork:
        user_post_property();
        break;
    default:
        break;
    }
}