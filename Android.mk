LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := gxi_pack.c
LOCAL_CFLAGS += -I. -I/usr/include/
LOCAL_MODULE := pack_intel
LOCAL_MODULE_TAGS := optional
include $(BUILD_HOST_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := gxi_unpack.c
LOCAL_CFLAGS += -I. -I/usr/include/
LOCAL_MODULE := unpack_intel
LOCAL_MODULE_TAGS := optional
include $(BUILD_HOST_EXECUTABLE)
