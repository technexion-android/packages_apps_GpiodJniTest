/*
 * Copyright (C) 2016 The Android Open Source Project
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

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   app/src/main/java/com/example/hellolibs/MainActivity.java
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hellolibs_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    // Just for simplicity, we do this right away; correct way would do it in
    // another thread...
//    auto ticks = GetTicks();
//
//    for (auto exp = 0; exp < 32; ++exp) {
//        volatile unsigned val = gpower(exp);
//        (void) val;  // to silence compiler warning
//    }
//    ticks = GetTicks() - ticks;
//
//    LOGI("calculation time: %" PRIu64, ticks);
    std::ignore = thiz;

    ALOGI("GPIOd version start is hello");

    ALOGI("GPIOd version is %s", gpiod_version_string());

    //const char* name="/dev/gpiochip2";
    const char* name="gpiochip2";
    int value = gpiod_ctxless_get_value((char *)name, 7, 0, "gpioget");

    ALOGI("GPIO value is %d", value);

    gpiod_ctxless_set_value("/dev/gpiochip2", 7, 0, 0, "gpioset", NULL, NULL);

    ALOGI("GPIOd version end is hello");

    gpiod_chip* fd = gpiod_chip_open("/dev/gpiochip2");

    if (fd != NULL){
        ALOGI("ROVER NOT NULL");

        gpiod_line* line = gpiod_chip_get_line(fd, 7);
        gpiod_line_set_value(line, 0);
    }
    else
        ALOGI("ROVER NULL");



    return env->NewStringUTF("Hello from JNI LIBS!");
}
