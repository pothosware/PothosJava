// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class Proxy
{
    private long nativeHandle;

    public Proxy()
    {
        nativeHandle = allocateJNI();
    }

    public Object call(String name)
    {
        return callJNI(nativeHandle, name);
    }

    public Object call(String name, Object[] params)
    {
        return callJNI(nativeHandle, name, params);
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

    private static native Object callJNI(long handle, String name);

    private static native Object callJNI(long handle, String name, Object[] params);

    private static native String toStringJNI(long handle);

    private static native int hashCodeJNI(long handle);

    private static native boolean equalsJNI(long handle1, long handle2);

    private static native long allocateJNI();
}
