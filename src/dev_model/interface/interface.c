#include "interface.h"
#include "protocol_data_def.h"
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL (void *)0
#endif
typedef struct
{
    int service_id;
    void *callback;
} evs_service_map_t;

static evs_service_map_t g_evs_service_map[] = {

    /*服务回调*/
    {EVS_QUE_DARA_SRV, NULL},

    {EVS_DEV_MAINTAIN_SRV, NULL},     //设备维护服务
    {EVS_CTRL_LOCK_SRV, NULL},        //电子锁控制服务
    {EVS_FEE_MODEL_UPDATA_SRV, NULL}, //计量计费模型更新服务
    {EVS_START_CHARGE_SRV, NULL},     //平台远程启动服务
    {EVS_AUTH_RESULT_SRV, NULL},      //启动充电鉴权结果
    {EVS_STOP_CHARGE_SRV, NULL},      //平台停止充电
    {EVS_ORDER_CHECK_SRV, NULL},      //交易记录确认服务
    {EVS_RSV_CHARGE_SRV, NULL},       //预约充电服务
    {EVS_GROUND_LOCK_SRV, NULL},      //地锁控制服务
    {EVS_GATE_LOCK_SRV, NULL},        //智能门锁控制服务
    {EVS_ORDERLY_CHARGE_SRV, NULL},   //有序充电策略下发
    {EVS_POWER_CTRL_SRV, NULL},       //直流控制服务
    /*系统回调*/
    {EVS_CONNECT_SUCC, NULL},
    {EVS_DISCONNECTED, NULL},
    {EVS_REPORT_REPLY, NULL},
    {EVS_TRIGGER_EVENT_REPLY, NULL},
    {EVS_STATE_EVERYTHING, NULL}

};

void *evs_service_callback(int service)
{
    if (service < 0 || service >= sizeof(g_evs_service_map) / sizeof(evs_service_map_t))
    {
        return NULL;
    }
    return g_evs_service_map[service].callback;
}

/*服务回调函数定义*/
DEFINE_SEVICE_CALLBACK(EVS_DEV_MAINTAIN_SRV, int8_t (*callback)(evs_service_devCtrl *request, int *feedback))
DEFINE_SEVICE_CALLBACK(EVS_CTRL_LOCK_SRV, int8_t (*callback)(evs_service_lockCtrl *request, evs_service_feedback_lockCtrl *feedback))
DEFINE_SEVICE_CALLBACK(EVS_FEE_MODEL_UPDATA_SRV, int8_t (*callback)(evs_service_issue_feeModel *request, evs_service_feedback_feeModel *feedback))
DEFINE_SEVICE_CALLBACK(EVS_START_CHARGE_SRV, int8_t (*callback)(evs_service_startCharge *request, evs_service_feedback_startCharge *feedback))
DEFINE_SEVICE_CALLBACK(EVS_AUTH_RESULT_SRV, int8_t (*callback)(evs_service_authCharge *request, void *feedback))
DEFINE_SEVICE_CALLBACK(EVS_STOP_CHARGE_SRV, int8_t (*callback)(evs_service_stopCharge *request, evs_service_feedback_stopCharge *feedback))
DEFINE_SEVICE_CALLBACK(EVS_ORDER_CHECK_SRV, int8_t (*callback)(evs_service_confirmTrade *request, void *feedback))
DEFINE_SEVICE_CALLBACK(EVS_RSV_CHARGE_SRV, int8_t (*callback)(evs_service_rsvCharge *request, evs_service_feedback_rsvCharge *feedback))
DEFINE_SEVICE_CALLBACK(EVS_GROUND_LOCK_SRV, int8_t (*callback)(evs_service_groundLock_ctrl *request, evs_service_feedback_groundLock_ctrl *feedback))
DEFINE_SEVICE_CALLBACK(EVS_GATE_LOCK_SRV, int8_t (*callback)(evs_service_gateLock_ctrl *request, evs_service_feedback_gateLock_ctrl *feedback))
DEFINE_SEVICE_CALLBACK(EVS_ORDERLY_CHARGE_SRV, int8_t (*callback)(evs_service_orderCharge *request, evs_service_feedback_orderCharge *feedback))
//DEFINE_SEVICE_CALLBACK(EVS_POWER_CTRL_SRV, int8_t (*callback)(int *request, int *feedback))
DEFINE_SEVICE_CALLBACK(EVS_QUE_DARA_SRV, int8_t (*callback)(evs_service_query_log *request, evs_service_feedback_query_log *feedback))

/*系统回调函数定义*/
DEFINE_SEVICE_CALLBACK(EVS_CONNECT_SUCC, int (*callback)(void))
DEFINE_SEVICE_CALLBACK(EVS_DISCONNECTED, int (*callback)(void))
DEFINE_SEVICE_CALLBACK(EVS_REPORT_REPLY, int (*callback)(const int, const int, const char *, const int))
DEFINE_SEVICE_CALLBACK(EVS_TRIGGER_EVENT_REPLY, int (*callback)(const int, const int, const char *, const int,
                                                                const char *, const int))
DEFINE_SEVICE_CALLBACK(EVS_STATE_EVERYTHING, int (*callback)(int ev, const char *msg));
