// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "../JavaProxy.hpp"
#include "JNIUtility.hpp"

#include <Pothos/Proxy.hpp>

#include <jni.h>

extern "C"
{

/*
 * Class:     Pothos_Proxy
 * Method:    getEnvironmentJNI
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_getEnvironmentJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);

        auto* pNewEnvironmentSPtr = new Pothos::ProxyEnvironment::Sptr();
        *pNewEnvironmentSPtr = pNativeProxy->getEnvironment();

        return ptrToJLong(pNewEnvironmentSPtr);
    )

    return 0;
}

/*
 * Class:     Pothos_Proxy
 * Method:    callJNI
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_callJNI__JLjava_lang_String_2
  (JNIEnv * env, jclass, jlong handle, jstring name)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto nativeName = Pothos::Object(name).convert<std::string>();

        Pothos::Proxy* pNewProxy = new Pothos::Proxy();
        *pNewProxy = pNativeProxy->call(nativeName, nullptr, 0);

        return ptrToJLong(pNewProxy);
    )

    return 0;
}

/*
 * Class:     Pothos_Proxy
 * Method:    callJNI
 * Signature: (JLjava/lang/String;[Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_callJNI__JLjava_lang_String_2_3Ljava_lang_Object_2
  (JNIEnv * env, jclass, jlong handle, jstring name, jobjectArray params)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto nativeName = Pothos::Object(name).convert<std::string>();

        auto proxyVector = Pothos::Object(params).convert<Pothos::ProxyVector>();

        Pothos::Proxy* pNewProxy = new Pothos::Proxy();
        *pNewProxy = pNativeProxy->getHandle()->call(
                         nativeName,
                         proxyVector.data(),
                         proxyVector.size());

        return ptrToJLong(pNewProxy);
    )

    return 0;
}

/*
 * Class:     Pothos_Proxy
 * Method:    getJNI
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_getJNI
  (JNIEnv * env, jclass, jlong handle, jstring field)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto nativeField = Pothos::Object(field).convert<std::string>();

        Pothos::Proxy* pNewProxy = new Pothos::Proxy();
        *pNewProxy = pNativeProxy->get(nativeField);

        return ptrToJLong(pNewProxy);
    )

    return 0;
}

/*
 * Class:     Pothos_Proxy
 * Method:    setObjectJNI
 * Signature: (JLjava/lang/String;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_Pothos_Proxy_setObjectJNI
  (JNIEnv * env, jclass, jlong handle, jstring field, jobject value)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto nativeField = Pothos::Object(field).convert<std::string>();

        auto javaEnv = std::dynamic_pointer_cast<JavaProxyEnvironment>(pNativeProxy->getEnvironment());
        auto valueProxy = javaEnv->makeHandle(value);

        pNativeProxy->set(nativeField, valueProxy);
    )
}

/*
 * Class:     Pothos_Proxy
 * Method:    setProxyJNI
 * Signature: (JLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_Pothos_Proxy_setProxyJNI
  (JNIEnv * env, jclass, jlong handle, jstring field, jlong valueHandle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto nativeField = Pothos::Object(field).convert<std::string>();
        auto* pValueProxy = jlongToPtr<Pothos::Proxy>(valueHandle);

        pNativeProxy->set(nativeField, (*pValueProxy));
    )
}

/*
 * Class:     Pothos_Proxy
 * Method:    toObjectJNI
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_Pothos_Proxy_toObjectJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        auto javaHandle = std::dynamic_pointer_cast<JavaProxyHandle>(pNativeProxy->getHandle());

        return javaHandle->toJobject();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_Proxy
 * Method:    getClassNameJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_Proxy_getClassNameJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        return Pothos::Object(pNativeProxy->getClassName()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_Proxy
 * Method:    toStringJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_Proxy_toStringJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
        return Pothos::Object(pNativeProxy->toString()).convert<jstring>();
    )

    return env->NewStringUTF("");
}

/*
 * Class:     Pothos_Proxy
 * Method:    hashCodeJNI
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_Pothos_Proxy_hashCodeJNI
  (JNIEnv * env, jclass, jlong handle)
{
    POTHOS_SAFE_JNI
    (
        return static_cast<jint>(jlongToPtr<Pothos::Proxy>(handle)->hashCode());
    )

    return 0;
}

/*
 * Class:     Pothos_Proxy
 * Method:    equalsJNI
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_Pothos_Proxy_equalsJNI
  (JNIEnv * env, jclass, jlong handle1, jlong handle2)
{
    POTHOS_SAFE_JNI
    (
        auto* pProxy1 = jlongToPtr<Pothos::Proxy>(handle1);
        auto* pProxy2 = jlongToPtr<Pothos::Proxy>(handle2);

        return ((*pProxy1) == (*pProxy2));
    )

    return JNI_FALSE;
}

/*
 * Class:     Pothos_Proxy
 * Method:    allocateJNI
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_Pothos_Proxy_allocateJNI
  (JNIEnv * env, jclass)
{
    POTHOS_SAFE_JNI
    (
        return ptrToJLong(new Pothos::Proxy());
    )

    return 0;
}

}
