// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class LabelIterator implements Iterator<Label>
{
    static
    {
        LoadNative.loadNative();
    }

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

        Proxy indexedProxy = labelIteratorProxy
                                 .call("begin")
                                 .call("[]", (index++));

        return new Label(indexedProxy);
    }
}
