// Copyright (c) 2013-2014 Josh Blum
//                    2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include "JavaProxy.hpp"
#include <Pothos/Callable.hpp>
#include <Pothos/Plugin.hpp>
#include <Pothos/System/Paths.hpp>
#include <iostream>
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/Format.h>
#include <Poco/Path.h>
#include <Poco/SingletonHolder.h>
#include <Poco/String.h>
#include <cstdint>
#include <mutex>

/***********************************************************************
 * JVM per process manager -- we only get 1 JVM per process
 **********************************************************************/
//! wrapper knows how to delete jvm
struct MyJvmWrapper
{
    MyJvmWrapper(void):
        jvm(nullptr)
    {
        return;
    }

    ~MyJvmWrapper(void)
    {
        //This is hanging on windows and apparently never really works.
        //Since a JVM is once per process, it doesnt really hurt to not clean it up.
        //if (jvm != nullptr) jvm->DestroyJavaVM();
    }

    JavaVM *jvm;
};

static std::mutex &getJvmMutex(void)
{
    static Poco::SingletonHolder<std::mutex> sh;
    return *sh.get();
}

static MyJvmWrapper &getJvmWrapper(void)
{
    static Poco::SingletonHolder<MyJvmWrapper> sh;
    return *sh.get();
}

/***********************************************************************
 * JavaProxyEnvironment - create JVM and JNIEnv
 **********************************************************************/

static Poco::Path getModulesDir()
{
    return Poco::Path(Pothos::System::getPothosDevLibraryPath())
               .append("Pothos")
               .append("modules" + Pothos::System::getAbiVersion())
               .absolute();
}

static std::vector<std::string> getAllJARFiles()
{
    Poco::Path dirPath(getModulesDir());

    std::vector<std::string> jarFiles;
    Poco::SimpleRecursiveDirectoryIterator end;
    for(Poco::SimpleRecursiveDirectoryIterator dirIter(dirPath);
        dirIter != end;
        ++dirIter)
    {
        Poco::Path path(dirIter->path());

        if(path.getExtension() == "jar")
        {
            jarFiles.emplace_back(path.toString());
        }
    }

    return jarFiles;
}

static std::string getJavaClassPathParameter()
{
    std::string pathSeparatorString;
    pathSeparatorString.push_back(Poco::Path::pathSeparator());

    auto jarFiles = getAllJARFiles();
    auto appendedJARFiles = Poco::cat(
                                pathSeparatorString,
                                jarFiles.begin(),
                                jarFiles.end());
    std::string ret;
    if(!appendedJARFiles.empty())
    {
        ret = "-Djava.class.path=" + appendedJARFiles;
    }

    return ret;
}

JavaProxyEnvironment::JavaProxyEnvironment(const Pothos::ProxyEnvironmentArgs &args)
{
    std::lock_guard<std::mutex> lock(getJvmMutex());
    MyJvmWrapper &wrapper = getJvmWrapper();
    if (wrapper.jvm != nullptr)
    {
        jint ret = wrapper.jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (ret < 0) throw Pothos::ProxyEnvironmentFactoryError("JavaProxyEnvironment::GetEnv()");
    }

    else
    {
        JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
        std::vector<std::string> optionsManaged;
        for (const auto &entry : args)
        {
            optionsManaged.push_back("-D" + entry.first + "=" + entry.second);
        }
        optionsManaged.push_back("-verbose:jni");

        std::string classPathParam = getJavaClassPathParameter();
        if(!classPathParam.empty())
        {
            optionsManaged.emplace_back(std::move(classPathParam));
        }

        JavaVMOption* options = new JavaVMOption[optionsManaged.size()];
        for (size_t i = 0; i < optionsManaged.size(); i++)
        {
            options[i].optionString = (char *)optionsManaged[i].c_str();
        }
        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = args.size();
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;
        /* load and initialize a Java VM, return a JNI interface
         * pointer in env */
        jint ret = JNI_CreateJavaVM(&wrapper.jvm, (void**)&env, &vm_args);
        delete options;

        if (ret < 0) throw Pothos::ProxyEnvironmentFactoryError("JavaProxyEnvironment::JNI_CreateJavaVM()");
    }

    this->jvm = wrapper.jvm;
}

Pothos::Proxy JavaProxyEnvironment::makeHandle(jvalue value, char sig)
{
    auto env = std::dynamic_pointer_cast<JavaProxyEnvironment>(this->shared_from_this());
    return Pothos::Proxy(new JavaProxyHandle(env, value, sig));
}

std::shared_ptr<JavaProxyHandle> JavaProxyEnvironment::getHandle(const Pothos::Proxy &proxy)
{
    Pothos::Proxy myProxy = proxy;
    if (proxy.getEnvironment() != this->shared_from_this())
    {
        auto local = proxy.getEnvironment()->convertProxyToObject(proxy);
        myProxy = this->convertObjectToProxy(local);
    }
    return std::dynamic_pointer_cast<JavaProxyHandle>(myProxy.getHandle());
}

Pothos::Proxy JavaProxyEnvironment::findProxy(const std::string &name)
{
    jvalue value;
    value.l = this->forName(name.c_str());
    if (value.l == nullptr)
    {
        throw Pothos::ProxyEnvironmentFindError("JavaProxyEnvironment::findProxy("+name+")");
    }
    return this->makeHandle(value, 'L');
}

void JavaProxyEnvironment::serialize(const Pothos::Proxy &proxy, std::ostream &os)
{
    try
    {
        auto b = this->findProxy("java.io.ByteArrayOutputStream").call("new");
        auto o = this->findProxy("java.io.ObjectOutputStream").call("new", b);
        o.call("writeObject", proxy);
        const auto bytes = b.call<std::vector<int8_t>>("toByteArray");
        os.write((const char *)bytes.data(), bytes.size());
    }
    catch (const Pothos::Exception &ex)
    {
        throw Pothos::ProxySerializeError("JavaProxyEnvironment::serialize()", ex);
    }
}

Pothos::Proxy JavaProxyEnvironment::deserialize(std::istream &is)
{
    is.seekg (0, std::ios_base::end);
    const auto length = is.tellg();
    is.seekg (0, std::ios_base::beg);
    std::vector<Poco::Int8> bytes(length);
    is.read((char *)bytes.data(), bytes.size());

    try
    {
        auto b = this->findProxy("java.io.ByteArrayInputStream").call("new", bytes);
        auto o = this->findProxy("java.io.ObjectInputStream").call("new", b);
        return o.call("readObject");
    }
    catch (const Pothos::Exception &ex)
    {
        throw Pothos::ProxySerializeError("JavaProxyEnvironment::deserialize()", ex);
    }
}

Pothos::Object JavaProxyEnvironment::convertProxyToObject(const Pothos::Proxy &proxy_)
{
    // First, try the parent method.
    try
    {
        return Pothos::ProxyEnvironment::convertProxyToObject(proxy_);
    }
    catch (const Pothos::ProxyEnvironmentConvertError&) {}

    Pothos::Proxy proxy = proxy_;
    auto javaHandle = std::dynamic_pointer_cast<JavaProxyHandle>(proxy.getHandle());

    while(javaHandle->hasSuperclass())
    {
        proxy = javaHandle->getProxyWithSuperclassName();
        javaHandle = std::dynamic_pointer_cast<JavaProxyHandle>(proxy.getHandle());
        try
        {
            return Pothos::ProxyEnvironment::convertProxyToObject(proxy);
        }
        catch(const Pothos::ProxyEnvironmentConvertError&) {}
    }

    // At this point, we've tried everything up to java.lang.Object, so if
    // there's no conversion so far, there's no conversion at all.
    throw Pothos::ProxyEnvironmentConvertError(
        "JavaProxyEnvironment::convertProxyToObject()",
        Poco::format("cannot convert %s or any superclasses to Pothos::Object",
        proxy_.getClassName()));
}

/***********************************************************************
 * factory registration
 **********************************************************************/
Pothos::ProxyEnvironment::Sptr makeJavaProxyEnvironment(const Pothos::ProxyEnvironmentArgs &args)
{
    return Pothos::ProxyEnvironment::Sptr(new JavaProxyEnvironment(args));
}

pothos_static_block(pothosRegisterJavaProxy)
{
    Pothos::PluginRegistry::addCall(
        "/proxy/environment/java",
        &makeJavaProxyEnvironment);
}
