// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "JavaProxy.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Plugin.hpp>
#include <Pothos/Proxy.hpp>

#include <Pothos/Framework/BufferChunk.hpp>
#include <Pothos/Framework/SharedBuffer.hpp>

#include <Poco/String.h>

#include <jni.h>

#include <algorithm>
#include <complex>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

static Pothos::Proxy convertBufferChunkToJavaByteBuffer(
    Pothos::ProxyEnvironment::Sptr env,
    const Pothos::BufferChunk& buffer)
{
    auto javaProxyEnvironment = std::dynamic_pointer_cast<JavaProxyEnvironment>(env);
    jobject jniByteBuffer = javaProxyEnvironment->env->NewDirectByteBuffer(
                                reinterpret_cast<void*>(buffer.address),
                                static_cast<jlong>(buffer.length));

    auto bufferProxy = javaProxyEnvironment->makeHandle(jniByteBuffer);

    // Cast the return buffer type to the correct subclass based on the
    // BufferChunk's dtype.
    static const std::unordered_map<std::string, std::string> dtypeToJavaFunc =
    {
        {"int8", "asCharBuffer"},
        {"int16", "asShortBuffer"},
        {"int32", "asIntBuffer"},
        {"int64", "asLongBuffer"},
        {"float32", "asFloatBuffer"},
        {"float64", "asDoubleBuffer"}
    };
    auto mapIter = dtypeToJavaFunc.find(buffer.dtype.name());
    if(mapIter != dtypeToJavaFunc.end())
    {
        const std::string& castFunc = mapIter->second;
        bufferProxy = bufferProxy.call(castFunc);
    }
    else
    {
        throw Pothos::InvalidArgumentException("Invalid or unsupported DType: "+buffer.dtype.name());
    }

    return bufferProxy;
}

static bool isJavaProxySubclass(
    const Pothos::Proxy& proxy,
    const std::string& destClass)
{
    auto env = proxy.getEnvironment();

    auto proxyJavaClass = proxy.call("class");
    auto destJavaClass = env->findProxy(destClass);

    return destJavaClass.call<bool>("isAssignableFrom", proxyJavaClass);
}

static Pothos::BufferChunk convertJavaByteBufferToBufferChunk(const Pothos::Proxy& byteBuffer)
{
    // The given byte buffer must be direct (meaning it has a "backing" array
    // that can be accessed by native code).
    if(!byteBuffer.call<bool>("isDirect"))
    {
        throw Pothos::InvalidArgumentException("The given "+byteBuffer.getClassName()+" cannot be accessed by native code.");
    }

    auto javaProxyEnvironment = std::dynamic_pointer_cast<JavaProxyEnvironment>(
                                    byteBuffer.getEnvironment());
    jobject jniByteBuffer = javaProxyEnvironment->getHandle(byteBuffer)->toJobject();

    void* address = javaProxyEnvironment->env->GetDirectBufferAddress(jniByteBuffer);
    jlong capacity = javaProxyEnvironment->env->GetDirectBufferCapacity(jniByteBuffer);

    static const std::unordered_map<std::string, std::string> javaClassToDType =
    {
        {"java.nio.ByteBuffer", "int8"},
        {"java.nio.CharBuffer", "int8"},
        {"java.nio.ShortBuffer", "int16"},
        {"java.nio.IntBuffer", "int32"},
        {"java.nio.LongBuffer", "int64"},
        {"java.nio.FloatBuffer", "float32"},
        {"java.nio.DoubleBuffer", "float64"},
    };
    using MapPair = std::unordered_map<std::string, std::string>::value_type;

    auto applicableClassIter = std::find_if(
        javaClassToDType.begin(),
        javaClassToDType.end(),
        [&byteBuffer](const MapPair& mapPair)
        {
            return isJavaProxySubclass(byteBuffer, mapPair.first);
        });
    if(applicableClassIter == javaClassToDType.end())
    {
        throw Pothos::InvalidArgumentException("Could not find valid DType for "+byteBuffer.getClassName());
    }

    Pothos::DType dtype(applicableClassIter->second);

    auto sharedBuff = Pothos::SharedBuffer(
                          reinterpret_cast<size_t>(address),
                          static_cast<size_t>(capacity * dtype.elemSize()),
                          byteBuffer.getHandle());
    auto chunk = Pothos::BufferChunk(sharedBuff);
    chunk.dtype = dtype;

    return chunk;
}

pothos_static_block(pothosRegisterJavaByteBufferConversions)
{
    Pothos::PluginRegistry::addCall(
        "/proxy/converters/java/bufferchunk_to_java_bytebuffer",
        &convertBufferChunkToJavaByteBuffer);

    const std::vector<std::string> compatibleByteBufferClasses =
    {
        "ByteBuffer",
        "CharBuffer",
        "ShortBuffer",
        "IntBuffer",
        "LongBuffer",
        "FloatBuffer",
        "DoubleBuffer"
    };
    for(const std::string& byteBufferClass: compatibleByteBufferClasses)
    {
        const std::string lowerName = Poco::toLower(byteBufferClass);

        Pothos::PluginRegistry::add(
            "/proxy/converters/java/java_"+lowerName+"_to_bufferchunk",
            Pothos::ProxyConvertPair(
                "java.nio."+byteBufferClass,
                &convertJavaByteBufferToBufferChunk));
    }
}
