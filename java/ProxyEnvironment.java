// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class ProxyEnvironment
{
    private long nativeHandle;

    public ProxyEnvironment(
        String name,
        java.util.HashMap proxyEnvironmentArgs)
    {
        nativeHandle = allocateJNI(name, proxyEnvironmentArgs);
    }

    public ProxyEnvironment(long handle)
    {
        nativeHandle = handle;
    }

    public String getNodeId()
    {
        return getNodeIdJNI(nativeHandle);
    }

    public String getUniquePid()
    {
        return getUniquePidJNI(nativeHandle);
    }

    public String getPeeringAddress()
    {
        return getPeeringAddressJNI(nativeHandle);
    }

    public String getName()
    {
        return getNameJNI(nativeHandle);
    }

    public Proxy findProxy(String name)
    {
        return new Proxy(findProxyJNI(nativeHandle, name));
    }

    @Override
    public String toString()
    {
        return getName();
    }

    @Override
    public int hashCode()
    {
        return hashCodeJNI(nativeHandle);
    }

    @Override
    public boolean equals(Object obj)
    {
        if(this == obj)
        {
            return true;
        }
        else if(!(obj instanceof ProxyEnvironment))
        {
            return false;
        }

        return equalsJNI(nativeHandle, ((ProxyEnvironment)obj).nativeHandle);
    }

    //
    // JNI below
    //

    public static native String getLocalUniquePid();

    private static native String getNodeIdJNI(long handle);

    private static native String getUniquePidJNI(long handle);

    private static native String getPeeringAddressJNI(long handle);

    private static native String getNameJNI(long handle);

    private static native long findProxyJNI(long handle, String name);

    private static native int hashCodeJNI(long handle);

    private static native boolean equalsJNI(long handle1, long handle2);

    private static native long allocateJNI(String name, java.util.HashMap proxyEnvironmentArgs);
}
