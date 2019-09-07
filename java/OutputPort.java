// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.nio.ByteBuffer;

public class OutputPort
{
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
        Object[] args = new Object[1];
        args[0] = alias;

        outputPortProxy.call("setAlias", args);
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
        Object[] args = new Object[1];
        args[0] = numElements;

        outputPortProxy.call("produce", args);
    }

    public void popElements(long numElements)
    {
        Object[] args = new Object[1];
        args[0] = numElements;

        outputPortProxy.call("popElements", args);
    }

    public void postLabel(Label label)
    {
        Object[] args = new Object[1];
        args[0] = label.getProxy();

        outputPortProxy.call("postLabel", args);
    }

    public void postMessage(Object message)
    {
        Object[] args = new Object[1];
        args[0] = message;

        outputPortProxy.call("postMessage", args);
    }

    public void postBuffer(ByteBuffer buffer)
    {
        Object[] args = new Object[1];
        args[0] = buffer;

        outputPortProxy.call("postBuffer", args);
    }

    public void setReserve(long numElements)
    {
        Object[] args = new Object[1];
        args[0] = numElements;

        outputPortProxy.call("setReserve", args);
    }

    public boolean isSignal()
    {
        return (boolean)managedCall("isSignal");
    }

    public void setReadBeforeWrite(InputPort port)
    {
        Object[] args = new Object[1];
        args[0] = port.getProxy();

        outputPortProxy.call("setReadBeforeWrite", args);
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
