/*
 * Copyright (C) 2019 Technexion Ltd.
 *
 * Author: Wig Cheng <wig.cheng@technexion.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#define LOG_TAG    "gpio-jni"
#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <utils/Log.h>
#include <gpiod.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellolibs_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::ignore = thiz;

    ALOGI("GPIOd version start is hello");

    //const char* name="/dev/gpiochip2";
    const char* name="gpiochip2";
    int value = gpiod_ctxless_get_value((char *)name, 7, 0, "gpioget");

    ALOGI("GPIO value is %d", value);

    gpiod_ctxless_set_value("/dev/gpiochip2", 7, 0, 0, "gpioset", NULL, NULL);

    ALOGI("GPIOd version end is hello");

    return env->NewStringUTF(gpiod_version_string());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellolibs_MainActivity_getGpioInfo(JNIEnv *env, jobject thiz, jint gpiobank, jint gpioline) {

    std::ignore = thiz;

    char bank[32] = {0}, ret[4] = {0};
    sprintf(bank, "gpiochip%d", gpiobank);
    ALOGI("GPIO gpiobank is %d", gpiobank);
    ALOGI("GPIO gpioline is %d", gpioline);

    jint value = gpiod_ctxless_get_value((char *)bank, gpioline, 0, "gpioget");

    ALOGI("Value = %d", value);

    sprintf(ret, "%d", value);

    return env->NewStringUTF(ret);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellolibs_MainActivity_setGpioInfo(JNIEnv *env, jobject thiz, jint gpiobank, jint gpioline, jint gpio_value) {

    std::ignore = thiz;

    char bank[32] = {0};
    sprintf(bank, "/dev/gpiochip%d", gpiobank);
    ALOGI("GPIO gpiobank is %d", gpiobank);
    ALOGI("GPIO gpioline is %d", gpioline);

    int ret = gpiod_ctxless_set_value(bank, gpioline, gpio_value, 0, "gpioset", NULL, NULL);

    ALOGI("set gpio ret = %d", ret);

    return env->NewStringUTF("Set finish!");
}