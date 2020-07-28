#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "protocol_data_def.h"

#define EVS_LINKKIT_OPEN 0
#define EVS_LINKKIT_CONNECT 1
#define EVS_LINKKIT_POLL 2

#define EVS_LINKKIT_OPEN_FAULT -1    //设备linkkit打开失败
#define EVS_LINKKIT_OPEN_WAIT -2     //设备linkkit打开重试等待
#define EVS_LINKKIT_CONNECT_FAULT -3 //设备linkkit连接失败
#define EVS_LINKKIT_CONNECT_WAIT -4  //设备linkkit连接重试等待

#define EVS_IS_NOT_READY -1       //设备未准备就绪
#define EVS_GET_REG_CODE_FAULT -2 //获取设备注册码失败
#define EVS_SET_CERT_FAULT -3     //设置设备证书失败
    /*
函数名称： int evs_linkkit_new(const int evs_is_ready,const int is_device_uid)
函数功能： 当设备就绪后（可以读取到设备的设备证书信息和设备注册码），创建SDK套件
输入参数： evs_is_ready 
1：设备准备就绪   
0: 设备未准备就绪
is_device_uid
0:使用注册码获取证书
1：使用设备唯一编码获取证书
返回值:
0                                 设备执行成功
EVS_IS_NOT_READY           设备未准备就绪
EVS_GET_REG_CODE_FAULT     获取设备注册码失败
EVS_SET_CERT_FAULT         设置设备证书失败 
*/
    int evs_linkkit_new(const int evs_is_ready,const int is_device_uid);

    /*
函数名称： int evs_linkkit_time_sync(void)
函数功能： 当设备与iot平台连接成功后，进行校时
输入参数： 无 

返回值:
0   校时请求发送成功
1  校时 请求发送失败
*/
    int evs_linkkit_time_sync(void);
    /*
函数名称： int evs_linkkit_fota(unsigned char *buffer, int buffer_length)
函数功能： 当iot平台连下发固件升级时，进行ota固件包下载
输入参数： 
1 buffer固件缓存区
2 buffer_length 缓存区大小
返回值:
0   ota固件下载成功
1   ota固件下载失败
*/
    int evs_linkkit_fota(unsigned char *buffer, int buffer_length);

    int evs_linkkit_free();
    /*
函数名称： int evs_mainloop()
函数功能： SDK功能运行函数
输入参数： 无
返回值:
EVS_LINKKIT_OPEN_FAULT           设备linkkit打开失败
EVS_LINKKIT_OPEN_WAIT            设备linkkit打开重试等待
EVS_LINKKIT_CONNECT_FAULT        设备linkkit连接失败  
EVS_LINKKIT_CONNECT_WAIT         设备linkkit连接重试等待  
*/
    int evs_mainloop();

    //int evs_send_event();
    //int evs_post_property();
    /**
 * @brief Send pile event data to SDK.
 *---
 * @param [in] event_type: @n the event you want to send.
 * @param [in] param: @n the event data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
    void evs_send_event(evs_cmd_event_enum event_type, void *param);

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
    void evs_send_property(evs_cmd_property_enum property_type, void *param);

#ifdef __cplusplus
}
#endif
#endif /* interface.h */