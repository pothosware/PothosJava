// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "../JavaProxy.hpp"
#include "JNIUtility.hpp"

#include <Pothos/Proxy.hpp>

#include <jni.h>

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
 * Signature: (JLjava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_Pothos_Proxy_callJNI__JLjava_lang_String_2_3Ljava_lang_Object_2
  (JNIEnv *, jclass, jlong handle, jstring name, jobjectArray params)
{
    auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
    auto nativeName = Pothos::Object(name).convert<std::string>();
    auto pProxyEnv = std::dynamic_pointer_cast<JavaProxyEnvironment>(pNativeProxy->getEnvironment());

    auto proxyVector = Pothos::Object(params).convert<Pothos::ProxyVector>();

    return pNativeProxy->getHandle()->call(
               nativeName,
               proxyVector.data(),
               proxyVector.size());
}

/*
 * Class:     Pothos_Proxy
 * Method:    toStringJNI
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Pothos_Proxy_toStringJNI
  (JNIEnv *, jclass, jlong handle)
{
    auto* pNativeProxy = jlongToPtr<Pothos::Proxy>(handle);
    return Pothos::Object(pNativeProxy->toString()).convert<jstring>();
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
