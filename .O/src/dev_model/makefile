MODULE_NAME := src/dev_model
ALL_SUB_DIRS := certs extension external_libs/mbedtls external_libs/nghttp2 src/atm src/coap src/dev_bind src/dev_model src/dev_reset src/dev_sign src/dynamic_register src/http src/http2 src/infra src/mqtt src/ota src/shadow src/wifi_provision wrappers
AR := ar
CC := gcc
CFLAGS := -DCONFIG_MBEDTLS_DEBUG_LEVEL=0 -DCONFIG_MQTT_RX_MAXLEN=5000 -DDEVICE_MODEL_ENABLED -DDEV_SIGN -DDM_MESSAGE_CACHE_DISABLED -DDYNAMIC_REGISTER -DFORCE_SSL_VERIFY -DHAL_KV -DHTTP_DYNAMIC_REGISTER -DINFRA_CJSON -DINFRA_COMPAT -DINFRA_HTTPC -DINFRA_JSON_PARSER -DINFRA_LIST -DINFRA_LOG -DINFRA_LOG_ALL_MUTED -DINFRA_LOG_MUTE_CRT -DINFRA_LOG_MUTE_DBG -DINFRA_LOG_MUTE_ERR -DINFRA_LOG_MUTE_FLW -DINFRA_LOG_MUTE_INF -DINFRA_LOG_MUTE_WRN -DINFRA_LOG_NETWORK_PAYLOAD -DINFRA_MD5 -DINFRA_NET -DINFRA_REPORT -DINFRA_SHA256 -DINFRA_STRING -DINFRA_TIMER -DLOG_REPORT_TO_CLOUD -DMQTT_AUTO_SUBSCRIBE -DMQTT_COMM_ENABLED -DMQTT_DEFAULT_IMPL -DMQTT_DIRECT -DOTA_ENABLED -DPLATFORM_HAS_DYNMEM -DPLATFORM_HAS_MBEDTLS -DPLATFORM_HAS_STDINT -DPLATFORM_IS_DEBUG -DSDK_TEAM_TEST -DSUPPORT_TLS -DWITH_MEM_STATS=0 -DWITH_MEM_STATS_PER_MODULE=0 -DWITH_MQTT_DYN_BUF=1 -DWITH_MQTT_JSON_FLOW=1 -DWITH_MQTT_SUB_SHORTCUT=1 -DWITH_MQTT_ZIP_TOPIC=1 -D_PLATFORM_IS_LINUX_ -D__UBUNTU_SDK_DEMO__ -Iwrappers -Os -rdynamic -w
COMP_LIB := libiot_sdk.a
COMP_LIB_COMPONENTS := certs src/dev_model src/dev_sign src/dynamic_register src/infra src/mqtt src/ota
CONFIG_VENDOR := ubuntu
CROSS_CANDIDATES := AR CC CXX LD OBJCOPY STRIP
CROSS_PREFIX := 
CXX := g++
EXPORT_DIR := 
IMPORT_DIR := tools/prebuilt
INSTALL_DIR := /home/zhangqiang/evse/evse-sdk-3.20/.O/usr
INSTALL_LIB_DIR := /home/zhangqiang/evse/evse-sdk-3.20/.O/usr/lib
KERNEL_DIR := 
LD := ld
LDFLAGS := -lpthread -lrt
MAKE_ENV_VARS := 
NOEXEC_CMAKE_DIRS := 
OBJCOPY := objcopy
PACKAGE_DIR := /home/zhangqiang/evse/evse-sdk-3.20/packages
RULE_DIR := /home/zhangqiang/evse/evse-sdk-3.20/tools/build-rules
STRIP := strip
SYSROOT_INC := /home/zhangqiang/evse/evse-sdk-3.20/.O/usr/include
TOP_DIR := /home/zhangqiang/evse/evse-sdk-3.20
WIN32_CMAKE_SKIP := 
COMP_LIB_FILES :=  libiot_infra.a  libiot_sign.a  libiot_mqtt.a  libiot_cert.a  libiot_dynreg.a  libiot_ota.a  libiot_alink.a

include $(RULE_DIR)/settings.mk
include $(CONFIG_TPL)

all:

LIBA_TARGET     := libiot_alink.a

HDR_REFS        += src/infra
HDR_REFS		+= src/mqtt
HDR_REFS		+= src/dev_sign

DEPENDS         += wrappers
LDFLAGS         += -liot_sdk -liot_hal -liot_tls

LIB_SRCS_PATTERN     	:= *.c server/*.c client/*.c deprecated/*.c interface/*.c protocol/*.c

LIB_SRCS_EXCLUDE     	  := examples/linkkit_example_solo.c examples/cJSON.c
SRCS_linkkit-example-solo := examples/linkkit_example_solo.c examples/cJSON.c

LIB_SRCS_EXCLUDE             += examples/linkkit_example_gateway.c examples/cJSON.c
SRCS_linkkit-example-gateway := examples/linkkit_example_gateway.c examples/cJSON.c

LIB_SRCS_EXCLUDE     	  += examples/device_example_pile.c examples/cJSON.c
SRCS_device_example_pile := examples/device_example_pile.c examples/cJSON.c

$(call Append_Conditional, LIB_SRCS_PATTERN, alcs/*.c, ALCS_ENABLED)

$(call Append_Conditional, TARGET, device_example_pile, DEVICE_MODEL_ENABLED, BUILD_AOS NO_EXECUTABLES)
$(call Append_Conditional, TARGET, linkkit-example-solo, DEVICE_MODEL_ENABLED, BUILD_AOS NO_EXECUTABLES)
$(call Append_Conditional, TARGET, linkkit-example-gateway, DEVICE_MODEL_GATEWAY, BUILD_AOS NO_EXECUTABLES)


env:
	@echo ""
	@printf -- "-----------------------------------------------------------------\n"
	@$(foreach var,$(SHOW_ENV_VARS),$(call Dump_Var,$(var)))
	@printf -- "-----------------------------------------------------------------\n"
	@echo ""

include $(RULE_DIR)/rules.mk
