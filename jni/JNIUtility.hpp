// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include "../JavaProxy.hpp"

#include <Pothos/Proxy.hpp>

#include <jni.h>

static jobject proxyToJObject(const Pothos::Proxy& proxy)
{
    auto proxyHandle = std::dynamic_pointer_cast<JavaProxyHandle>(proxy.getHandle());
    return proxyHandle->toJobject();
}

template <typename T>
static inline T* jlongToPtr(jlong handle)
{
    return reinterpret_cast<T*>(handle);
}

template <typename T>
static inline jlong ptrToJLong(T* ptr)
{
    return reinterpret_cast<jlong>(ptr);
}
