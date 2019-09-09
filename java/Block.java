// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

// TODO: WorkInfo, emitSignal
public class Block
{
    private Proxy javaBlockProxy = null;

    public Block()
    {
        ProxyEnvironment proxyEnvironment = new ProxyEnvironment("managed");
        Proxy blockRegistryClass = proxyEnvironment.findProxy("Pothos/BlockRegistry");

        javaBlockProxy = blockRegistryClass.call("()", "/blocks/java_block");
        javaBlockProxy.call("_setJavaBlock", this);
    }

    public Vector<InputPort> inputs()
    {
        @SuppressWarnings("unchecked") Vector<Proxy> inputProxies = (Vector<Proxy>)managedCall("inputs");
        Vector<InputPort> inputPorts = new Vector<InputPort>(inputProxies.size());

        for(int i = 0; i < inputPorts.size(); ++i)
        {
            inputPorts.set(i, new InputPort(inputProxies.get(i)));
        }

        return inputPorts;
    }

    public HashMap<String, InputPort> allInputs()
    {
        @SuppressWarnings("unchecked") HashMap<String, Proxy> inputProxies = (HashMap<String, Proxy>)managedCall("allInputs");
        HashMap<String, InputPort> inputPorts = new HashMap<String, InputPort>();

        Iterator<Map.Entry<String,Proxy>> inputProxyIterator = inputProxies.entrySet().iterator();
        while(inputProxyIterator.hasNext())
        {
            Map.Entry<String,Proxy> mapEntry = inputProxyIterator.next();
            inputPorts.put(mapEntry.getKey(), new InputPort(mapEntry.getValue()));
        }

        return inputPorts;
    }

    public Vector<OutputPort> outputs()
    {
        @SuppressWarnings("unchecked") Vector<Proxy> outputProxies = (Vector<Proxy>)managedCall("outputs");
        Vector<OutputPort> outputPorts = new Vector<OutputPort>(outputProxies.size());

        for(int i = 0; i < outputPorts.size(); ++i)
        {
            outputPorts.set(i, new OutputPort(outputProxies.get(i)));
        }

        return outputPorts;
    }

    public HashMap<String, OutputPort> allOutputs()
    {
        @SuppressWarnings("unchecked") HashMap<String, Proxy> outputProxies = (HashMap<String, Proxy>)managedCall("allOutputs");
        HashMap<String, OutputPort> outputPorts = new HashMap<String, OutputPort>();

        Iterator<Map.Entry<String,Proxy>> outputProxyIterator = outputProxies.entrySet().iterator();
        while(outputProxyIterator.hasNext())
        {
            Map.Entry<String,Proxy> mapEntry = outputProxyIterator.next();
            outputPorts.put(mapEntry.getKey(), new OutputPort(mapEntry.getValue()));
        }

        return outputPorts;
    }

    public InputPort input(String name)
    {
        return this.allInputs().get(name);
    }

    public InputPort input(int index)
    {
        return this.inputs().get(index);
    }

    public OutputPort output(String name)
    {
        return this.allOutputs().get(name);
    }

    public OutputPort output(int index)
    {
        return this.outputs().get(index);
    }

    public boolean isActive()
    {
        return (boolean)managedCall("isActive");
    }

    public InputPort setupInput(String name)
    {
        return setupInput(name, new DType(), "");
    }

    public InputPort setupInput(String name, DType dtype)
    {
        return setupInput(name, dtype, "");
    }

    public InputPort setupInput(String name, DType dtype, String domain)
    {
        Object[] args = new Object[3];
        args[0] = name;
        args[1] = dtype.getProxy();
        args[2] = domain;

        return new InputPort(javaBlockProxy.call("setupInput", args));
    }

    public InputPort setupInput(long index)
    {
        return setupInput(index, new DType(), "");
    }

    public InputPort setupInput(long index, DType dtype)
    {
        return setupInput(index, dtype, "");
    }

    public InputPort setupInput(long index, DType dtype, String domain)
    {
        Object[] args = new Object[3];
        args[0] = index;
        args[1] = dtype.getProxy();
        args[2] = domain;

        return new InputPort(javaBlockProxy.call("setupInput", args));
    }

    public OutputPort setupOutput(String name)
    {
        return setupOutput(name, new DType(), "");
    }

    public OutputPort setupOutput(String name, DType dtype)
    {
        return setupOutput(name, dtype, "");
    }

    public OutputPort setupOutput(String name, DType dtype, String domain)
    {
        Object[] args = new Object[3];
        args[0] = name;
        args[1] = dtype.getProxy();
        args[2] = domain;

        return new OutputPort(javaBlockProxy.call("setupOutput", args));
    }

    public OutputPort setupOutput(long index)
    {
        return setupOutput(index, new DType(), "");
    }

    public OutputPort setupOutput(long index, DType dtype)
    {
        return setupOutput(index, dtype, "");
    }

    public OutputPort setupOutput(long index, DType dtype, String domain)
    {
        Object[] args = new Object[3];
        args[0] = index;
        args[1] = dtype.getProxy();
        args[2] = domain;

        return new OutputPort(javaBlockProxy.call("setupOutput", args));
    }

    public void registerSignal(String name)
    {
        javaBlockProxy.call("registerSignal", name);
    }

    public void registerSlot(String name)
    {
        javaBlockProxy.call("registerSlot", name);
    }

    public void registerProbe(String name, String signalName, String slotName)
    {
        Object[] args = new Object[3];
        args[0] = name;
        args[1] = signalName;
        args[2] = slotName;

        javaBlockProxy.call("registerProbe", args);
    }

    public void yield()
    {
        javaBlockProxy.call("yield");
    }

    // These should be overridden.
    public void activate() {}
    public void deactivate() {}
    public void work() {}
    // TODO: propagateLabels

    // For Topology
    public final Proxy getInternalBlock()
    {
        return javaBlockProxy;
    }

    //
    // Helpers
    //

    private Object managedCall(String name)
    {
        return javaBlockProxy.call(name).toObject();
    }

    private Object managedCall(String name, Object arg)
    {
        return javaBlockProxy.call(name, arg).toObject();
    }

    private Object managedCall(String name, Object[] args)
    {
        return javaBlockProxy.call(name, args).toObject();
    }
}
