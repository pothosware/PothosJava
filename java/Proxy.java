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

    public Object call(String name, Object param1)
    {
        return callJNI(nativeHandle, name, param1);
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

    private static native Object callJNI(long handle, String name, Object param1);

    private static native int hashCodeJNI(long handle);

    private static native boolean equalsJNI(long handle1, long handle2);

    private static native long allocateJNI();
}
