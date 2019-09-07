// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.nio.ByteBuffer;

public class InputPort
{
    private Proxy inputPortProxy;

    public InputPort(Proxy proxy)
    {
        inputPortProxy = proxy;
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

        inputPortProxy.call("setAlias", args);
    }

    public DType dtype()
    {
        return new DType(inputPortProxy.call("dtype"));
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

    public boolean hasMessage()
    {
        return (boolean)managedCall("hasMessage");
    }

    public LabelIterator labels()
    {
        return new LabelIterator(inputPortProxy.call("labels"));
    }

    public void removeLabel(Label label)
    {
        Object[] args = new Object[1];
        args[0] = label.getProxy();

        inputPortProxy.call("removeLabel", args);
    }

    public void consume(long numElements)
    {
        Object[] args = new Object[1];
        args[0] = numElements;

        inputPortProxy.call("consume", args);
    }

    public ByteBuffer takeBuffer()
    {
        return (ByteBuffer)managedCall("takeBuffer");
    }

    public Object popMessage()
    {
        return managedCall("popMessage");
    }

    public Object peekMessage()
    {
        return managedCall("peekMessage");
    }

    public boolean isSlot()
    {
        return (boolean)managedCall("isSlot");
    }

    public void pushBuffer(ByteBuffer buffer)
    {
        Object[] args = new Object[1];
        args[0] = buffer;

        inputPortProxy.call("pushBuffer", args);
    }

    public void pushLabel(Label label)
    {
        Object[] args = new Object[1];
        args[0] = label.getProxy();

        inputPortProxy.call("pushLabel", args);
    }

    public void pushMessage(Object message)
    {
        Object[] args = new Object[1];
        args[0] = message;

        inputPortProxy.call("pushLabel", args);
    }

    public void clear()
    {
        inputPortProxy.call("clear");
    }

    public Proxy getProxy()
    {
        return inputPortProxy;
    }

    //
    // Helpers
    //

    private Object managedCall(String name)
    {
        return inputPortProxy.call(name).toObject();
    }

    private Object managedCall(String name, Object[] args)
    {
        return inputPortProxy.call(name, args).toObject();
    }

    private Object managedGet(String field)
    {
        return inputPortProxy.get(field).toObject();
    }
}
