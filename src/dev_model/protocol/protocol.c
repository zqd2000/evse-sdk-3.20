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

#ifdef DYNAMIC_REGISTER
#include "dynreg_api.h"
#endif

//#define cJSON_AddNumberToArray(array, n) cJSON_AddItemToArray(array, cJSON_CreateNumber(n))
//#define cJSON_AddStringToArray(array, s) cJSON_AddItemToArray(array, cJSON_CreateString(s))

char g_product_key[IOTX_PRODUCT_KEY_LEN + 1] = "";
/* setup your productSecret !!! */
char g_product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = " ";
/* setup your deviceName !!! */
char g_device_name[IOTX_DEVICE_NAME_LEN + 1] = "";
/* setup your deviceSecret !!! */
char g_device_secret[IOTX_DEVICE_SECRET_LEN + 1] = "";
/* setup your device_reg_code !!! */
char g_device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1] = "";

#if defined(PLATFORM_IS_DEBUG)
#define PROTOCOL_TRACE(...)                                     \
    do                                                          \
    {                                                           \
        HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__); \
        HAL_Printf(__VA_ARGS__);                                \
        HAL_Printf("\033[0m\r\n");                              \
    } while (0)
#else
#define PROTOCOL_TRACE(...)
#endif

#define EVS_YIELD_TIMEOUT_MS (200)

unsigned int strtoint(char s[])
{
    unsigned int i;
    unsigned int num = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
    {
        num = 10 * num + (s[i] - '0');
    }
    return num;
}

void bcd2str(unsigned char bcd[], char str[], unsigned int bcd_len)
{
    int i = 0, k = 0;
    char buf[32] = {0};

    if (memcmp(bcd, buf, bcd_len) != 0)
    {

        for (i = 0, k = 0; i < bcd_len && k < (2 * bcd_len); k++, i++)
        {
            str[k] = ((bcd[i] >> 4) + '0');
            str[++k] = (bcd[i] & 0x0f) + '0';
        }
    }
}

typedef struct
{
    int master_devid;
    int cloud_connected;
    int master_initialized;
} evs_user_ctx_t;
static evs_user_ctx_t evs_g_user_ctx;
iotx_linkkit_dev_meta_info_t master_meta_info;

/**
 * @brief 解析所有属性设置的值
 * @param request 指向属性设置请求payload的指针
 * @param request_len 属性设置请求的payload长度
 * @return 解析成功: 0, 解析失败: <0
 */
int app_parse_property(const char *request, unsigned int request_len)
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
        PROTOCOL_TRACE("struct property id: structCnt");
    }

    cJSON_Delete(req);
    return 0;
}

/** 建连成功事件回调 */
static int user_connected_event_handler(void)
{
    void *callback;
    evs_g_user_ctx.cloud_connected = 1;
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
    evs_g_user_ctx.cloud_connected = 0;
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
    evs_g_user_ctx.master_initialized = 1;
    return 0;
}

/** 事件回调：接收到云端回复属性上报应答 **/
static int user_report_reply_event_handler(const int devid, const int msgid, const int code, const char *reply,
                                           const int reply_len)
{
    void *callback;

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
    PROTOCOL_TRACE("Property Set Received, Request: %s", request);

    app_parse_property(request, request_len);

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY,
                             (unsigned char *)request, request_len);
    PROTOCOL_TRACE("Post Property return: %d", res);

    return res;
}

/** 事件回调：接收到云端回复的时间戳 **/
static int user_timestamp_reply_event_handler(const char *timestamp)
{
    PROTOCOL_TRACE("Current Timestamp: %s", timestamp);

    char time_buf[11] = {0};
    memcpy(time_buf, timestamp, sizeof(time_buf) - 1);

    unsigned int time = strtoint(time_buf);

    void *callback;
    callback = evs_service_callback(EVS_TIME_SYNC);
    if (callback)
    {
        ((int (*)(unsigned int))callback)(time);
    }
    return 0;
}

/** FOTA事件回调处理 **/
static int user_fota_event_handler(int type, const char *version)
{

    /* 0 - new firmware exist, query the new firmware */
    if (type == 0)
    {
        PROTOCOL_TRACE("New Firmware Version: %s", version);
        void *callback;
        callback = evs_service_callback(EVS_OTA_UPDATE);
        if (callback)
        {
            ((int (*)(const char *))callback)(version);
        }
    }
    return 0;
}

/** 事件回调：接收到云端错误信息 **/
static int user_cloud_error_handler(const int code, const char *data, const char *detail)
{
    PROTOCOL_TRACE("code =%d ,data=%s, detail=%s", code, data, detail);
    return 0;
}

/** 事件回调：通过动态注册获取到DeviceSecret **/
static int dynreg_device_secret(const char *device_secret)
{
    PROTOCOL_TRACE("device secret: %s", device_secret);
    return 0;
}

/** 事件回调: SDK内部运行状态打印 **/
static int user_sdk_state_dump(int ev, const char *msg)
{
    void *callback;
    PROTOCOL_TRACE("received state event, -0x%04x(%s)\n", -ev, msg);
    callback = evs_service_callback(EVS_STATE_EVERYTHING);
    if (callback)
    {
        ((int (*)(int ev, const char *msg))callback)(ev, msg);
    }
    return 0;
}

static int evs_service_get_config_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    int i = 0;
    evs_data_dev_config service_dev_feedback_config_data;

    callback = evs_service_callback(EVS_CONF_GET_SRV);
    if (callback)
    {
        ((int (*)(const evs_data_dev_config *feedcak))callback)(&service_dev_feedback_config_data);
    }

    cJSON *response_root = cJSON_CreateObject();
    cJSON *qrCodeArray;

    cJSON_AddNumberToObject(response_root, "equipParamFreq", service_dev_feedback_config_data.equipParamFreq);
    cJSON_AddNumberToObject(response_root, "gunElecFreq", service_dev_feedback_config_data.gunElecFreq);
    cJSON_AddNumberToObject(response_root, "nonElecFreq", service_dev_feedback_config_data.nonElecFreq);
    cJSON_AddNumberToObject(response_root, "faultWarnings", service_dev_feedback_config_data.faultWarnings);
    cJSON_AddNumberToObject(response_root, "acMeterFreq", service_dev_feedback_config_data.acMeterFreq);
    cJSON_AddNumberToObject(response_root, "dcMeterFreq", service_dev_feedback_config_data.dcMeterFreq);
    cJSON_AddNumberToObject(response_root, "offlinChaLen", service_dev_feedback_config_data.offlinChaLen);
    cJSON_AddNumberToObject(response_root, "grndLock", service_dev_feedback_config_data.grndLock);
    cJSON_AddNumberToObject(response_root, "doorLock", service_dev_feedback_config_data.doorLock);

    cJSON_AddItemToObject(response_root, "qrCode", qrCodeArray = cJSON_CreateArray());
    for (i = 0; i < EVS_MAX_PORT_NUM; i++)
    {
        //cJSON_AddStringToArray(qrCodeArray, service_dev_feedback_config_data.qrCode[i]);
        cJSON_AddItemToArray(qrCodeArray, cJSON_CreateString(service_dev_feedback_config_data.qrCode[i]));
    }

    *response = cJSON_PrintUnformatted(response_root);
    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_update_config_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_data_dev_config service_dev_config_data;
    int feedback_data;
    int i = 0;
    memset(&service_dev_config_data, 0, sizeof(service_dev_config_data));
    cJSON *item_equipParamFreq = cJSON_GetObjectItem(root, "equipParamFreq");
    if (item_equipParamFreq != NULL && cJSON_IsNumber(item_equipParamFreq))
    {
        service_dev_config_data.equipParamFreq = item_equipParamFreq->valueint;
    }

    cJSON *item_gunElecFeeq = cJSON_GetObjectItem(root, "gunElecFreq");
    if (item_gunElecFeeq != NULL && cJSON_IsNumber(item_gunElecFeeq))
    {
        service_dev_config_data.gunElecFreq = item_gunElecFeeq->valueint;
    }

    cJSON *item_nonElecFreq = cJSON_GetObjectItem(root, "nonElecFreq");
    if (item_nonElecFreq != NULL && cJSON_IsNumber(item_nonElecFreq))
    {
        service_dev_config_data.nonElecFreq = item_nonElecFreq->valueint;
    }

    cJSON *item_faultWarnings = cJSON_GetObjectItem(root, "faultWarnings");
    if (item_faultWarnings != NULL && cJSON_IsNumber(item_faultWarnings))
    {
        service_dev_config_data.faultWarnings = item_faultWarnings->valueint;
    }

    cJSON *item_acMeterFreq = cJSON_GetObjectItem(root, "acMeterFreq");
    if (item_acMeterFreq != NULL && cJSON_IsNumber(item_acMeterFreq))
    {
        service_dev_config_data.acMeterFreq = item_acMeterFreq->valueint;
    }

    cJSON *item_dcMeterFreq = cJSON_GetObjectItem(root, "dcMeterFreq");
    if (item_dcMeterFreq != NULL && cJSON_IsNumber(item_dcMeterFreq))
    {
        service_dev_config_data.dcMeterFreq = item_dcMeterFreq->valueint;
    }

    cJSON *item_offlinChaLen = cJSON_GetObjectItem(root, "offlinChaLen");
    if (item_offlinChaLen != NULL && cJSON_IsNumber(item_offlinChaLen))
    {
        service_dev_config_data.offlinChaLen = item_offlinChaLen->valueint;
    }

    cJSON *item_grndLock = cJSON_GetObjectItem(root, "grndLock");
    if (item_grndLock != NULL && cJSON_IsNumber(item_grndLock))
    {
        service_dev_config_data.grndLock = item_grndLock->valueint;
    }

    cJSON *item_doorLock = cJSON_GetObjectItem(root, "doorLock");
    if (item_doorLock != NULL && cJSON_IsNumber(item_doorLock))
    {
        service_dev_config_data.doorLock = item_doorLock->valueint;
    }

    cJSON *item_qrCode = cJSON_GetObjectItem(root, "qrCode");
    if (item_qrCode != NULL && cJSON_IsArray(item_qrCode))
    {
        cJSON *item_arrayData;
        int qrcode_num = cJSON_GetArraySize(item_qrCode);
        qrcode_num = (qrcode_num <= EVS_MAX_PORT_NUM) ? qrcode_num : EVS_MAX_PORT_NUM;
        int qrcode_len = strlen(item_arrayData->valuestring) + 1;
        if (qrcode_len < EVS_MAX_QRCODE_LEN)
        {
            for (i = 0; i < qrcode_num; i++)
            {
                item_arrayData = cJSON_GetArrayItem(item_qrCode, i);
                memcpy(service_dev_config_data.qrCode[i], item_arrayData->valuestring, qrcode_len);
            }
        }
        else
        {
            PROTOCOL_TRACE("QrCode buffer is too small!!!");
        }
    }

    callback = evs_service_callback(EVS_CONF_UPDATE_SRV);
    if (callback)
    {
        ((int (*)(const evs_data_dev_config *request, int *feedcak))callback)(&service_dev_config_data, &feedback_data);
    }

    cJSON *response_root = cJSON_CreateObject();
    if ((feedback_data != 10) && (feedback_data != 11)) //必须处理返回值，并返回结果，负责默认回复失败
    {
        cJSON_AddNumberToObject(response_root, "resCode", 11);
    }
    else
    {
        cJSON_AddNumberToObject(response_root, "resCode", feedback_data);
    }

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_issue_feeModel_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_issue_feeModel service_feeModel_data;
    evs_service_feedback_feeModel service_feedback_feeModel_data;
    int i = 0;
    memset(&service_feeModel_data, 0, sizeof(service_feeModel_data));
    cJSON *item_eleModelId = cJSON_GetObjectItem(root, "eleModelId");
    if (item_eleModelId != NULL && cJSON_IsString(item_eleModelId))
    {
        char *eleModelId = item_eleModelId->valuestring;
        memcpy(service_feeModel_data.eleModelId, eleModelId, strlen(eleModelId));
    }

    /****服务费模型id*****/
    cJSON *item_serModelId = cJSON_GetObjectItem(root, "serModelId");
    if (item_serModelId != NULL && cJSON_IsString(item_serModelId))
    {
        char *serModelId = item_serModelId->valuestring;
        memcpy(service_feeModel_data.serModelId, serModelId, strlen(serModelId));
    }

    cJSON *item_eleTimeNum = cJSON_GetObjectItem(root, "timeNum");
    if (item_eleTimeNum != NULL && cJSON_IsNumber(item_eleTimeNum))
    {
        service_feeModel_data.TimeNum = item_eleTimeNum->valueint;
    }

    cJSON *item_TimeSeg = cJSON_GetObjectItem(root, "timeSeg");
    cJSON *array_timeSeg = NULL;
    if (item_TimeSeg != NULL && cJSON_IsArray(item_TimeSeg))
    {

        for (i = 0; i < service_feeModel_data.TimeNum; i++)
        {
            array_timeSeg = cJSON_GetArrayItem(item_TimeSeg, i);
            memcpy(service_feeModel_data.TimeSeg[i], array_timeSeg->valuestring, strlen(array_timeSeg->valuestring));
        }
    }

    cJSON *item_SegFlag = cJSON_GetObjectItem(root, "segFlag");
    cJSON *arrary_segFlag = NULL;
    if (item_SegFlag != NULL && cJSON_IsArray(item_SegFlag))
    {

        for (i = 0; i < service_feeModel_data.TimeNum; i++)
        {
            arrary_segFlag = cJSON_GetArrayItem(item_SegFlag, i);
            service_feeModel_data.SegFlag[i] = arrary_segFlag->valueint;
        }
    }

    cJSON *item_chargeFee = cJSON_GetObjectItem(root, "chargeFee");
    cJSON *arrary_chargeFee = NULL;
    if (item_chargeFee != NULL && cJSON_IsArray(item_chargeFee))
    {
        for (i = 0; i < 4; i++)
        {
            arrary_chargeFee = cJSON_GetArrayItem(item_chargeFee, i);
            service_feeModel_data.chargeFee[i] = arrary_chargeFee->valueint;
        }
    }

    cJSON *item_serviceFee = cJSON_GetObjectItem(root, "serviceFee");
    cJSON *arrary_serviceFee = NULL;
    if (item_serviceFee != NULL && cJSON_IsArray(item_serviceFee))
    {
        for (i = 0; i < 4; i++)
        {
            arrary_serviceFee = cJSON_GetArrayItem(item_serviceFee, i);
            service_feeModel_data.serviceFee[i] = arrary_serviceFee->valueint;
        }
    }

    callback = evs_service_callback(EVS_FEE_MODEL_UPDATA_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_issue_feeModel *request, evs_service_feedback_feeModel *feedcak))callback)(&service_feeModel_data, &service_feedback_feeModel_data);
    }
    cJSON *response_root = cJSON_CreateObject();
    cJSON_AddStringToObject(response_root, "eleModelId", service_feedback_feeModel_data.eleModelId);
    cJSON_AddStringToObject(response_root, "serModelId", service_feedback_feeModel_data.serModelId);
    cJSON_AddNumberToObject(response_root, "result", service_feedback_feeModel_data.result);

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_startCharge_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }
    evs_service_startCharge service_charge_data;
    evs_service_feedback_startCharge service_feedback_startCharge_data;
    memset(&service_charge_data, 0, sizeof(service_charge_data));
    /* Parse json */
    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_charge_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
    if (item_preTradeNo != NULL && cJSON_IsString(item_preTradeNo))
    {
        memcpy(service_charge_data.preTradeNo, item_preTradeNo->valuestring, strlen(item_preTradeNo->valuestring));
    }

    cJSON *item_startType = cJSON_GetObjectItem(root, "startType");
    if (item_startType != NULL && cJSON_IsNumber(item_startType))
    {
        service_charge_data.startType = item_startType->valueint;
    }

    cJSON *item_chargeMode = cJSON_GetObjectItem(root, "chargeMode");
    if (item_chargeMode != NULL && cJSON_IsNumber(item_chargeMode))
    {
        service_charge_data.chargeMode = item_chargeMode->valueint;
    }

    cJSON *item_limitData = cJSON_GetObjectItem(root, "limitData");
    if (item_limitData != NULL && cJSON_IsNumber(item_limitData))
    {
        service_charge_data.limitData = item_limitData->valueint;
    }

    cJSON *item_stopCode = cJSON_GetObjectItem(root, "stopCode");
    if (item_stopCode != NULL && cJSON_IsNumber(item_stopCode))
    {
        service_charge_data.stopCode = item_stopCode->valueint;
    }

    cJSON *item_startMode = cJSON_GetObjectItem(root, "startMode");
    if (item_startMode != NULL && cJSON_IsNumber(item_startMode))
    {
        service_charge_data.startMode = item_startMode->valueint;
    }

    cJSON *item_insertGunTime = cJSON_GetObjectItem(root, "insertGunTime");
    if (item_insertGunTime != NULL && cJSON_IsNumber(item_insertGunTime))
    {
        service_charge_data.insertGunTime = item_insertGunTime->valueint;
    }

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

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_authCharge_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }
    evs_service_authCharge service_authCharge_data;
    evs_service_feedback_authCharge service_feedback_authCharge_data;

    memset(&service_authCharge_data, 0, sizeof(service_authCharge_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_authCharge_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
    if (item_preTradeNo != NULL && cJSON_IsString(item_preTradeNo))
    {
        char *tradeNo = item_preTradeNo->valuestring;
        memcpy(service_authCharge_data.preTradeNo, tradeNo, strlen(tradeNo));
    }

    cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
    if (item_tradeNo != NULL && cJSON_IsString(item_tradeNo))
    {
        char *devTradeNo = item_tradeNo->valuestring;
        memcpy(service_authCharge_data.tradeNo, devTradeNo, strlen(devTradeNo));
    }

    cJSON *item_vinCode = cJSON_GetObjectItem(root, "vinCode");
    if (item_vinCode != NULL && cJSON_IsString(item_vinCode))
    {
        char *vinCode = item_vinCode->valuestring;
        memcpy(service_authCharge_data.vinCode, vinCode, strlen(vinCode));
    }

    cJSON *item_oppoCode = cJSON_GetObjectItem(root, "oppoCode");
    if (item_oppoCode != NULL && cJSON_IsString(item_oppoCode))
    {
        char *oppoCode = item_oppoCode->valuestring;
        memcpy(service_authCharge_data.oppoCode, oppoCode, strlen(oppoCode));
    }

    cJSON *item_result = cJSON_GetObjectItem(root, "result");
    if (item_result != NULL && cJSON_IsNumber(item_result))
    {
        service_authCharge_data.result = item_result->valueint;
    }

    cJSON *item_chargeMode = cJSON_GetObjectItem(root, "chargeMode");
    if (item_chargeMode != NULL && cJSON_IsNumber(item_chargeMode))
    {
        service_authCharge_data.chargeMode = item_chargeMode->valueint;
    }

    cJSON *item_limitData = cJSON_GetObjectItem(root, "limitData");
    if (item_limitData != NULL && cJSON_IsNumber(item_limitData))
    {
        service_authCharge_data.limitData = item_limitData->valueint;
    }

    cJSON *item_stopCode = cJSON_GetObjectItem(root, "stopCode");
    if (item_stopCode != NULL && cJSON_IsNumber(item_stopCode))
    {
        service_authCharge_data.stopCode = item_stopCode->valueint;
    }

    cJSON *item_startMode = cJSON_GetObjectItem(root, "startMode");
    if (item_startMode != NULL && cJSON_IsNumber(item_startMode))
    {
        service_authCharge_data.startMode = item_startMode->valueint;
    }

    cJSON *item_insertGunTime = cJSON_GetObjectItem(root, "insertGunTime");
    if (item_insertGunTime != NULL && cJSON_IsNumber(item_insertGunTime))
    {
        service_authCharge_data.insertGunTime = item_insertGunTime->valueint;
    }

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

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_stopCharge_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_stopCharge service_stopCharge_data;
    evs_service_feedback_stopCharge service_feedback_stopCharge_data;

    memset(&service_stopCharge_data, 0, sizeof(service_stopCharge_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_stopCharge_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
    if (item_preTradeNo != NULL && cJSON_IsString(item_preTradeNo))
    {
        char *tradeNo = item_preTradeNo->valuestring;
        memcpy(service_stopCharge_data.preTradeNo, tradeNo, strlen(tradeNo));
    }

    cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
    if (item_tradeNo != NULL && cJSON_IsString(item_tradeNo))
    {
        char *devTradeNo = item_tradeNo->valuestring;
        memcpy(service_stopCharge_data.tradeNo, devTradeNo, strlen(devTradeNo));
    }

    cJSON *item_stopReason = cJSON_GetObjectItem(root, "stopReason");
    if (item_stopReason != NULL && cJSON_IsNumber(item_stopReason))
    {
        service_stopCharge_data.stopReason = item_stopReason->valueint;
    }

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

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_confirmTrade_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }
    evs_service_confirmTrade service_confirmTrade_data;

    memset(&service_confirmTrade_data, 0, sizeof(service_confirmTrade_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_confirmTrade_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
    if (item_preTradeNo != NULL && cJSON_IsString(item_preTradeNo))
    {
        char *tradeNo = item_preTradeNo->valuestring;
        memcpy(service_confirmTrade_data.preTradeNo, tradeNo, strlen(tradeNo));
    }

    cJSON *item_tradeNo = cJSON_GetObjectItem(root, "tradeNo");
    if (item_tradeNo != NULL && cJSON_IsString(item_tradeNo))
    {
        char *devTradeNo = item_tradeNo->valuestring;
        memcpy(service_confirmTrade_data.tradeNo, devTradeNo, strlen(devTradeNo));
    }

    cJSON *item_errcode = cJSON_GetObjectItem(root, "errcode");
    if (item_errcode != NULL && cJSON_IsNumber(item_errcode))
    {
        service_confirmTrade_data.errcode = item_errcode->valueint;
    }
    callback = evs_service_callback(EVS_ORDER_CHECK_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_confirmTrade *request, void *feedcak))callback)(&service_confirmTrade_data, NULL);
    }
    cJSON_Delete(root);

    return 0;
}

static int evs_service_query_log_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }
    evs_service_query_log service_query_log_data;
    evs_service_feedback_query_log feedback_query_log_data;
    char temp[16] = {0};

    memset(&service_query_log_data, 0, sizeof(service_query_log_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_query_log_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_startDate = cJSON_GetObjectItem(root, "startDate");
    if (item_startDate != NULL && cJSON_IsString(item_startDate))
    {
        char *startDate = item_startDate->valuestring;
        service_query_log_data.startDate = strtoint(startDate);
    }

    cJSON *item_stopDate = cJSON_GetObjectItem(root, "stopDate");
    if (item_stopDate != NULL && cJSON_IsString(item_stopDate))
    {
        char *stopDate = item_stopDate->valuestring;
        service_query_log_data.stopDate = strtoint(stopDate);
    }

    cJSON *item_askType = cJSON_GetObjectItem(root, "askType");
    if (item_askType != NULL && cJSON_IsNumber(item_askType))
    {
        service_query_log_data.askType = item_askType->valueint;
    }

    callback = evs_service_callback(EVS_QUE_DARA_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_query_log *request, evs_service_feedback_query_log *feedcak))callback)(&service_query_log_data, &feedback_query_log_data);
    }
    cJSON *response_root = cJSON_CreateObject();
    cJSON_AddNumberToObject(response_root, "gunNo", feedback_query_log_data.gunNo);

    sprintf(temp, "%d", feedback_query_log_data.startDate);
    cJSON_AddStringToObject(response_root, "startDate", temp);

    sprintf(temp, "%d", feedback_query_log_data.stopDate);
    cJSON_AddStringToObject(response_root, "stopDate", temp);

    cJSON_AddNumberToObject(response_root, "askType", feedback_query_log_data.askType);
    cJSON_AddNumberToObject(response_root, "succ", feedback_query_log_data.succ);
    cJSON_AddNumberToObject(response_root, "retType", feedback_query_log_data.retType);
    cJSON_AddStringToObject(response_root, "dataArea", feedback_query_log_data.dataArea);

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_gateLock_ctrl_handler(const char *request, char **response, int *response_len)
{

    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_gateLock_ctrl service_gateLock_ctrl_data;
    evs_service_feedback_gateLock_ctrl service_feedback_gateLock_ctrl_data;

    memset(&service_gateLock_ctrl_data, 0, sizeof(service_gateLock_ctrl_data));

    cJSON *item_lockNo = cJSON_GetObjectItem(root, "lockNo");
    if (item_lockNo != NULL && cJSON_IsNumber(item_lockNo))
    {
        service_gateLock_ctrl_data.lockNo = item_lockNo->valueint;
    }

    cJSON *item_ctrlFlag = cJSON_GetObjectItem(root, "ctrlFlag");
    if (item_ctrlFlag != NULL && cJSON_IsNumber(item_ctrlFlag))
    {
        service_gateLock_ctrl_data.ctrlFlag = item_ctrlFlag->valueint;
    }

    callback = evs_service_callback(EVS_GATE_LOCK_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_gateLock_ctrl *request, evs_service_feedback_gateLock_ctrl *feedcak))callback)(&service_gateLock_ctrl_data, &service_feedback_gateLock_ctrl_data);
    }

    cJSON *response_root = cJSON_CreateObject();
    cJSON_AddNumberToObject(response_root, "lockNo", service_feedback_gateLock_ctrl_data.lockNo);
    cJSON_AddNumberToObject(response_root, "result", service_feedback_gateLock_ctrl_data.result);

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_groundLock_ctrl_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_groundLock_ctrl service_groundLock_ctrl_data;
    evs_service_feedback_groundLock_ctrl service_feedback_groundLock_ctrl_data;

    memset(&service_groundLock_ctrl_data, 0, sizeof(service_groundLock_ctrl_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_groundLock_ctrl_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_ctrlFlag = cJSON_GetObjectItem(root, "ctrlFlag");
    if (item_ctrlFlag != NULL && cJSON_IsNumber(item_ctrlFlag))
    {
        service_groundLock_ctrl_data.ctrlFlag = item_ctrlFlag->valueint;
    }

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

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_lockCtrl_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_lockCtrl service_lockCtrl_data;
    evs_service_feedback_lockCtrl service_feedback_lockCtrl_data;

    memset(&service_lockCtrl_data, 0, sizeof(service_lockCtrl_data));

    cJSON *item_gunNo = cJSON_GetObjectItem(root, "gunNo");
    if (item_gunNo != NULL && cJSON_IsNumber(item_gunNo))
    {
        service_lockCtrl_data.gunNo = item_gunNo->valueint;
    }

    cJSON *item_lockParam = cJSON_GetObjectItem(root, "lockParam");
    if (item_lockParam != NULL && cJSON_IsNumber(item_lockParam))
    {
        service_lockCtrl_data.lockParam = item_lockParam->valueint;
    }

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

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_dev_maintain_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }

    evs_service_dev_maintain service_dev_maintain;
    evs_service_feedback_dev_maintain service_feedback_dev_maintain;

    memset(&service_dev_maintain, 0, sizeof(service_dev_maintain));

    cJSON *item_ctrlType = cJSON_GetObjectItem(root, "ctrlType");
    if (item_ctrlType != NULL && cJSON_IsNumber(item_ctrlType))
    {
        service_dev_maintain.ctrlType = item_ctrlType->valueint;
    }

    callback = evs_service_callback(EVS_DEV_MAINTAIN_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_dev_maintain *request, evs_service_feedback_dev_maintain *feedcak))callback)(&service_dev_maintain, &service_feedback_dev_maintain);
    }
    cJSON *response_root = cJSON_CreateObject();
    cJSON_AddNumberToObject(response_root, "ctrlType", service_feedback_dev_maintain.ctrlType);
    cJSON_AddNumberToObject(response_root, "reason", service_feedback_dev_maintain.reason);

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

static int evs_service_orderCharge_handler(const char *request, char **response, int *response_len)
{
    void *callback;
    cJSON *root = cJSON_Parse(request);
    if (root == NULL || !cJSON_IsObject(root))
    {
        PROTOCOL_TRACE("JSON Parse Error");
        return -1;
    }
    evs_service_orderCharge service_oderCharge_data;
    evs_service_feedback_orderCharge service_feedback_oderCharge_data;

    memset(&service_oderCharge_data, 0, sizeof(service_oderCharge_data));

    cJSON *item_preTradeNo = cJSON_GetObjectItem(root, "preTradeNo");
    if (item_preTradeNo != NULL && cJSON_IsString(item_preTradeNo))
    {
        char *tradeNo = item_preTradeNo->valuestring;
        memcpy(service_oderCharge_data.preTradeNo, tradeNo, strlen(tradeNo));
    }

    cJSON *item_validTime = cJSON_GetObjectItem(root, "validTime");
    if (item_validTime != NULL && cJSON_IsArray(item_validTime))
    {
        int item_num = cJSON_GetArraySize(item_validTime);
        if ((item_num > 0))
        {
            if (item_num <= EVS_MAX_SEG_LEN)
            {
                service_oderCharge_data.num = item_num;
            }
            else
            {
                service_oderCharge_data.num = EVS_MAX_SEG_LEN;
            }
            cJSON *array_validTime = NULL;
            int i = 0;
            for (i = 0; i < service_oderCharge_data.num; i++)
            {
                array_validTime = cJSON_GetArrayItem(item_validTime, i);
                memcpy(service_oderCharge_data.validTime[i], array_validTime->valuestring, strlen(array_validTime->valuestring));
            }

            cJSON *item_kw = cJSON_GetObjectItem(root, "kw");
            cJSON *array_kw;
            if (item_kw != NULL && cJSON_IsArray(item_kw))
            {
                for (i = 0; i < service_oderCharge_data.num; i++)
                {
                    array_kw = cJSON_GetArrayItem(item_kw, i);
                    service_oderCharge_data.kw[i] = array_kw->valueint;
                }
            }
        }
    }

    callback = evs_service_callback(EVS_ORDERLY_CHARGE_SRV);
    if (callback)
    {
        ((int (*)(const evs_service_orderCharge *request, evs_service_feedback_orderCharge *feedcak))callback)(&service_oderCharge_data, &service_feedback_oderCharge_data);
    }
    cJSON *response_root = cJSON_CreateObject();
    cJSON_AddStringToObject(response_root, "preTradeNo", service_feedback_oderCharge_data.preTradeNo);
    cJSON_AddNumberToObject(response_root, "reason", service_feedback_oderCharge_data.reason);
    cJSON_AddNumberToObject(response_root, "result", service_feedback_oderCharge_data.result);

    *response = cJSON_PrintUnformatted(response_root);

    if (*response == NULL)
    {
        PROTOCOL_TRACE("Json Not Exist!");
        return -1;
    }
    else
    {
        *response_len = strlen(*response);
    }

    cJSON_Delete(root);
    cJSON_Delete(response_root);

    return 0;
}

/** 事件回调：接收到云端下发的服务请求 **/
static int user_service_request_event_handler(const int devid, const char *serviceid, const int serviceid_len,
                                              const char *request, const int request_len,
                                              char **response, int *response_len)
{
    int add_result = 0;

    const char *response_fmt = "{\"Result\": %d}";

    PROTOCOL_TRACE("Service Request Received, Service ID: %.*s, Payload: %s", serviceid_len, serviceid, request);

    if (strlen("feeModelUpdateSrv") == serviceid_len && memcmp("feeModelUpdateSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_issue_feeModel_handler(request, response, response_len);
    }
    if (strlen("startChargeSrv") == serviceid_len && memcmp("startChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_startCharge_handler(request, response, response_len);
    }

    if (strlen("authResultSrv") == serviceid_len && memcmp("authResultSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_authCharge_handler(request, response, response_len);
    }

    if (strlen("stopChargeSrv") == serviceid_len && memcmp("stopChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_stopCharge_handler(request, response, response_len);
    }

    if (strlen("orderCheckSrv") == serviceid_len && memcmp("orderCheckSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_confirmTrade_handler(request, response, response_len);
    }
    if (strlen("queDataSrv") == serviceid_len && memcmp("queDataSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_query_log_handler(request, response, response_len);
    }
    if (strlen("gateLockSrv") == serviceid_len && memcmp("gateLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_gateLock_ctrl_handler(request, response, response_len);
    }
    if (strlen("groundLockSrv") == serviceid_len && memcmp("groundLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_groundLock_ctrl_handler(request, response, response_len);
    }
    if (strlen("ctrlLockSrv") == serviceid_len && memcmp("ctrlLockSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_lockCtrl_handler(request, response, response_len);
    }
    if (strlen("devMaintainSrv") == serviceid_len && memcmp("devMaintainSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_dev_maintain_handler(request, response, response_len);
    }
    if (strlen("acOrderlyChargeSrv") == serviceid_len && memcmp("acOrderlyChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_orderCharge_handler(request, response, response_len);
    }
    if (strlen("dcOrderlyChargeSrv") == serviceid_len && memcmp("dcOrderlyChargeSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_orderCharge_handler(request, response, response_len);
    }
    if (strlen("confUpdateSrv") == serviceid_len && memcmp("confUpdateSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_update_config_handler(request, response, response_len);
    }
    if (strlen("getConfSrv") == serviceid_len && memcmp("getConfSrv", serviceid, serviceid_len) == 0)
    {
        evs_service_get_config_handler(request, response, response_len);
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

static int send_property_dcPile(evs_property_dcPile *data)
{
    int res = 0;
    char *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcDeRealIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "netType", data->netType);
    cJSON_AddNumberToObject(body, "sigVal", data->sigVal);

    cJSON_AddNumberToObject(body, "netId", data->netId);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    cJSON_AddNumberToObject(body, "caseTemp", data->caseTemp);
    cJSON_AddNumberToObject(body, "inletTemp", data->inletTemp);
    cJSON_AddNumberToObject(body, "outletTemp", data->outletTemp);

    cJSON_AddStringToObject(body, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(body, "serModelId", data->serModelId);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_property_acPile(evs_property_acPile *data)
{
    int res = 0;
    char *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acDeRealIty", body = cJSON_CreateObject());

    cJSON_AddNumberToObject(body, "netType", data->netType);
    cJSON_AddNumberToObject(body, "sigVal", data->sigVal);
    cJSON_AddNumberToObject(body, "netId", data->netId);

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

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//交流非充电过程实时监测属性
static int send_property_ac_nonwork(evs_property_ac_nonWork *data)
{
    int res = 0;
    char *payload;
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acGunIdleIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(body, "workStatus", data->workStatus);

    cJSON_AddNumberToObject(body, "conStatus", data->conStatus);
    cJSON_AddNumberToObject(body, "outRelayStatus", data->outRelayStatus);
    cJSON_AddNumberToObject(body, "eLockStatus", data->eLockStatus);
    cJSON_AddNumberToObject(body, "gunTemp", data->gunTemp);

    cJSON_AddNumberToObject(body, "acVolA", data->acVolA);
    cJSON_AddNumberToObject(body, "acCurA", data->acCurA);

    cJSON_AddNumberToObject(body, "acVolB", data->acVolB);
    cJSON_AddNumberToObject(body, "acCurB", data->acCurB);

    cJSON_AddNumberToObject(body, "acVolC", data->acVolC);
    cJSON_AddNumberToObject(body, "acCurC", data->acCurC);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//交流充电过程实时监测属性
static int send_property_ac_work(evs_property_ac_work *data)
{
    int res = 0;
    char *payload;
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
    cJSON_AddNumberToObject(body, "PwmDutyRadio", data->PwmDutyRadio);
    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电过程BMS实时监测属性
static int send_property_bms(evs_property_BMS *data)
{
    int res = 0;
    char *payload;
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
    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流非充电过程实时监测属性
static int send_property_dc_nonwork(evs_property_dc_nonWork *data)
{
    int res = 0;
    char *payload;
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

    cJSON_AddNumberToObject(body, "conTemp1", data->conTemp1);
    cJSON_AddNumberToObject(body, "conTemp2", data->conTemp2);

    cJSON_AddNumberToObject(body, "dcVol", data->dcVol);
    cJSON_AddNumberToObject(body, "dcCur", data->dcCur);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电过程实时监测属性
static int send_property_dc_work(evs_property_dc_work *data)
{
    int res = 0;
    char *payload;
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

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//直流充电设备交流输入电表底值监测属性表
static int send_property_dc_input_meter(evs_property_dc_input_meter *data)
{
    int res = 0;
    char *payload, Temp[16] = {0};
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcSysMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);

    cJSON_AddStringToObject(body, "acqTime", data->acqTime);

    bcd2str(data->mailAddr, Temp, sizeof(data->mailAddr));
    cJSON_AddStringToObject(body, "mailAddr", Temp);

    bcd2str(data->meterNo, Temp, sizeof(data->meterNo));
    cJSON_AddStringToObject(body, "meterNo", Temp);
    cJSON_AddStringToObject(body, "assetId", data->assetId);

    sprintf(Temp, "%d", data->sumMeter);
    cJSON_AddStringToObject(body, "sumMeter", Temp);
    sprintf(Temp, "%d", data->ApElect);
    cJSON_AddStringToObject(body, "ApElect", Temp);
    sprintf(Temp, "%d", data->BpElect);
    cJSON_AddStringToObject(body, "BpElect", Temp);
    sprintf(Temp, "%d", data->CpElect);
    cJSON_AddStringToObject(body, "CpElect", Temp);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//充电设备输出电表底值监测属性表
static int send_property_dc_outmeter(evs_property_meter *data)
{
    int res = 0;
    char *payload, Temp[16] = {0};
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "dcOutMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);

    cJSON_AddStringToObject(body, "acqTime", data->acqTime);

    bcd2str(data->mailAddr, Temp, sizeof(data->mailAddr));
    cJSON_AddStringToObject(body, "mailAddr", Temp);

    bcd2str(data->meterNo, Temp, sizeof(data->meterNo));
    cJSON_AddStringToObject(body, "meterNo", Temp);

    cJSON_AddStringToObject(body, "assetId", data->assetId);

    sprintf(Temp, "%d", data->sumMeter);
    cJSON_AddStringToObject(body, "sumMeter", Temp);

    cJSON_AddStringToObject(body, "lastTrade", data->lastTrade);
    cJSON_AddNumberToObject(body, "power", data->elec);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

//充电设备输出电表底值监测属性表
static int send_property_ac_outmeter(evs_property_meter *data)
{
    int res = 0;
    char *payload, Temp[16] = {0};
    cJSON *root, *body;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "acOutMeterIty", body = cJSON_CreateObject());
    cJSON_AddNumberToObject(body, "gunNo", data->gunNo);

    cJSON_AddStringToObject(body, "acqTime", data->acqTime);

    bcd2str(data->mailAddr, Temp, sizeof(data->mailAddr));
    cJSON_AddStringToObject(body, "mailAddr", Temp);

    bcd2str(data->meterNo, Temp, sizeof(data->meterNo));
    cJSON_AddStringToObject(body, "meterNo", Temp);

    cJSON_AddStringToObject(body, "assetId", data->assetId);

    sprintf(Temp, "%d", data->sumMeter);
    cJSON_AddStringToObject(body, "sumMeter", Temp);

    cJSON_AddStringToObject(body, "lastTrade", data->lastTrade);
    cJSON_AddNumberToObject(body, "power", data->elec);

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_Report(evs_g_user_ctx.master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));
    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Property Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_firware_info(evs_event_fireware_info *data)
{
    int res = 0;
    char *payload, meterAddr[13] = {0}, meter[EVS_MAX_METER_ADDR_LEN] = {0};
    cJSON *root, *inMeterArray, *outMeterArray;
    unsigned char i = 0, j = 0, k = 0;

    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "simNo", data->simNo);
    cJSON_AddStringToObject(root, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(root, "stakeModel", data->stakeModel);
    cJSON_AddStringToObject(root, "devSn", data->devSn);
    cJSON_AddStringToObject(root, "serModelId", data->serModelId);
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
    for (i = 0; i < EVS_MAX_INPUT_METER_NUM; i++)
    {
        if (memcmp(data->inMeter[i], meter, EVS_MAX_METER_ADDR_LEN) != 0)
        {
            for (j = 0, k = 0; j < EVS_MAX_METER_ADDR_LEN; k++, j++)
            {
                meterAddr[k] = ((data->inMeter[i][j] >> 4) + '0');
                meterAddr[++k] = (data->inMeter[i][j] & 0x0f) + '0';
            }
            //cJSON_AddStringToArray(inMeterArray, meterAddr);
            cJSON_AddItemToArray(inMeterArray, cJSON_CreateString(meterAddr));
        }
    }

    cJSON_AddItemToObject(root, "outMeter", outMeterArray = cJSON_CreateArray());
    for (i = 0; i < EVS_MAX_PORT_NUM; i++)
    {
        if (memcmp(data->outMeter[i], meter, EVS_MAX_METER_ADDR_LEN) != 0)
        {
            for (j = 0, k = 0; j < EVS_MAX_METER_ADDR_LEN; k++, j++)
            {
                meterAddr[k] = ((data->outMeter[i][j] >> 4) + '0');
                meterAddr[++k] = (data->outMeter[i][j] & 0x0f) + '0';
            }
            //cJSON_AddStringToArray(outMeterArray, meterAddr);
            cJSON_AddItemToArray(outMeterArray, cJSON_CreateString(meterAddr));
        }
    }

    payload = cJSON_PrintUnformatted(root);
    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "firmwareEvt", strlen("firmwareEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_ask_feeModel(evs_event_ask_feeModel *data)
{
    int res = 0;
    char *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(root, "serModelId", data->serModeId);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "askFeeModelEvt", strlen("askFeeModelEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_start_result(evs_event_startResult *data)
{
    int res = 0;
    char *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "startResult", data->startResult);
    cJSON_AddNumberToObject(root, "faultCode", data->faultCode);
    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddStringToObject(root, "vinCode", data->vinCode);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "startChaResEvt", strlen("startChaResEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_auth_start(evs_event_startCharge *data)
{
    int res = 0;
    char *payload = NULL;

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

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "startChargeAuthEvt", strlen("startChargeAuthEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_stopCharge(evs_event_stopCharge *data)
{
    int res = 0;
    char *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "stopResult", data->stopResult);
    cJSON_AddNumberToObject(root, "resultCode", data->resultCode);
    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddNumberToObject(root, "stopFailReson", data->stopFailReson);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "stopChaResEvt", strlen("stopChaResEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_groundLock_change(evs_event_groundLock_change *data)
{
    int res = 0;
    char *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "lockState", data->lockState);
    cJSON_AddNumberToObject(root, "powerType", data->powerType);
    cJSON_AddNumberToObject(root, "cellState", data->cellState);
    cJSON_AddNumberToObject(root, "lockerState", data->lockerState);
    cJSON_AddNumberToObject(root, "lockerForced", data->lockerForced);
    cJSON_AddNumberToObject(root, "lowPower", data->lowPower);
    cJSON_AddNumberToObject(root, "soc", data->soc);
    cJSON_AddNumberToObject(root, "openCnt", data->openCnt);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "groundLockEvt", strlen("groundLockEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_gateLock_change(evs_event_gateLock_change *data)
{
    int res = 0;
    char *payload = NULL;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "lockNo", data->lockNo);
    cJSON_AddNumberToObject(root, "lockState", data->lockState);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "smartLockEvent", strlen("smartLockEvent"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_tradeInfo(evs_event_tradeInfo *data)
{
    int res = 0;
    char *payload = NULL, time[16] = {0}, sumPower[16] = {0};

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);

    cJSON_AddStringToObject(root, "preTradeNo", data->preTradeNo);
    cJSON_AddStringToObject(root, "tradeNo", data->tradeNo);
    cJSON_AddStringToObject(root, "vinCode", data->vinCode);

    cJSON_AddNumberToObject(root, "timeDivType", data->timeDivType);

    sprintf(time, "%d", data->chargeStartTime);
    cJSON_AddStringToObject(root, "chargeStartTime", time);
    sprintf(time, "%d", data->chargeEndTime);
    cJSON_AddStringToObject(root, "chargeEndTime", time);

    cJSON_AddNumberToObject(root, "startSoc", data->startSoc);
    cJSON_AddNumberToObject(root, "endSoc", data->endSoc);
    cJSON_AddNumberToObject(root, "reason", data->reason);

    cJSON_AddNumberToObject(root, "totalElect", data->totalElect);

    cJSON_AddStringToObject(root, "eleModelId", data->eleModelId);
    cJSON_AddStringToObject(root, "serModelId", data->serModelId);

    sprintf(sumPower, "%d", data->sumStart);
    cJSON_AddStringToObject(root, "sumStart", sumPower);
    sprintf(sumPower, "%d", data->sumEnd);
    cJSON_AddStringToObject(root, "sumEnd", sumPower);

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
    cJSON_AddNumberToObject(root, "valleyServCost", data->valleyServCost);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "orderUpdateEvt", strlen("orderUpdateEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_alarm(evs_event_alarm *data)
{
    int res = 0;
    char *payload;
    cJSON *root, *faultArray, *warnArray;
    unsigned char i = 0;

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "faultSum", data->faultSum);
    cJSON_AddNumberToObject(root, "warnSum", data->warnSum);

    cJSON_AddItemToObject(root, "faultValue", faultArray = cJSON_CreateArray());
    for (i = 0; i < data->faultSum; i++)
    {
        //cJSON_AddNumberToArray(faultArray, data->faultValue[i]);
        cJSON_AddItemToArray(faultArray, cJSON_CreateNumber(data->faultValue[i]));
    }
    cJSON_AddItemToObject(root, "warnValue", warnArray = cJSON_CreateArray());
    for (i = 0; i < data->warnSum; i++)
    {
        //cJSON_AddNumberToArray(warnArray, data->warnValue[i]);
        cJSON_AddItemToArray(warnArray, cJSON_CreateNumber(data->warnValue[i]));
    }
    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "totalFaultEvt", strlen("totalFaultEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_ask_dev_config(void)
{
    int res = 0;
    char payload[6] = "{}";

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "askConfigEvt", strlen("askConfigEvt"), (char *)payload, strlen(payload));

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_acPile_change(evs_event_pile_stutus_change *data)
{
    int res = 0;
    char *payload, time[16] = {0};
    cJSON *root;

    sprintf(time, "%d", data->yxOccurTime);

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "yxOccurTime", time);
    cJSON_AddNumberToObject(root, "connCheckStatus", data->connCheckStatus);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "acStChEvt", strlen("acStChEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_dcPile_change(evs_event_pile_stutus_change *data)
{
    int res = 0;
    char *payload, time[16] = {0};
    cJSON *root;
    //unsigned char i = 0;

    sprintf(time, "%d", data->yxOccurTime);

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddStringToObject(root, "yxOccurTime", time);
    cJSON_AddNumberToObject(root, "connCheckStatus", data->connCheckStatus);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "dcStChEvt", strlen("acStChEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

static int send_event_car_info(evs_event_car_info *data)
{
    int res = 0;
    cJSON *root;
    char *payload;

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "gunNo", data->gunNo);
    cJSON_AddNumberToObject(root, "batterySOC", data->batterySOC);
    cJSON_AddNumberToObject(root, "batteryCap", data->batteryCap);
    cJSON_AddStringToObject(root, "gunNo", data->vinCode);
    cJSON_AddNumberToObject(root, "state", data->state);

    payload = cJSON_PrintUnformatted(root);

    res = IOT_Linkkit_TriggerEvent(evs_g_user_ctx.master_devid, "acCarInfoEvt", strlen("acCarInfoEvt"), (char *)payload, strlen(payload));

    if (root != NULL)
    {
        cJSON_Delete(root);
    }

    if (payload != NULL)
    {
        HAL_Free(payload);
    }

    PROTOCOL_TRACE("Post Event Message ID: %d", res);
    if (res < 0)
    {
        return -1;
    }
    return res;
}

int evs_linkkit_time_sync(void)
{
    int ret = 0;

    ret = IOT_Linkkit_Query(evs_g_user_ctx.master_devid, ITM_MSG_QUERY_TIMESTAMP, NULL, 0);
    if (ret)
    {
        PROTOCOL_TRACE("Linkkit Qurey time stamp fail %d ", ret);
        return 1;
    }

    return 0;
}

int evs_linkkit_fota(unsigned char *buffer, int buffer_length)
{
    int ret = 0;

    ret = IOT_Linkkit_Query(evs_g_user_ctx.master_devid, ITM_MSG_QUERY_FOTA_DATA, buffer, buffer_length);
    if (ret)
    {
        PROTOCOL_TRACE("Linkkit Qurey time stamp fail %d ", ret);
        return 1;
    }

    return 0;
}

int evs_linkkit_new(const int evs_is_ready, const int is_device_uid)
{

#ifdef DYNAMIC_REGISTER
    int DeviceSecretLength = 0;
    int regCodeLenth = 0;
    iotx_http_region_types_t region = IOTX_HTTP_REGION_CUSTOM;
    int res = 0;
    iotx_dev_meta_info_t dev_reg_meta;
    char reg_code[IOTX_DEVICE_REG_CODE_LEN + 1] = "";
    char device_uid[IOTX_DEVICE_UID_LEN + 1] = "";
#endif

#if !defined(PLATFORM_IS_DEBUG)
    int custom_port = 18883;
	IOT_SetLogLevel(IOT_LOG_ERROR); 
#else
    IOT_SetLogLevel(IOT_LOG_DEBUG);
#endif
    void *callback;
    int dynamic_register = 0, post_reply_need = 0;
    evs_device_meta evs_dev_meta;
    memset(&evs_g_user_ctx, 0, sizeof(evs_g_user_ctx));
    int ret = 0;

#ifdef ATM_ENABLED
    if (IOT_ATM_Init() < 0)
    {
        PROTOCOL_TRACE("IOT_ATM_Init failed!\n");
        return -1;
    }
#endif

#ifdef DYNAMIC_REGISTER
    memset(&dev_reg_meta, 0, sizeof(dev_reg_meta));
    memset(&evs_dev_meta, 0, sizeof(evs_dev_meta));
    callback = evs_service_callback(EVS_CERT_GET);
    if (callback)
    {
        ret = ((int (*)(evs_device_meta * meta)) callback)(&evs_dev_meta);
    }
    //PROTOCOL_TRACE("evs_dev_meta.device_secret is %s\n", evs_dev_meta.device_secret);
    //PROTOCOL_TRACE("evs_dev_meta.device_name is %s\n", evs_dev_meta.device_name);
    //PROTOCOL_TRACE("evs_dev_meta.product_key is %s\n", evs_dev_meta.product_key);

    DeviceSecretLength = strlen(evs_dev_meta.device_secret);
    //HAL_Printf("DeviceSecretLength is %d\n", DeviceSecretLength);
    //如果没有证书
    if ((DeviceSecretLength <= 5) || (DeviceSecretLength > IOTX_DEVICE_SECRET_LEN) || (ret < 0))
    {
        if (is_device_uid != 0)
        {
            callback = evs_service_callback(EVS_DEVICE_UID_GET);
            if (callback)
            {
                regCodeLenth = ((int (*)(char *device_uid))callback)(device_uid);
                memcpy(dev_reg_meta.device_asset, device_uid, sizeof(device_uid));
            }
            IOT_Get_Regcode(region, &dev_reg_meta);
            //PROTOCOL_TRACE("IOT_Get_Regcode dev_reg_meta.device_reg_code is %s\n",dev_reg_meta.device_reg_code);
            regCodeLenth = strlen(dev_reg_meta.device_reg_code);
        }
        else
        {
            callback = evs_service_callback(EVS_DEVICE_REG_CODE_GET);
            if (callback)
            {

                regCodeLenth = ((int (*)(char *device_reg_code))callback)(reg_code);
                memcpy(dev_reg_meta.device_reg_code, reg_code, sizeof(reg_code));
            }
        }
        //regCodeLenth = HAL_GetDeviceRegCode(g_device_reg_code);
        //判断注册码，如果没有注册码，则在此循环
        //PROTOCOL_TRACE("dev_reg_meta.device_reg_code length is %d\n",regCodeLenth);
        //PROTOCOL_TRACE("dev_reg_meta.device_reg_code is %s\n",dev_reg_meta.device_reg_code);
        if ((regCodeLenth < 5) || (regCodeLenth > IOTX_DEVICE_REG_CODE_LEN))
        {
            HAL_Printf("Get RegCode failed\n");
            return -1;
        }
        res = IOT_Dynamic_Register(region, &dev_reg_meta);
        if (res < 0)
        {
            HAL_Printf("IOT_Dynamic_Register failed\n");
            return -2;
        }
        //HAL_Printf("\nProduct Key: %s\n", dev_reg_meta.product_key);
        memcpy(evs_dev_meta.product_key, dev_reg_meta.product_key, strlen(dev_reg_meta.product_key));
        //HAL_Printf("\nDevice Name: %s\n", dev_reg_meta.device_name);
        memcpy(evs_dev_meta.device_name, dev_reg_meta.device_name, strlen(dev_reg_meta.device_name));
        //HAL_Printf("\nDevice Secret: %s\n", dev_reg_meta.device_secret);
        memcpy(evs_dev_meta.device_secret, dev_reg_meta.device_secret, strlen(dev_reg_meta.device_secret));
        callback = evs_service_callback(EVS_CERT_SET);
        if (callback)
        {
            ((int (*)(const evs_device_meta meta))callback)(evs_dev_meta);
        }
    }
#endif
    callback = evs_service_callback(EVS_CERT_GET);
    if (callback)
    {
        if (((int (*)(evs_device_meta *))callback)(&evs_dev_meta) != 0)
        {
            HAL_Printf("Get cert failed\n");
            return -3;
        }
    }

    memset(&master_meta_info, 0, sizeof(iotx_linkkit_dev_meta_info_t));
    memcpy(master_meta_info.product_key, evs_dev_meta.product_key, strlen(evs_dev_meta.product_key));
    memcpy(master_meta_info.device_name, evs_dev_meta.device_name, strlen(evs_dev_meta.device_name));
    memcpy(master_meta_info.device_secret, evs_dev_meta.device_secret, strlen(evs_dev_meta.device_secret));

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

#if !defined(PLATFORM_IS_DEBUG)
    IOT_Ioctl(IOTX_IOCTL_SET_MQTT_DOMAIN, (void*)"10.111.186.1");
    IOT_Ioctl(IOTX_IOCTL_SET_MQTT_PORT, (void *)&custom_port);
#endif
    return 0;
}

int evs_linkkit_free()
{
    IOT_Linkkit_Close(evs_g_user_ctx.master_devid);
    IOT_SetLogLevel(IOT_LOG_NONE);
    return 0;
}

int evs_mainloop()
{

    static int main_loop_step = 0;
    static int evs_linkkit_open_cnt = 0;
    static int evs_linkkit_connect_cnt = 0;
    int res = 0;
    switch (main_loop_step)
    {
    case EVS_LINKKIT_OPEN:
        if ((evs_linkkit_open_cnt % 2000) == 0)
        {
            evs_g_user_ctx.master_devid = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &master_meta_info);
            if (evs_g_user_ctx.master_devid >= 0)
            {
                main_loop_step++;
                evs_linkkit_open_cnt = 0;
            }
            else
            {
                evs_linkkit_open_cnt++;
                PROTOCOL_TRACE("IOT_Linkkit_Open failed! retry after %d ms\n", 2000);
                return EVS_LINKKIT_OPEN_FAULT;
            }
        }
        else
        {
            evs_linkkit_open_cnt++;
            return EVS_LINKKIT_OPEN_WAIT;
        }
    case EVS_LINKKIT_CONNECT:
        if ((evs_linkkit_connect_cnt % 2000) == 0)
        {
            res = IOT_Linkkit_Connect(evs_g_user_ctx.master_devid);
            if (res >= 0)
            {
                main_loop_step++;
                evs_linkkit_connect_cnt = 0;
            }
            else
            {
                evs_linkkit_connect_cnt++;
                PROTOCOL_TRACE("IOT_Linkkit_Connect failed! retry after %d ms\n", 5000);
                return EVS_LINKKIT_CONNECT_FAULT;
            }
        }
        else
        {
            evs_linkkit_connect_cnt++;
            return EVS_LINKKIT_CONNECT_WAIT;
        }
    case EVS_LINKKIT_POLL:
        IOT_Linkkit_Yield(EVS_YIELD_TIMEOUT_MS);
        break;
    default:
        break;
    }
    return 0;
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

void evs_send_event(evs_cmd_event_enum event_type, void *param)
{
    switch (event_type)
    {
    case EVS_CMD_EVENT_FIREWARE_INFO:
        send_event_firware_info((evs_event_fireware_info *)param);
        break;

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
    case EVS_CMD_EVENT_ASK_DEV_CONFIG:
        send_event_ask_dev_config();
        /* code */
        break;
    case EVS_CMD_EVENT_CAR_INFO:
        send_event_car_info((evs_event_car_info *)param);
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

void evs_send_property(evs_cmd_property_enum property_type, void *param)
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