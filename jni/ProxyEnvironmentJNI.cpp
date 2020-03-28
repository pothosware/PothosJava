// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "../JavaProxy.hpp"
#include "JNIUtility.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Proxy/Environment.hpp>

#include <Poco/Exception.h>

#include <jni.h>

#include <functional>
#include <iostream>

extern "C"
{

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    getLocalUniquePid
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_ProxyEnvironment_getLocalUniquePid
  (JNIEnv * env, jclass)
{
    POTHOS_SAFE_JNI
    (
        return Pothos::Object(Pothos::ProxyEnvironment::getLocalUniquePid()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    getNodeIdJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_ProxyEnvironment_getNodeIdJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        return Pothos::Object((*pNativeEnvSPtr)->getNodeId()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    getUniquePidJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_ProxyEnvironment_getUniquePidJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        return Pothos::Object((*pNativeEnvSPtr)->getUniquePid()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    getPeeringAddressJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_ProxyEnvironment_getPeeringAddressJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        return Pothos::Object((*pNativeEnvSPtr)->getPeeringAddress()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    getNameJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_ProxyEnvironment_getNameJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        return Pothos::Object((*pNativeEnvSPtr)->getName()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    findProxyJNI
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_ProxyEnvironment_findProxyJNI
  (JNIEnv * env, jclass, jlong handle, jstring name)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        auto nativeName = (*pNativeEnvSPtr)->makeProxy(name).convert<std::string>();

        Pothos::Proxy* pNewProxy = Pothos::Proxy();
        *pNewProxy = (*pNativeEnvSPtr)->findProxy(nativeName);

        return ptrToJLong(pNewProxy);
    )

    return 0;
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    hashCodeJNI
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_Pothos_ProxyEnvironment_hashCodeJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle);
        return static_cast<jint>(std::hash<std::string>{}((*pNativeEnvSPtr)->getName()));
    )

    return 0;
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    equalsJNI
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_Pothos_ProxyEnvironment_equalsJNI
  (JNIEnv * env, jclass, jlong handle1, jlong handle2)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeEnvSPtr1 = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle1);
        auto* pNativeEnvSPtr2 = jlongToPtr<Pothos::ProxyEnvironment::Sptr>(handle2);

        return ((*pNativeEnvSPtr1)->getName() == (*pNativeEnvSPtr2)->getName());
    )

    return JNI_FALSE;
}

/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    allocateJNI
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_ProxyEnvironment_allocateJNI__Ljava_lang_String_2
  (JNIEnv * env, jclass, jstring name)
{
    POTHOS_SAFE_JNI
    (
        auto javaEnvSPtr = Pothos::ProxyEnvironment::make("java");
        auto nativeName = javaEnvSPtr->makeProxy(name).convert<std::string>();

        auto* pNewProxyEnvironment = new Pothos::ProxyEnvironment::Sptr();
        *pNewProxyEnvironment = Pothos::ProxyEnvironment::make(nativeName);

        return ptrToJLong(pNewProxyEnvironment);
    )

    return 0;
}


/*
 * Class:     Pothos_ProxyEnvironment
 * Method:    allocateJNI
 * Signature: (Ljava/lang/String;Ljava/util/HashMap;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_ProxyEnvironment_allocateJNI__Ljava_lang_String_2Ljava_util_HashMap_2
  (JNIEnv * env, jclass, jstring name, jobject proxyEnvironmentArgs)
{
    POTHOS_SAFE_JNI
    (
        auto javaEnvSPtr = Pothos::ProxyEnvironment::make("java");
        auto nativeName = javaEnvSPtr->makeProxy(name)
                              .convert<std::string>();
        auto nativeArgs = javaEnvSPtr->makeProxy(proxyEnvironmentArgs)
                              .convert<Pothos::ProxyEnvironmentArgs>();

        auto* pNewProxyEnvironment = new Pothos::ProxyEnvironment::Sptr();
        *pNewProxyEnvironment = Pothos::ProxyEnvironment::make(nativeName, nativeArgs);

        return ptrToJLong(pNewProxyEnvironment);
    )

    return 0;
}

}
