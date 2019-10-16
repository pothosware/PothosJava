// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class Label
{
    private Proxy labelProxy;

    public Label(String id, Object data, long index)
    {
        this(id, data, index, 1);
    }

    public Label(String id, Object data, long index, long width)
    {
        ProxyEnvironment proxyEnv = new ProxyEnvironment("managed");
        Proxy labelClassProxy = proxyEnv.findProxy("Pothos/Label");

        Object[] args = new Object[4];
        args[0] = id;
        args[1] = data;
        args[2] = index;
        args[3] = width;

        labelProxy = labelClassProxy.call("()", args);
    }

    public Label(Proxy proxy)
    {
        labelProxy = proxy;
    }

    public Label toAdjusted(long mult, long div)
    {
        Object[] args = new Object[2];
        args[0] = mult;
        args[1] = div;

        return new Label(labelProxy.call("()", args));
    }

    public Label adjust(long mult, long div)
    {
        Object[] args = new Object[2];
        args[0] = mult;
        args[1] = div;

        return new Label(labelProxy.call("adjust", args));
    }

    public String id()
    {
        return (String)managedGet("id");
    }

    public Object data()
    {
        return managedGet("data");
    }

    public long index()
    {
        return (long)managedGet("index");
    }

    public long width()
    {
        return (long)managedGet("width");
    }

    public Proxy getProxy()
    {
        return labelProxy;
    }

    //
    // Helpers
    //

    private Object managedCall(String name)
    {
        return labelProxy.call(name).toObject();
    }

    private Object managedCall(String name, Object[] args)
    {
        return labelProxy.call(name, args).toObject();
    }

    private Object managedGet(String field)
    {
        return labelProxy.get(field).toObject();
    }
}
