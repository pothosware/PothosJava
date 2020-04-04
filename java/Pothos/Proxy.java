// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class Proxy
{
    static
    {
        LoadNative.loadNative();
    }

    private long nativeHandle;

    public Proxy()
    {
        nativeHandle = allocateJNI();
    }

    public Proxy(long handle)
    {
        nativeHandle = handle;
    }

    public ProxyEnvironment getEnvironment()
    {
        return new ProxyEnvironment(getEnvironmentJNI(nativeHandle));
    }

    public Proxy call(String name)
    {
        return new Proxy(callJNI(nativeHandle, name));
    }

    public Proxy call(String name, Object param)
    {
        Object[] params = new Object[1];
        params[0] = param;

        return this.call(name, params);
    }

    public Proxy call(String name, Object[] params)
    {
        return new Proxy(callJNI(nativeHandle, name, params));
    }

    public Proxy call(String name, Proxy param)
    {
        Proxy[] params = new Proxy[1];
        params[0] = param;

        return this.call(name, params);
    }

    public Proxy call(String name, Proxy[] params)
    {
        Object[] objectParams = new Object[params.length];
        for(int i = 0; i < objectParams.length; ++i)
        {
            objectParams[i] = params[i].toObject();
        }

        return call(name, objectParams);
    }

    public Proxy get(String field)
    {
        return new Proxy(getJNI(nativeHandle, field));
    }

    public void set(String field, Object value)
    {
        setObjectJNI(nativeHandle, field, value);
    }

    public void set(String field, Proxy value)
    {
        setProxyJNI(nativeHandle, field, value.nativeHandle);
    }

    public Object toObject()
    {
        return toObjectJNI(nativeHandle);
    }

    public String getClassName()
    {
        return getClassNameJNI(nativeHandle);
    }

    @Override
    public String toString()
    {
        return toStringJNI(nativeHandle);
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
        else if(!(obj instanceof Proxy))
        {
            return false;
        }

        return equalsJNI(nativeHandle, ((Proxy)obj).nativeHandle);
    }

    //
    // JNI below
    //

    private static native long getEnvironmentJNI(long handle);

    private static native long callJNI(long handle, String name);

    private static native long callJNI(long handle, String name, Object[] params);

    private static native long getJNI(long handle, String field);

    private static native void setObjectJNI(long handle, String field, Object value);

    private static native void setProxyJNI(long handle, String field, long valueHandle);

    private static native Object toObjectJNI(long handle);

    private static native String getClassNameJNI(long handle);

    private static native String toStringJNI(long handle);

    private static native int hashCodeJNI(long handle);

    private static native boolean equalsJNI(long handle1, long handle2);

    private static native long allocateJNI();
}
