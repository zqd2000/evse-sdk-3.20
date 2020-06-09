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

#define cJSON_AddNumberToArray(array, n) cJSON_AddItemToArray(array, cJSON_CreateNumber(n))
#define cJSON_AddStringToArray(array, s) cJSON_AddItemToArray(array, cJSON_CreateString(s))

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
    void *callback;
    cJSON *root = NULL;
    const char *response_fmt = "{\"Result\": %d}";

    EXAMPLE_TRACE("Service Request Received, Service ID: %.*s, Payload: %s", serviceid_len, serviceid, request);

    /* Parse Root */
    root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        EXAMPLE_TRACE("JSON Parse Error");
        return -1;
    }
    if (strlen("feeModelUpdateSrv") == serviceid_len && memcmp("feeModelUpdateSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_issue_feeModel service_feeModel_data;
        evs_service_feedback_feeModel service_feedback_feeModel_data;
        int i = 0;
        /* Parse json */

        cJSON *item_eleModelId = cJSON_GetObjectItem(root, "eleModelId");
        if (item_eleModelId == NULL || !cJSON_IsString(item_eleModelId))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *eleModelId = item_eleModelId->string;
        memcpy(service_feeModel_data.eleModelId, eleModelId, strlen(eleModelId));
        /****服务费模型id*****/
        cJSON *item_serModelId = cJSON_GetObjectItem(root, "serModelId");
        if (item_serModelId == NULL || !cJSON_IsString(item_serModelId))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *serModelId = item_serModelId->string;
        memcpy(service_feeModel_data.eleModelId, serModelId, strlen(serModelId));

        cJSON *item_eleTimeNum = cJSON_GetObjectItem(root, "eleTimeNum");
        if (item_eleTimeNum == NULL || !cJSON_IsNumber(item_eleTimeNum))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_feeModel_data.eleTimeNum = item_eleTimeNum->valueint;

        cJSON *item_serTimeNum = cJSON_GetObjectItem(root, "serTimeNum");
        if (item_serTimeNum == NULL || !cJSON_IsNumber(item_serTimeNum))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_feeModel_data.serTimeNum = item_serTimeNum->valueint;

        cJSON *item_eleTimeSeg = cJSON_GetObjectItem(root, "eleTimeSeg");
        if (item_eleTimeSeg == NULL || !cJSON_IsArray(item_eleTimeSeg))
        {
            cJSON_Delete(root);
            return -1;
        }
        cJSON *item_arrayData;
        for (i = 0; i < service_feeModel_data.eleTimeNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_eleTimeSeg, i);
            memcpy(service_feeModel_data.eleTimeSeg[i], item_arrayData->string, strlen(item_arrayData->string));
        }
        cJSON *item_serTimeSeg = cJSON_GetObjectItem(root, "serTimeSeg");
        if (item_serTimeSeg == NULL || !cJSON_IsArray(item_serTimeSeg))
        {
            cJSON_Delete(root);
            return -1;
        }
        for (i = 0; i < service_feeModel_data.serTimeNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_serTimeSeg, i);
            memcpy(service_feeModel_data.serTimeSeg[i], item_arrayData->string, strlen(item_arrayData->string));
        }

        cJSON *item_eleSegFlag = cJSON_GetObjectItem(root, "eleSegFlag");
        if (item_eleSegFlag == NULL || !cJSON_IsArray(item_eleSegFlag))
        {
            cJSON_Delete(root);
            return -1;
        }
        for (i = 0; i < service_feeModel_data.eleTimeNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_eleSegFlag, i);
            service_feeModel_data.eleSegFlag[i] = item_arrayData->valueint;
        }
        cJSON *item_serSegFlag = cJSON_GetObjectItem(root, "serSegFlag");
        if (item_serSegFlag == NULL || !cJSON_IsArray(item_serSegFlag))
        {
            cJSON_Delete(root);
            return -1;
        }
        for (i = 0; i < service_feeModel_data.serTimeNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_serSegFlag, i);
            service_feeModel_data.serSegFlag[i] = item_arrayData->valueint;
        }

        cJSON *item_chargeFee = cJSON_GetObjectItem(root, "chargeFee");
        if (item_chargeFee == NULL || !cJSON_IsArray(item_chargeFee))
        {
            cJSON_Delete(root);
            return -1;
        }
        for (i = 0; i < 4; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_chargeFee, i);
            service_feeModel_data.chargeFee[i] = item_arrayData->valueint;
        }
        cJSON *item_serviceFee = cJSON_GetObjectItem(root, "serviceFee");
        if (item_serviceFee == NULL || !cJSON_IsArray(item_serviceFee))
        {
            cJSON_Delete(root);
            return -1;
        }
        for (i = 0; i < 4; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_serviceFee, i);
            service_feeModel_data.serviceFee[i] = item_arrayData->valueint;
        }
        callback = evs_service_callback(EVS_FEE_MODEL_UPDATA_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_issue_feeModel *request, evs_service_feedback_feeModel *feedcak))callback)(&service_feeModel_data, &service_feedback_feeModel_data);
            //((int (*)(const evs_service_query_log request ,evs_service_feedback_query_log *response)))callback)(request, &response);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddStringToObject(response_root, "modelId", service_feedback_feeModel_data.eleModelId);
        cJSON_AddStringToObject(response_root, "modelId", service_feedback_feeModel_data.serModelId);
        cJSON_AddNumberToObject(response_root, "time", service_feedback_feeModel_data.res);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);

        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }
    if (strlen("startChargeSrv") == serviceid_len && memcmp("startChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_startCharge service_charge_data;
        evs_service_feedback_startCharge service_feedback_startCharge_data;
        uint8_t *tradeNo;
        /* Parse json */
        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.gunNo = item_gunNo->valueint;

        cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
        if (item_preTradeNo == NULL || !cJSON_IsString(item_preTradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        tradeNo = item_preTradeNo->string;
        memcpy(service_charge_data.preTradeNo, tradeNo, strlen(tradeNo));

        cJSON *item_startType = cJSON_GetObjectItem(root, "startType");
        if (item_startType == NULL || !cJSON_IsNumber(item_startType))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.startType = item_startType->valueint;

        cJSON *item_chargeMode = cJSON_GetObjectItem(root, "chargeMode");
        if (item_chargeMode == NULL || !cJSON_IsNumber(item_chargeMode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.chargeMode = item_chargeMode->valueint;

        cJSON *item_limitData = cJSON_GetObjectItem(root, "limitData");
        if (item_limitData == NULL || !cJSON_IsNumber(item_limitData))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.limitData = item_limitData->valueint;

        cJSON *item_stopCode = cJSON_GetObjectItem(root, "stopCode");
        if (item_stopCode == NULL || !cJSON_IsNumber(item_stopCode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.stopCode = item_stopCode->valueint;

        cJSON *item_startMode = cJSON_GetObjectItem(root, "startMode");
        if (item_startMode == NULL || !cJSON_IsNumber(item_startMode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.startMode = item_startMode->valueint;

        cJSON *item_auxiVolt = cJSON_GetObjectItem(root, "auxiVolt");
        if (item_auxiVolt == NULL || !cJSON_IsNumber(item_auxiVolt))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.auxiVolt = item_auxiVolt->valueint;

        cJSON *item_insertGunTime = cJSON_GetObjectItem(root, "insertGunTime");
        if (item_insertGunTime == NULL || !cJSON_IsNumber(item_insertGunTime))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_charge_data.insertGunTime = item_insertGunTime->valueint;

        callback = evs_service_callback(EVS_START_CHARGE_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_startCharge *request, evs_service_feedback_startCharge *feedcak))callback)(&service_charge_data, &service_feedback_startCharge_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddStringToObject(response_root, "preTradeNo", service_feedback_startCharge_data.preTradeNo);
        cJSON_AddStringToObject(response_root, "tradeNo", service_feedback_startCharge_data.tradeNo);
        cJSON_AddNumberToObject(response_root, "gunNo", service_feedback_startCharge_data.gunNo);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }

    if (strlen("authResultSrv") == serviceid_len && memcmp("authResultSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_authCharge service_authCharge_data;
        evs_service_feedback_authCharge service_feedback_authCharge_data;
        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.gunNo = item_gunNo->valueint;

        cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
        if (item_preTradeNo == NULL || !cJSON_IsString(item_preTradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *tradeNo = item_preTradeNo->string;
        memcpy(service_authCharge_data.preTradeNo, tradeNo, strlen(tradeNo));

        cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
        if (item_tradeNo == NULL || !cJSON_IsString(item_tradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *devTradeNo = item_tradeNo->string;
        memcpy(service_authCharge_data.tradeNo, devTradeNo, strlen(devTradeNo));

        cJSON *item_vinCode = cJSON_GetObjectItem(root, "vinCode");
        if (item_vinCode == NULL || !cJSON_IsString(item_vinCode))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *vinCode = item_vinCode->string;
        memcpy(service_authCharge_data.vinCode, vinCode, strlen(vinCode));

        cJSON *item_oppoCode = cJSON_GetObjectItem(root, "oppoCode");
        if (item_oppoCode == NULL || !cJSON_IsString(item_oppoCode))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *oppoCode = item_oppoCode->string;
        memcpy(service_authCharge_data.oppoCode, oppoCode, strlen(oppoCode));

        cJSON *item_result = cJSON_GetObjectItem(root, "result");
        if (item_result == NULL || !cJSON_IsNumber(item_result))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.result = item_result->valueint;

        cJSON *item_chargeMode = cJSON_GetObjectItem(root, "chargeMode");
        if (item_chargeMode == NULL || !cJSON_IsNumber(item_chargeMode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.chargeMode = item_chargeMode->valueint;

        cJSON *item_limitData = cJSON_GetObjectItem(root, "limitData");
        if (item_limitData == NULL || !cJSON_IsNumber(item_limitData))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.limitData = item_limitData->valueint;

        cJSON *item_stopCode = cJSON_GetObjectItem(root, "stopCode");
        if (item_stopCode == NULL || !cJSON_IsNumber(item_stopCode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.stopCode = item_stopCode->valueint;

        cJSON *item_startMode = cJSON_GetObjectItem(root, "startMode");
        if (item_startMode == NULL || !cJSON_IsNumber(item_startMode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.startMode = item_startMode->valueint;

        cJSON *item_insertGunTime = cJSON_GetObjectItem(root, "insertGunTime");
        if (item_insertGunTime == NULL || !cJSON_IsNumber(item_insertGunTime))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_authCharge_data.insertGunTime = item_insertGunTime->valueint;

        callback = evs_service_callback(EVS_AUTH_RESULT_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_authCharge *request, evs_service_feedback_authCharge *feedcak))callback)(&service_authCharge_data, &service_feedback_authCharge_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddStringToObject(response_root, "preTradeNo", service_feedback_authCharge_data.preTradeNo);
        cJSON_AddStringToObject(response_root, "tradeNo", service_feedback_authCharge_data.tradeNo);
        cJSON_AddNumberToObject(response_root, "gunNo", service_feedback_authCharge_data.gunNo);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }

    if (strlen("stopChargeSrv") == serviceid_len && memcmp("stopChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_stopCharge service_stopCharge_data;
        evs_service_feedback_stopCharge service_feedback_stopCharge_data;

        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_stopCharge_data.gunNo = item_gunNo->valueint;

        cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
        if (item_preTradeNo == NULL || !cJSON_IsString(item_preTradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *tradeNo = item_preTradeNo->string;
        memcpy(service_stopCharge_data.preTradeNo, tradeNo, strlen(tradeNo));

        cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
        if (item_tradeNo == NULL || !cJSON_IsString(item_tradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *devTradeNo = item_tradeNo->string;
        memcpy(service_stopCharge_data.tradeNo, devTradeNo, strlen(devTradeNo));

        cJSON *item_stopReason = cJSON_GetObjectItem(root, "stopReason");
        if (item_stopReason == NULL || !cJSON_IsNumber(item_stopReason))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_stopCharge_data.stopReason = item_stopReason->valueint;

        callback = evs_service_callback(EVS_STOP_CHARGE_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_stopCharge *request, evs_service_feedback_stopCharge *feedcak))callback)(&service_stopCharge_data, &service_feedback_stopCharge_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddStringToObject(response_root, "preTradeNo", service_feedback_stopCharge_data.preTradeNo);
        cJSON_AddStringToObject(response_root, "tradeNo", service_feedback_stopCharge_data.tradeNo);
        cJSON_AddNumberToObject(response_root, "gunNo", service_feedback_stopCharge_data.gunNo);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }

    if (strlen("orderCheckSrv") == serviceid_len && memcmp("orderCheckSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_confirmTrade service_confirmTrade_data;

        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_confirmTrade_data.gunNo = item_gunNo->valueint;

        cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
        if (item_preTradeNo == NULL || !cJSON_IsString(item_preTradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *tradeNo = item_preTradeNo->string;
        memcpy(service_confirmTrade_data.preTradeNo, tradeNo, strlen(tradeNo));

        cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
        if (item_tradeNo == NULL || !cJSON_IsString(item_tradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *devTradeNo = item_tradeNo->string;
        memcpy(service_confirmTrade_data.tradeNo, devTradeNo, strlen(devTradeNo));

        cJSON *item_errcode = cJSON_GetObjectItem(root, "errcode");
        if (item_errcode == NULL || !cJSON_IsNumber(item_errcode))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_confirmTrade_data.errcode = item_errcode->valueint;

        cJSON_Delete(root);
    }
    if (strlen("queDataSrv") == serviceid_len && memcmp("queDataSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_query_log service_query_log_data;
        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_query_log_data.gunNo = item_gunNo->valueint;

        cJSON *item_startDate = cJSON_GetObjectItem(root, "startDate");
        if (item_startDate == NULL || !cJSON_IsString(item_startDate))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *startDate = item_startDate->string;
        memcpy(service_query_log_data.startDate, startDate, strlen(startDate));

        cJSON *item_stopDate = cJSON_GetObjectItem(root, "stopDate");
        if (item_stopDate == NULL || !cJSON_IsString(item_stopDate))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *stopDate = item_stopDate->string;
        memcpy(service_query_log_data.stopDate, stopDate, strlen(stopDate));

        cJSON *item_askType = cJSON_GetObjectItem(root, "askType");
        if (item_askType == NULL || !cJSON_IsNumber(item_askType))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_query_log_data.askType = item_askType->valueint;
    }
    if (strlen("gateLockSrv") == serviceid_len && memcmp("gateLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_gateLock_ctrl service_gateLock_ctrl_data;
        evs_service_feedback_gateLock_ctrl service_feedback_gateLock_ctrl_data;
        cJSON *item_lockNo = cJSON_GetObjectItem(root, "lockNo");
        if (item_lockNo == NULL || !cJSON_IsNumber(item_lockNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_gateLock_ctrl_data.lockNo = item_lockNo->valueint;

        cJSON *item_ctrlFlag = cJSON_GetObjectItem(root, "ctrlFlag");
        if (item_ctrlFlag == NULL || !cJSON_IsNumber(item_ctrlFlag))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_gateLock_ctrl_data.ctrlFlag = item_ctrlFlag->valueint;

        callback = evs_service_callback(EVS_GATE_LOCK_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_gateLock_ctrl *request, evs_service_feedback_gateLock_ctrl *feedcak))callback)(&service_gateLock_ctrl_data, &service_feedback_gateLock_ctrl_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddNumberToObject(response_root, "lockNo", service_feedback_gateLock_ctrl_data.lockNo);
        cJSON_AddNumberToObject(response_root, "result", service_feedback_gateLock_ctrl_data.result);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }
    if (strlen("groundLockSrv") == serviceid_len && memcmp("groundLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_groundLock_ctrl service_groundLock_ctrl_data;
        evs_service_feedback_groundLock_ctrl service_feedback_groundLock_ctrl_data;

        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_groundLock_ctrl_data.gunNo = item_gunNo->valueint;

        cJSON *item_ctrlFlag = cJSON_GetObjectItem(root, "ctrlFlag");
        if (item_ctrlFlag == NULL || !cJSON_IsNumber(item_ctrlFlag))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_groundLock_ctrl_data.ctrlFlag = item_ctrlFlag->valueint;

        callback = evs_service_callback(EVS_GROUND_LOCK_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_groundLock_ctrl *request, evs_service_feedback_groundLock_ctrl *feedcak))callback)(&service_groundLock_ctrl_data, &service_feedback_groundLock_ctrl_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddNumberToObject(response_root, "gunNo", service_feedback_groundLock_ctrl_data.gunNo);
        cJSON_AddNumberToObject(response_root, "reason", service_feedback_groundLock_ctrl_data.reason);
        cJSON_AddNumberToObject(response_root, "result", service_feedback_groundLock_ctrl_data.result);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }
    if (strlen("ctrlLockSrv") == serviceid_len && memcmp("ctrlLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_lockCtrl service_lockCtrl_data;
        evs_service_feedback_lockCtrl service_feedback_lockCtrl_data;

        cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
        if (item_gunNo == NULL || !cJSON_IsNumber(item_gunNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_lockCtrl_data.gunNo = item_gunNo->valueint;

        cJSON *item_lockParam = cJSON_GetObjectItem(root, "lockParam");
        if (item_lockParam == NULL || !cJSON_IsNumber(item_lockParam))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_lockCtrl_data.lockParam = item_lockParam->valueint;

        callback = evs_service_callback(EVS_CTRL_LOCK_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_lockCtrl *request, evs_service_feedback_lockCtrl *feedcak))callback)(&service_lockCtrl_data, &service_feedback_lockCtrl_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddNumberToObject(response_root, "gunNo", service_feedback_lockCtrl_data.gunNo);
        cJSON_AddNumberToObject(response_root, "lockStatus", service_feedback_lockCtrl_data.lockStatus);
        cJSON_AddNumberToObject(response_root, "resCode", service_feedback_lockCtrl_data.resCode);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }
    if (strlen("devMaintainSrv") == serviceid_len && memcmp("devMaintainSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_devCtrl service_devCtrl_data;
        evs_service_feedback_devCtrl service_feedback_devCtrl_data;

        cJSON *item_ctrlType = cJSON_GetObjectItem(root, "ctrlType");
        if (item_ctrlType == NULL || !cJSON_IsNumber(item_ctrlType))
        {
            cJSON_Delete(root);
            return -1;
        }
        service_devCtrl_data.ctrlType = item_ctrlType->valueint;

        callback = evs_service_callback(EVS_DEV_MAINTAIN_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_devCtrl *request, evs_service_feedback_devCtrl *feedcak))callback)(&service_devCtrl_data, &service_feedback_devCtrl_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddNumberToObject(response_root, "ctrlType", service_feedback_devCtrl_data.ctrlType);
        cJSON_AddNumberToObject(response_root, "reason", service_feedback_devCtrl_data.reason);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }
    if (strlen("orderlyChargeSrv") == serviceid_len && memcmp("orderlyChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_orderCharge service_oderCharge_data;
        evs_service_feedback_orderCharge service_feedback_oderCharge_data;
        cJSON *item_arrayData;
        uint8_t i = 0, arrayNum;
        cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
        if (item_preTradeNo == NULL || !cJSON_IsString(item_preTradeNo))
        {
            cJSON_Delete(root);
            return -1;
        }
        uint8_t *tradeNo = item_preTradeNo->string;
        memcpy(service_oderCharge_data.preTradeNo, tradeNo, strlen(tradeNo));

        cJSON *item_validTime = cJSON_GetObjectItem(root, "validTime");
        if (item_validTime == NULL || !cJSON_IsArray(item_validTime))
        {
            cJSON_Delete(root);
            return -1;
        }
        arrayNum = cJSON_GetArraySize(item_validTime);
        for (i = 0; i < arrayNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_validTime, i);
            memcpy(service_oderCharge_data.validTime[i], item_arrayData->string, strlen(item_arrayData->string));
        }

        cJSON *item_kw = cJSON_GetObjectItem(root, "kw");
        if (item_kw == NULL || !cJSON_IsArray(item_kw))
        {
            cJSON_Delete(root);
            return -1;
        }
        arrayNum = cJSON_GetArraySize(item_kw);
        for (i = 0; i < arrayNum; i++)
        {
            item_arrayData = cJSON_GetArrayItem(item_kw, i);
            service_oderCharge_data.kw[i] = item_arrayData->valueint;
        }

        callback = evs_service_callback(EVS_ORDERLY_CHARGE_SRV);
        if (callback)
        {
            ((int (*)(const evs_service_orderCharge *request, evs_service_feedback_orderCharge *feedcak))callback)(&service_oderCharge_data, &service_feedback_oderCharge_data);
        }
        cJSON *response_root = cJSON_CreateObject();
        cJSON_AddStringToObject(response_root, "tradeNo", service_feedback_oderCharge_data.tradeNo);
        cJSON_AddNumberToObject(response_root, "reason", service_feedback_oderCharge_data.reason);
        cJSON_AddNumberToObject(response_root, "result", service_feedback_oderCharge_data.result);

        *response = cJSON_PrintUnformatted(response_root);
        *response_len = strlen(*response);
        cJSON_Delete(root);
        cJSON_Delete(response_root);
    }

    if (*response == NULL)
    {
        *response_len = strlen(response_fmt) + 10 + 1;
        *response = (char *)HAL_Malloc(*response_len);
        memset(*response, 0, *response_len);
        HAL_Snprintf(*response, *response_len, response_fmt, add_result);
        *response_len = strlen(*response);
    }

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

static int32_t send_property_dcPile(evs_property_dcPile *data)
{
    uint32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcDeRealIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "netType", data->netType);
    cJSON_AddNumberToObject(body, "sigVal", data->sigVal);

    cJSON_AddNumberToObject(body, "netID", data->netID);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    cJSON_AddNumberToObject(body, "caseTemp", data->caseTemp);
    cJSON_AddNumberToObject(body, "inletTemp", data->inletTemp);
    cJSON_AddNumberToObject(body, "outletTemp", data->outletTemp);

    cJSON_AddStringToObject(body, "modelId", data->modelId);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_property_acPile(evs_property_acPile *data)
{
    uint32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acDeRealIty", body = cJSON_CreateObject());

    cJSON_AddNumberToObject(body, "netType", data->netType);
    cJSON_AddNumberToObject(body, "sigVal", data->sigVal);
    cJSON_AddNumberToObject(body, "netID", data->netID);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    cJSON_AddNumberToObject(body, "caseTemp", data->caseTemp);

    cJSON_AddStringToObject(body, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(body, "serModelId", data->serModelId);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//交流非充电过程实时监测属性
static int32_t send_property_ac_nonwork(evs_property_ac_nonWork *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acGunIdleIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(body, "workStatus", data->workStatus);

    cJSON_AddNumberToObject(body, "conStatus", data->conStatus);
    cJSON_AddNumberToObject(body, "eLockStatus", data->eLockStatus);
    cJSON_AddNumberToObject(body, "gunTemp", data->gunTemp);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//交流充电过程实时监测属性
static int32_t send_property_ac_work(evs_property_ac_work *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acGunRunIty", body = cJSON_CreateObject());

    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(body, "workStatus", data->workStatus);
    cJSON_AddNumberToObject(body, "conStatus", data->conStatus);
    cJSON_AddNumberToObject(body, "eLockStatus", data->eLockStatus);
    cJSON_AddNumberToObject(body, "outRelayStatus", data->outRelayStatus);
    cJSON_AddNumberToObject(body, "gunTemp", data->gunTemp);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    cJSON_AddStringToObject(body, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(body, "tradeNo", data->tradeNo);

    cJSON_AddNumberToObject(body, "realPower", data->realPower);
    cJSON_AddNumberToObject(body, "chgTime", data->chgTime);

    cJSON_AddNumberToObject(body, "totalElect", data->totalElect);
    cJSON_AddNumberToObject(body, "sharpElect", data->sharpElect);
    cJSON_AddNumberToObject(body, "peakElect", data->peakElect);
    cJSON_AddNumberToObject(body, "flatElect", data->flatElect);
    cJSON_AddNumberToObject(body, "valleyElect", data->valleyElect);

    cJSON_AddNumberToObject(body, "totalCost", data->totalCost);
    cJSON_AddNumberToObject(body, "totalPowerCost", data->totalPowerCost);
    cJSON_AddNumberToObject(body, "totalServCost", data->totalServCost);
    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电过程BMS实时监测属性
static int32_t send_property_bms(evs_property_BMS *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcBmsRunIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddStringToObject(body, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(body, "tradeNo", data->tradeNo);

    cJSON_AddNumberToObject(body, "socVal", data->socVal);
    cJSON_AddNumberToObject(body, "BMSVer", data->BMSVer);

    cJSON_AddNumberToObject(body, "BMSMaxVol", data->BMSMaxVol);
    cJSON_AddNumberToObject(body, "batType", data->batType);
    cJSON_AddNumberToObject(body, "batRatedCap", data->batRatedCap);

    cJSON_AddNumberToObject(body, "batRatedTotalVol", data->batRatedTotalVol);
    cJSON_AddNumberToObject(body, "singlBatMaxAllowVol", data->singlBatMaxAllowVol);

    cJSON_AddNumberToObject(body, "maxAllowCur", data->maxAllowCur);
    cJSON_AddNumberToObject(body, "battotalEnergy", data->battotalEnergy);

    cJSON_AddNumberToObject(body, "maxVol", data->maxVol);
    cJSON_AddNumberToObject(body, "maxTemp", data->maxTemp);
    cJSON_AddNumberToObject(body, "batCurVol", data->batCurVol);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流非充电过程实时监测属性
static int32_t send_property_dc_nonwork(evs_property_dc_nonWork *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcGunIdleIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(body, "workStatus", data->workStatus);

    cJSON_AddNumberToObject(body, "gunStatus", data->gunStatus);
    cJSON_AddNumberToObject(body, "eLockStatus", data->eLockStatus);
    cJSON_AddNumberToObject(body, "DCK1Status", data->DCK1Status);
    cJSON_AddNumberToObject(body, "DCK2Status", data->DCK2Status);

    cJSON_AddNumberToObject(body, "DCPlusFuseStatus", data->DCPlusFuseStatus);
    cJSON_AddNumberToObject(body, "DCMinusFuseStatus", data->DCMinusFuseStatus);

    cJSON_AddNumberToObject(body, "gunTemp1", data->conTemp1);
    cJSON_AddNumberToObject(body, "gunTemp2", data->conTemp2);

    cJSON_AddNumberToObject(body, "dcVol", data->dcVol);
    cJSON_AddNumberToObject(body, "dcCur", data->dcCur);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电过程实时监测属性
static int32_t send_property_dc_work(evs_property_dc_work *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcGunRunIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(body, "workStatus", data->workStatus);

    cJSON_AddNumberToObject(body, "gunStatus", data->gunStatus);
    cJSON_AddNumberToObject(body, "eLockStatus", data->eLockStatus);
    cJSON_AddNumberToObject(body, "DCK1Status", data->DCK1Status);
    cJSON_AddNumberToObject(body, "DCK2Status", data->DCK2Status);

    cJSON_AddNumberToObject(body, "DCPlusFuseStatus", data->DCPlusFuseStatus);
    cJSON_AddNumberToObject(body, "DCMinusFuseStatus", data->DCMinusFuseStatus);

    cJSON_AddNumberToObject(body, "conTemp1", data->conTemp1);
    cJSON_AddNumberToObject(body, "conTemp2", data->conTemp2);

    cJSON_AddNumberToObject(body, "dcVol", data->dcVol);
    cJSON_AddNumberToObject(body, "dcCur", data->dcCur);
    cJSON_AddStringToObject(body, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(body, "tradeNo", data->tradeNo);

    cJSON_AddNumberToObject(body, "chgType", data->chgType);

    cJSON_AddNumberToObject(body, "realPower", data->realPower);
    cJSON_AddNumberToObject(body, "chgTime", data->chgTime);
    cJSON_AddNumberToObject(body, "socVal", data->socVal);

    cJSON_AddNumberToObject(body, "needVol", data->needVol);

    cJSON_AddNumberToObject(body, "needCur", data->needCur);
    cJSON_AddNumberToObject(body, "chargeMode", data->chargeMode);
    cJSON_AddNumberToObject(body, "bmsVol", data->bmsVol);

    cJSON_AddNumberToObject(body, "bmsCur", data->bmsCur);
    cJSON_AddNumberToObject(body, "SingleMHV", data->SingleMHV);
    cJSON_AddNumberToObject(body, "remainT", data->remainT);

    cJSON_AddNumberToObject(body, "MHTemp", data->MHTemp);
    cJSON_AddNumberToObject(body, "MLTemp", data->MLTemp);

    cJSON_AddNumberToObject(body, "totalElect", data->totalElect);
    cJSON_AddNumberToObject(body, "sharpElect", data->sharpElect);
    cJSON_AddNumberToObject(body, "peakElect", data->peakElect);
    cJSON_AddNumberToObject(body, "flatElect", data->flatElect);
    cJSON_AddNumberToObject(body, "valleyElect", data->valleyElect);

    cJSON_AddNumberToObject(body, "totalCost", data->totalCost);
    cJSON_AddNumberToObject(body, "totalPowerCost", data->totalPowerCost);
    cJSON_AddNumberToObject(body, "totalServCost", data->totalServCost);
    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电设备交流输入电表底值监测属性表
static int32_t send_property_dc_input_meter(evs_property_dc_input_meter *data)
{
    int32_t res = 0;
    uint8_t *payload, meterAddr[13] = {0}, meter[6] = {0};
    cJSON *root, *body, *inMeterArray, *outMeterArray;
    uint8_t i = 0, j = 0, k = 0;
    uint8_t meterCnt = 0;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcSysMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddStringToObject(body, "acqTime", data->acqTime);
    cJSON_AddStringToObject(body, "mailAddr", data->mailAddr);
    cJSON_AddStringToObject(body, "meterNo", data->meterNo);
    cJSON_AddStringToObject(body, "assetID", data->assetID);
    cJSON_AddStringToObject(body, "sumMeter", data->sumMeter);
    cJSON_AddStringToObject(body, "ApElect", data->ApElect);
    cJSON_AddStringToObject(body, "BpElect", data->BpElect);
    cJSON_AddStringToObject(body, "CpElect", data->CpElect);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//充电设备输出电表底值监测属性表
static int32_t send_property_dc_outmeter(evs_property_meter *data)
{
    int32_t res = 0;
    uint8_t *payload, meterAddr[13] = {0}, meter[6] = {0};
    cJSON *root, *body, *inMeterArray, *outMeterArray;
    uint8_t i = 0, j = 0, k = 0;
    uint8_t meterCnt = 0;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcOutMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddStringToObject(body, "acqTime", data->acqTime);
    cJSON_AddStringToObject(body, "mailAddr", data->mailAddr);
    cJSON_AddStringToObject(body, "meterNo", data->meterNo);
    cJSON_AddStringToObject(body, "assetID", data->assetID);
    cJSON_AddStringToObject(body, "sumMeter", data->sumMeter);
    cJSON_AddStringToObject(body, "lastTrade", data->lastTrade);
    cJSON_AddStringToObject(body, "power", data->power);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//充电设备输出电表底值监测属性表
static int32_t send_property_ac_outmeter(evs_property_meter *data)
{
    int32_t res = 0;
    uint8_t *payload, meterAddr[13] = {0}, meter[6] = {0};
    cJSON *root, *body, *inMeterArray, *outMeterArray;
    uint8_t i = 0, j = 0, k = 0;
    uint8_t meterCnt = 0;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acOutMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddStringToObject(body, "acqTime", data->acqTime);
    cJSON_AddStringToObject(body, "mailAddr", data->mailAddr);
    cJSON_AddStringToObject(body, "meterNo", data->meterNo);
    cJSON_AddStringToObject(body, "assetID", data->assetID);
    cJSON_AddStringToObject(body, "sumMeter", data->sumMeter);
    cJSON_AddStringToObject(body, "lastTrade", data->lastTrade);
    cJSON_AddStringToObject(body, "power", data->power);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(EXAMPLE_MASTER_DEVID, ITM_MSG_POST_PROPERTY,
                             (uint8_t *)payload, strlen(payload));
    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_firware_info(evs_event_fireware_info *data)
{
    int32_t res = 0;
    uint8_t *payload, meterAddr[13] = {0}, meter[6] = {0};
    cJSON *root, *inMeterArray, *outMeterArray;
    uint8_t i = 0, j = 0, k = 0;
    uint8_t meterCnt = 0;

    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "simNo", data->simNo);
    cJSON_AddStringToObject(root, "modelId", data->modelId);
    cJSON_AddStringToObject(root, "stakeModel", data->stakeModel);
    cJSON_AddStringToObject(root, "devSn", data->devSn);
    cJSON_AddStringToObject(root, "modelId", data->modelId);
    cJSON_AddStringToObject(root, "stakeModel", data->stakeModel);

    cJSON_AddStringToObject(root, "simMac", data->simMac);
    cJSON_AddStringToObject(root, "btMac", data->btMac);

    cJSON_AddNumberToObject(root, "vendorCode", data->vendorCode);
    cJSON_AddNumberToObject(root, "devType", data->devType);
    cJSON_AddNumberToObject(root, "portNum", data->portNum);

    cJSON_AddNumberToObject(root, "longitude", data->longitude);
    cJSON_AddNumberToObject(root, "latitude", data->latitude);
    cJSON_AddNumberToObject(root, "height", data->height);

    cJSON_AddNumberToObject(root, "gridType", data->gridType);
    cJSON_AddNumberToObject(root, "meaType", data->meaType);
    cJSON_AddNumberToObject(root, "otRate", data->otRate);

    cJSON_AddNumberToObject(root, "otMaxVol", data->otMaxVol);
    cJSON_AddNumberToObject(root, "otMinVol", data->otMinVol);
    cJSON_AddNumberToObject(root, "otCur", data->otCur);

    cJSON_AddNumberToObject(root, "CT", data->CT);
    cJSON_AddNumberToObject(root, "isGateLock", data->isGateLock);
    cJSON_AddNumberToObject(root, "isGroundLock", data->isGroundLock);

    cJSON_AddItemToObject(root, "inMeter", inMeterArray = cJSON_CreateArray());
    for (i = 0; i < 2; i++)
    {
        if (memcmp(data->inMeter[i], meter, 6) != 0)
        {
            for (j = 0, k = 0; j < 6, k < 12; k++, j++)
            {
                meterAddr[k] = ((data->inMeter[i][j] >> 4) + '0');
                meterAddr[++k] = (data->inMeter[i][j] & 0x0f) + '0';
            }
            cJSON_AddStringToArray(inMeterArray, meterAddr);
        }
    }

    cJSON_AddItemToObject(root, "outMeter", outMeterArray = cJSON_CreateArray());
    for (i = 0; i < 4; i++)
    {
        if (memcmp(data->outMeter[i], meter, 6) != 0)
        {
            for (j = 0, k = 0; j < 6, k < 12; k++, j++)
            {
                meterAddr[k] = ((data->outMeter[i][j] >> 4) + '0');
                meterAddr[++k] = (data->outMeter[i][j] & 0x0f) + '0';
            }
            cJSON_AddStringToArray(outMeterArray, meterAddr);
        }
    }

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "firmwareEvt", strlen("firmwareEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_ask_feeModel(evs_event_ask_feeModel *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(root, "serModelId", data->serModeId);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "askFeeModelEvt", strlen("askFeeModelEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_start_result(evs_event_startResult *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "startResult", data->startResult);
    cJSON_AddNumberToObject(root, "faultCode", data->faultCode);
    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddStringToObject(root, "vinCode", data->vinCode);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "startChaResEvt", strlen("startChaResEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_auth_start(evs_event_startCharge *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "startType", data->startType);

    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddStringToObject(root, "authCode", data->authCode);

    cJSON_AddNumberToObject(root, "batterySOC", data->batterySOC);
    cJSON_AddNumberToObject(root, "batteryCap", data->batteryCap);

    cJSON_AddNumberToObject(root, "chargeTimes", data->chargeTimes);

    cJSON_AddNumberToObject(root, "batteryVol", data->batteryVol);
    cJSON_AddNumberToObject(root, "auxiVolt", data->auxiVolt);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "startChargeAuthEvt", strlen("startChargeAuthEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_stopCharge(evs_event_stopCharge *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "stopResult", data->stopResult);
    cJSON_AddNumberToObject(root, "resultCode", data->resultCode);
    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddNumberToObject(root, "stopFailReson", data->stopFailReson);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "stopChaResEvt", strlen("stopChaResEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_groundLock_change(evs_event_groundLock_change *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "lockState", data->lockState);
    cJSON_AddNumberToObject(root, "powerType", data->powerType);
    cJSON_AddStringToObject(root, "cellState", data->cellState);
    cJSON_AddStringToObject(root, "lockerState", data->lockerState);
    cJSON_AddNumberToObject(root, "lockerForced", data->lockerForced);
    cJSON_AddNumberToObject(root, "lowPower", data->lowPower);
    cJSON_AddNumberToObject(root, "soc", data->soc);
    cJSON_AddStringToObject(root, "openCnt", data->openCnt);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "groundLockEvt", strlen("groundLockEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_gateLock_change(evs_event_gateLock_change *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "lockNo", data->lockNo);
    cJSON_AddNumberToObject(root, "lockState", data->lockState);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "smartLockEvent", strlen("smartLockEvent"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_tradeInfo(evs_event_tradeInfo *data)
{
    int32_t res = 0;
    uint8_t *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);

    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddStringToObject(root, "vinCode", data->vinCode);

    cJSON_AddNumberToObject(root, "timeDivType", data->timeDivType);
    cJSON_AddNumberToObject(root, "totalElect", data->totalElect);

    cJSON_AddNumberToObject(root, "sharpElect", data->sharpElect);
    cJSON_AddNumberToObject(root, "peakElect", data->peakElect);

    cJSON_AddNumberToObject(root, "flatElect", data->flatElect);
    cJSON_AddNumberToObject(root, "valleyElect", data->valleyElect);

    cJSON_AddNumberToObject(root, "totalPowerCost", data->totalPowerCost);
    cJSON_AddNumberToObject(root, "totalServCost", data->totalServCost);

    cJSON_AddNumberToObject(root, "sharpPowerCost", data->sharpPowerCost);

    cJSON_AddNumberToObject(root, "peakPowerCost", data->peakPowerCost);
    cJSON_AddNumberToObject(root, "flatPowerCost", data->flatPowerCost);

    cJSON_AddNumberToObject(root, "valleyPowerCost", data->valleyPowerCost);
    cJSON_AddNumberToObject(root, "sharpServCost", data->sharpServCost);

    cJSON_AddNumberToObject(root, "peakServCost", data->peakServCost);
    cJSON_AddNumberToObject(root, "flatServCost", data->flatServCost);
    cJSON_AddNumberToObject(root, "flatServCost", data->valleyServCost);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "orderUpdateEvt", strlen("orderUpdateEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_alarm(evs_event_alarm *data)
{
    int32_t res = 0;
    uint8_t *payload;
    cJSON *root, *faultArray, *warnArray;
    uint8_t i = 0;

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "faultSum", data->faultSum);
    cJSON_AddNumberToObject(root, "warnSum", data->warnSum);

    cJSON_AddItemToObject(root, "faultValue", faultArray = cJSON_CreateArray());
    for (i = 0; i < data->faultSum; i++)
        cJSON_AddNumberToArray(faultArray, data->faultValue[i]);

    cJSON_AddItemToObject(root, "warnValue", warnArray = cJSON_CreateArray());
    for (i = 0; i < data->warnSum; i++)
        cJSON_AddNumberToArray(warnArray, data->warnValue[i]);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "totalFaultEvt", strlen("totalFaultEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_acPile_change(evs_event_pile_stutus_change *data)
{
    int32_t res = 0;
    uint8_t *payload, *time[16] = {0};
    cJSON *root, *valArray;
    uint8_t i = 0;

    sprintf(time, "%d", data->time);

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "time", time);
    cJSON_AddNumberToObject(root, "Sum", data->Sum);

    cJSON_AddItemToObject(root, "val", valArray = cJSON_CreateArray());
    //for (i = 0; i < data->Sum; i++)
    //cJSON_AddStringToArray(valArray, data->val[i]);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "acStChEvt", strlen("acStChEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int32_t send_event_dcPile_change(evs_event_pile_stutus_change *data)
{
    int32_t res = 0;
    uint8_t *payload, *time[16] = {0};
    cJSON *root, *valArray;
    uint8_t i = 0;

    sprintf(time, "%d", data->time);

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "time", time);
    cJSON_AddNumberToObject(root, "Sum", data->Sum);

    cJSON_AddItemToObject(root, "val", valArray = cJSON_CreateArray());
    for (i = 0; i < data->Sum; i++)
        cJSON_AddStringToArray(valArray, data->val[i]);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(EXAMPLE_MASTER_DEVID, "dcStChEvt", strlen("acStChEvt"), payload, strlen(payload));

    if (root)
        cJSON_Delete(root);
    HAL_Free(payload);

    EXAMPLE_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
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
// void protocol_service_callback(evs_service_type_t type, void *service_data)
// {

//     void *callback;
//     int output1 = 0, output2 = 0;
//     switch (type)
//     {
//     case EVS_GATA_LOCK_SRV /* constant-expression */:
//         /* code */
//         callback = evs_service_callback(EVS_GATA_LOCK_SRV);
//         if (callback)
//         {
//             ((int (*)(const int, int *))callback)(5, &output1);
//         }
//         printf("evs_service_callback EVS_GATA_LOCK_SRV %d\n", output1);
//         break;
//     case EVS_CHARGE_START_SRV /* constant-expression */:
//         /* code */
//         callback = evs_service_callback(EVS_GATA_LOCK_SRV);
//         if (callback)
//         {
//             ((int (*)(const int, int *))callback)(10, &output2);
//         }
//         printf("evs_service_callback EVS_CHARGE_START_SRV %d\n", output2);
//         break;

//     default:
//         break;
//     }
// }

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
    case EVS_CMD_EVENT_FIREWARE_INFO:
    {
        send_event_firware_info((evs_event_fireware_info *)param);
        break;
    }

    case EVS_CMD_EVENT_ASK_FEEMODEL:
        send_event_ask_feeModel((evs_event_ask_feeModel *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_STARTCHARGE:
        send_event_auth_start((evs_event_startCharge *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_STARTRESULT:
        send_event_start_result((evs_event_startResult *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_STOPCHARGE:
        send_event_stopCharge((evs_event_stopCharge *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_TRADEINFO:
        send_event_tradeInfo((evs_event_tradeInfo *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_ALARM:
        send_event_alarm((evs_event_alarm *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_ACPILE_CHANGE:
        send_event_acPile_change((evs_event_pile_stutus_change *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_DCPILE_CHANGE:
        send_event_dcPile_change((evs_event_pile_stutus_change *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_GROUNDLOCK_CHANGE:
        send_event_groundLock_change((evs_event_groundLock_change *)param);
        /* code */
        break;
    case EVS_CMD_EVENT_GATELOCK_CHANGE:
        send_event_gateLock_change((evs_event_gateLock_change *)param);
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
    case EVS_CMD_PROPERTY_DCPILE:
        send_property_dcPile((evs_property_dcPile *)param);
        break;
    case EVS_CMD_PROPERTY_ACPILE:
        send_property_acPile((evs_property_acPile *)param);
        break;
    case EVS_CMD_PROPERTY_AC_WORK:
        send_property_ac_work((evs_property_ac_work *)param);
        break;
    case EVS_CMD_PROPERTY_AC_NONWORK:
        send_property_ac_nonwork((evs_property_ac_nonWork *)param);
        break;
    case EVS_CMD_PROPERTY_BMS:
        send_property_bms((evs_property_BMS *)param);
        break;
    case EVS_CMD_PROPERTY_DC_INPUT_METER:
        send_property_dc_input_meter((evs_property_dc_input_meter *)param);
        break;
    case EVS_CMD_PROPERTY_AC_OUTMETER:
        send_property_ac_outmeter((evs_property_meter *)param);
        break;
    case EVS_CMD_PROPERTY_DC_OUTMETER:
        send_property_dc_outmeter((evs_property_meter *)param);
        break;
    case EVS_CMD_PROPERTY_DC_WORK:
        send_property_dc_work((evs_property_dc_work *)param);
        break;
    case EVS_CMD_PROPERTY_DC_NONWORK:
        send_property_dc_nonwork((evs_property_dc_nonWork *)param);
        break;
    default:
        break;
    }
}