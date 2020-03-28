// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "JNIUtility.hpp"

#include <Pothos/Proxy.hpp>

#include <jni.h>

#include <iostream>

void pothosExceptionToJavaException(JNIEnv* env, const Pothos::Exception& ex)
{
    auto cls = env->FindClass("java/lang/RuntimeException");
    if(0 == cls) return;

    env->ThrowNew(cls, ex.what());
    env->DeleteLocalRef(cls);
}
