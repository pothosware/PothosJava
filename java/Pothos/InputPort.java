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
        inputPortProxy.call("setAlias", alias);
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
        inputPortProxy.call("removeLabel", label.getProxy());
    }

    public void consume(long numElements)
    {
        inputPortProxy.call("consume", numElements);
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
        inputPortProxy.call("pushBuffer", buffer);
    }

    public void pushLabel(Label label)
    {
        inputPortProxy.call("pushLabel", label.getProxy());
    }

    public void pushMessage(Object message)
    {
        inputPortProxy.call("pushLabel", message);
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
