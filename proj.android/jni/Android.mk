LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog -landroid

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp


##下面是把Classes目录下面的所有.cpp以及.c源文件全部包含进来
#MY_CPP_PATH  := $(LOCAL_PATH)/../../Classes
#MY_ALL_FILES := $(shell find $(MY_CPP_PATH)/.)
#MY_ALL_FILES := $(MY_ALL_FILES:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
#MY_CPP_LIST  := $(filter %.cpp %.c,$(MY_ALL_FILES))
#MY_CPP_LIST  := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)
#
#LOCAL_SRC_FILES := $(MY_CPP_LIST)
#
##这三行命令可以把Classes目录下的所有头文件都包含进去
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
#LOCAL_C_INCLUDES += $(shell ls -FR $(LOCAL_C_INCLUDES) | grep $(LOCAL_PATH)/$ )
#LOCAL_C_INCLUDES := $(LOCAL_C_INCLUDES:$(LOCAL_PATH)/%:=$(LOCAL_PATH)/%)
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos/2d/platform/android/jni

#下面的方法比较麻烦

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/modules/FlappyBird.cpp \
                   ../../Classes/modules/LoadingScene.cpp \
                   ../../Classes/modules/ResourceLoader.cpp \
                   ../../Classes/modules/WelcomeLayer.cpp \
                   ../../Classes/modules/WelcomeScene.cpp \
                   ../../Classes/modules/main_game/BackgroundLayer.cpp \
                   ../../Classes/modules/main_game/GameLayer.cpp \
                   ../../Classes/modules/main_game/GameScene.cpp \
                   ../../Classes/modules/main_game/Number.cpp \
                   ../../Classes/modules/main_game/OptionLayer.cpp \
                   ../../Classes/modules/main_game/StatusLayer.cpp \
                   ../../Classes/modules/main_game/UserRecord.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/modules
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/modules/main_game

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
#$(call import-module,2d/platform/android)
$(call import-module,audio/android)
$(call import-module,Box2D)
