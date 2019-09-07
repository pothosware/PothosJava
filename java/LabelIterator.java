// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class LabelIterator implements Iterator<Label>
{
    private Proxy labelIteratorProxy;
    private long index = 0;
    private long length = 0;

    public LabelIterator(Proxy proxy)
    {
        labelIteratorProxy = proxy;
    }

    public boolean hasNext()
    {
        return (index < length);
    }

    public Label next()
    {
        if(!hasNext())
        {
            throw new NoSuchElementException(""+length);
        }

        Object[] args = new Object[1];
        args[0] = (index++);

        Proxy indexedProxy = labelIteratorProxy
                                 .call("begin")
                                 .call("[]", args);

        return new Label(indexedProxy);
    }
}
