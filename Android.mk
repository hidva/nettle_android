

LOCAL_PATH_BAK := $(LOCAL_PATH)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := nettle


ifdef $(LOCAL_MODULE)_c_includes
LOCAL_C_INCLUDES := $($(LOCAL_MODULE)_c_includes)
endif

ifdef $(LOCAL_MODULE)_cflags
LOCAL_CFLAGS := $($(LOCAL_MODULE)_cflags)
endif

ifdef $(LOCAL_MODULE)_cppflags
LOCAL_CPPFLAGS := $($(LOCAL_MODULE)_cppflags)
endif

ifdef $(LOCAL_MODULE)_export_cflags
LOCAL_EXPORT_CFLAGS := $($(LOCAL_MODULE)_export_cflags)
endif

ifdef $(LOCAL_MODULE)_export_cppflags
LOCAL_EXPORT_CPPFLAGS := $($(LOCAL_MODULE)_export_cppflags)
endif

ifdef $(LOCAL_MODULE)_export_c_includes
LOCAL_EXPORT_C_INCLUDES := $($(LOCAL_MODULE)_export_c_includes)
endif

LOCAL_SRC_FILES := 			\
	src/sha3-256.c			\
	src/aes-encrypt.c              	\
	src/sha3-256-meta.c            	\
	src/sha3-permute.c             	\
	src/aes-decrypt.c              	\
	src/aes-decrypt-internal.c     	\
	src/aes-meta.c                 	\
	src/aes-set-decrypt-key.c      	\
	src/aes-encrypt-table.c        	\
	src/aes-encrypt-internal.c     	\
	src/aes-set-encrypt-key.c      	\
	src/sha3.c                     	\
	src/write-le64.c

LOCAL_CFLAGS += -DHAVE_CONFIG_H=1

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ $(LOCAL_PATH)/src
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/include/ $(LOCAL_PATH)/src


include $(BUILD_STATIC_LIBRARY)

LOCAL_PATH := $(LOCAL_PATH_BAK)
