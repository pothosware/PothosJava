// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.nio.ByteBuffer;

public class OutputPort
{
    static
    {
        LoadNative.loadNative();
    }

    private Proxy outputPortProxy;

    public OutputPort(Proxy proxy)
    {
        outputPortProxy = proxy;
    }

    public int index()
    {
        return (int)managedCall("index");
    }

    public String name()
    {
        return (String)managedCall("name");
    }

    public String alias()
    {
        return (String)managedCall("alias");
    }

    public void setAlias(String alias)
    {
        outputPortProxy.call("setAlias", alias);
    }

    public DType dtype()
    {
        return new DType(outputPortProxy.call("dtype"));
    }

    public String domain()
    {
        return (String)managedCall("domain");
    }

    public ByteBuffer buffer()
    {
        return (ByteBuffer)managedCall("buffer");
    }

    public long elements()
    {
        return (long)managedCall("elements");
    }

    public long totalElements()
    {
        return (long)managedCall("totalElements");
    }

    public long totalBuffers()
    {
        return (long)managedCall("totalBuffers");
    }

    public long totalLabels()
    {
        return (long)managedCall("totalLabels");
    }

    public long totalMessages()
    {
        return (long)managedCall("totalMessages");
    }

    public void produce(long numElements)
    {
        outputPortProxy.call("produce", numElements);
    }

    public void popElements(long numElements)
    {
        outputPortProxy.call("popElements", numElements);
    }

    public void postLabel(Label label)
    {
        outputPortProxy.call("postLabel", label.getProxy());
    }

    public void postMessage(Object message)
    {
        outputPortProxy.call("postMessage", message);
    }

    public void postBuffer(ByteBuffer buffer)
    {
        outputPortProxy.call("postBuffer", buffer);
    }

    public void setReserve(long numElements)
    {
        outputPortProxy.call("setReserve", numElements);
    }

    public boolean isSignal()
    {
        return (boolean)managedCall("isSignal");
    }

    public void setReadBeforeWrite(InputPort port)
    {
        outputPortProxy.call("setReadBeforeWrite", port.getProxy());
    }

    public Proxy getProxy()
    {
        return outputPortProxy;
    }

    //
    // Helpers
    //

    private Object managedCall(String name)
    {
        return outputPortProxy.call(name).toObject();
    }

    private Object managedCall(String name, Object[] args)
    {
        return outputPortProxy.call(name, args).toObject();
    }

    private Object managedGet(String field)
    {
        return outputPortProxy.get(field).toObject();
    }
}
