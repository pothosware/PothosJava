// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "../JavaProxy.hpp"
#include "JNIUtility.hpp"

#include <Pothos/Proxy.hpp>

#include <jni.h>

static jobject proxyCallCommon(jlong handle, jstring name, size_t numParams, ...)
{
    auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
    auto nativeName = Pothos::Object(name).convert<std::string>();
    auto pProxyEnv = std::dynamic_pointer_cast<JavaProxyEnvironment>(pNativeProxy->getEnvironment());

    Pothos::ProxyVector proxyVector;
    proxyVector.reserve(numParams);

    va_list args;
    va_start(args, numParams);
    for(size_t i = 0; i < numParams; ++i)
    {
        jobject param = va_arg(args, jobject);
        proxyVector.emplace_back(pProxyEnv->makeHandle(param));
    }

    va_end(args);

    return pNativeProxy->getHandle()->call(
               nativeName,
               proxyVector.data(),
               numParams);
}

/*
 * Class:     Pothos_Proxy
 * Method:    callJNI
 * Signature: (JLjava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_Pothos_Proxy_callJNI__JLjava_lang_String_2
  (JNIEnv *, jclass, jlong handle, jstring name)
{
    auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
    auto nativeName = Pothos::Object(name).convert<std::string>();

    auto nativeResult = pNativeProxy->call(nativeName, nullptr, 0);
    return proxyToJObject(nativeResult);
}

/*
 * Class:     Pothos_Proxy
 * Method:    callJNI
 * Signature: (JLjava/lang/String;Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_Pothos_Proxy_callJNI__JLjava_lang_String_2Ljava_lang_Object_2
  (JNIEnv *, jclass, jlong handle, jstring name, jobject param1)
{
    return proxyCallCommon(handle, name, 1, param1);
}

/*
 * Class:     Pothos_Proxy
 * Method:    hashCodeJNI
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_Pothos_Proxy_hashCodeJNI
  (JNIEnv *, jclass, jlong handle)
{
    return static_cast<jint>(jlongToPtr<Pothos::Proxy>(handle)->hashCode());
}

/*
 * Class:     Pothos_Proxy
 * Method:    equalsJNI
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_Pothos_Proxy_equalsJNI
  (JNIEnv *, jclass, jlong handle1, jlong handle2)
{
    auto* pProxy1 = jlongToPtr<Pothos::Proxy>(handle1);
    auto* pProxy2 = jlongToPtr<Pothos::Proxy>(handle2);

    return ((*pProxy1) == (*pProxy2));
}

/*
 * Class:     Pothos_Proxy
 * Method:    allocateJNI
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_allocateJNI
  (JNIEnv *, jclass)
{
    return ptrToJLong(new Pothos::Proxy());
}
