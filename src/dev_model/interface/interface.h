#ifndef INTERFACE_H
#define INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////////////
/*服务类型定义*/
typedef enum {
    
    /*服务回调*/
    EVS_GATA_LOCK_SRV,
	EVS_CHARGE_START_SRV,
    /*系统回调*/
    EVS_STATE_EVERYTHING, 
    EVS_CONNECT_SUCC, 
    EVS_DISCONNECTED, 
    EVS_REPORT_REPLY, 
    EVS_TRIGGER_EVENT_REPLY
    
    
} evs_service_type_t;


#define EVS_RegisterCallback(service, cb)            evs_register_for_##service(cb)
#define DECLARE_SEVICE_CALLBACK(service, cb)         int evs_register_for_##service(cb);
#define DEFINE_SEVICE_CALLBACK(service, cb)          int evs_register_for_##service(cb) { \
        if (service < 0 || service >= sizeof(g_evs_service_map)/sizeof(evs_service_map_t)) {return -1;} \
        g_evs_service_map[service].callback = (void *)callback;return 0;}

/*服务回调函数声明*/
DECLARE_SEVICE_CALLBACK(EVS_GATA_LOCK_SRV,  int (*cb)(const int input_data,int * output_data))
DECLARE_SEVICE_CALLBACK(EVS_CHARGE_START_SRV,  int (*cb)(const int input_data,int * output_data))
/*系统回调函数声明*/
DECLARE_SEVICE_CALLBACK(EVS_CONNECT_SUCC,         int (*cb)(void))
DECLARE_SEVICE_CALLBACK(EVS_DISCONNECTED,         int (*cb)(void))
DECLARE_SEVICE_CALLBACK(EVS_REPORT_REPLY,         int (*cb)(const int, const int, const char *, const int))
DECLARE_SEVICE_CALLBACK(EVS_TRIGGER_EVENT_REPLY,  int (*cb)(const int, const int, const char *, const int,
                       const char *, const int))
DECLARE_SEVICE_CALLBACK(EVS_STATE_EVERYTHING, int (*cb)(int ev, const char *msg))
//void *evs_event_callback(int service);
//void protocol_service_callback(evs_service_type_t type);
void *evs_service_callback(int service);
/*设备端接口*/

#ifdef __cplusplus
}
#endif
#endif /* protocol.h */