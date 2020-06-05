#include "interface.h"
#include "protocol_data_def.h"
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL (void *)0
#endif
typedef struct {
    int service_id;
    void *callback;
} evs_service_map_t;

static evs_service_map_t g_evs_service_map[] = {
   
    
	/*服务回调*/
	{EVS_GATA_LOCK_SRV,     NULL},
    {EVS_CHARGE_START_SRV,  NULL},
    /*系统回调*/
	{EVS_CONNECT_SUCC,  NULL},
    {EVS_DISCONNECTED,  NULL},
    {EVS_REPORT_REPLY,  NULL},
    {EVS_TRIGGER_EVENT_REPLY,  NULL},
    {EVS_STATE_EVERYTHING,  NULL}
    
};

void *evs_service_callback(int service)
{
    if (service < 0 || service >= sizeof(g_evs_service_map) / sizeof(evs_service_map_t)) {
        return NULL;
    }
    return g_evs_service_map[service].callback;
}

/*服务回调函数定义*/
DEFINE_SEVICE_CALLBACK(EVS_GATA_LOCK_SRV,     int (*callback)(const int input_data,int * output_data))
DEFINE_SEVICE_CALLBACK(EVS_CHARGE_START_SRV,  int (*callback)(const int input_data,int * output_data))

/*系统回调函数定义*/
DEFINE_SEVICE_CALLBACK(EVS_CONNECT_SUCC,         int (*callback)(void))
DEFINE_SEVICE_CALLBACK(EVS_DISCONNECTED,         int (*callback)(void))
DEFINE_SEVICE_CALLBACK(EVS_REPORT_REPLY,         int (*callback)(const int, const int, const char *, const int))
DEFINE_SEVICE_CALLBACK(EVS_TRIGGER_EVENT_REPLY,  int (*callback)(const int, const int, const char *, const int,
                       const char *, const int))
DEFINE_SEVICE_CALLBACK(EVS_STATE_EVERYTHING, int (*callback)(int ev, const char *msg)); 





