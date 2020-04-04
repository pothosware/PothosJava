// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class DType
{
    static
    {
        LoadNative.loadNative();
    }

    private Proxy dtypeProxy;

    public DType()
    {
        ProxyEnvironment proxyEnvironment = new ProxyEnvironment("managed");
        Proxy managedDTypeClass = proxyEnvironment.findProxy("Pothos/DType");

        dtypeProxy = managedDTypeClass.call("()");
    }

    public DType(String markup)
    {
        ProxyEnvironment proxyEnvironment = new ProxyEnvironment("managed");
        Proxy managedDTypeClass = proxyEnvironment.findProxy("Pothos/DType");

        dtypeProxy = managedDTypeClass.call("()", markup);
    }

    public DType(String alias, int dimension)
    {
        ProxyEnvironment proxyEnvironment = new ProxyEnvironment("managed");
        Proxy managedDTypeClass = proxyEnvironment.findProxy("Pothos/DType");

        Object[] args = new Object[2];
        args[0] = alias;
        args[1] = dimension;

        dtypeProxy = managedDTypeClass.call("()", args);
    }

    public DType(Proxy proxy)
    {
        dtypeProxy = proxy;
    }

    // TODO: Java-esque version

    public static DType fromDType(DType dtype, int dimension)
    {
        return new DType(dtype.getMarkup(), dimension);
    }

    public String name()
    {
        return (String)managedCall("name");
    }

    public char elemType()
    {
        return (char)managedCall("elemType");
    }

    public char elemSize()
    {
        return (char)managedCall("elemSize");
    }

    public int dimension()
    {
        return (int)managedCall("dimension");
    }

    public int size()
    {
        return (int)managedCall("size");
    }

    public String getMarkup()
    {
        return (String)managedCall("getMarkup");
    }

    public boolean isCustom()
    {
        return (boolean)managedCall("isCustom");
    }

    public boolean isFloat()
    {
        return (boolean)managedCall("isFloat");
    }

    public boolean isInteger()
    {
        return (boolean)managedCall("isInteger");
    }

    public boolean isSigned()
    {
        return (boolean)managedCall("isSigned");
    }

    public boolean isComplex()
    {
        return (boolean)managedCall("isComplex");
    }

    public Proxy getProxy()
    {
        return dtypeProxy;
    }

    @Override
    public String toString()
    {
        return (String)managedCall("toString");
    }

    @Override
    public int hashCode()
    {
        return dtypeProxy.hashCode();
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

        Object[] args = new Object[1];
        args[0] = obj;

        return (boolean)managedCall("==", args);
    }

    //
    // Helpers
    //

    private Object managedCall(String name)
    {
        return dtypeProxy.call(name).toObject();
    }

    private Object managedCall(String name, Object[] args)
    {
        return dtypeProxy.call(name, args).toObject();
    }
}
